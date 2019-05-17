// lightView.cpp : implementation of the CLightView class
//

#include "stdafx.h"
#include "light.h"

#include "lightDoc.h"
#include "lightView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightView

IMPLEMENT_DYNCREATE(CLightView, CView)

BEGIN_MESSAGE_MAP(CLightView, CView)
	//{{AFX_MSG_MAP(CLightView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightView construction/destruction

CLightView::CLightView(): 
	scr(600, 400),
	m_st(ST_NONE)
{
	// TODO: add construction code here

}

CLightView::~CLightView()
{
}

BOOL CLightView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLightView drawing

void CLightView::OnDraw(CDC* pDC)
{
	CLightDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
/*	const double R =100.0;
	const double x0=20.0,y0=-30.0,z0=20.0;
	for(double i=-100.0; i<100.0;i++)
		for(double j=-100.0; j<100.0;j++)
		{
			if(sqrt(i*i+j*j)< R)
			{
				double a = x0*i+y0*j+z0*sqrt(R*R-i*i-j*j);
				double b = x0*i+y0*j-z0*sqrt(R*R-i*i-j*j);
				if (a > (x0*x0+y0*y0+z0*z0))
					pDC->SetPixel(i+200,j+200, RGB(255,0,0));
				if (b > (x0*x0+y0*y0+z0*z0))
					pDC->SetPixel(i+200,j+200, RGB(0,0,255));
				double z = (x0*x0+y0*y0+z0*z0 - x0*i - y0*j)/z0;
				if( sqrt((x0-i)*(x0-i)+(y0-j)*(y0-j)+(z0-z)*(z0-z)) < sqrt(R*R - x0*x0-y0*y0-z0*z0))
					pDC->SetPixel(i+200,j+200, RGB(0,255,0));
			}
		}*/
	scr.Draw(pDC, 10, 10);
}

/////////////////////////////////////////////////////////////////////////////
// CLightView diagnostics

#ifdef _DEBUG
void CLightView::AssertValid() const
{
	CView::AssertValid();
}

void CLightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLightDoc* CLightView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLightDoc)));
	return (CLightDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLightView message handlers

void CLightView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_st = ST_DRAG;
	m_Prev = point;

	CView::OnLButtonDown(nFlags, point);
}

void CLightView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_st == ST_DRAG)
	{
		scr.m_sgm.RotateY(point.x - m_Prev.x);
		scr.m_sgm.RotateX(point.y - m_Prev.y);
		m_Prev= point;
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}

void CLightView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_st = ST_NONE;
	CView::OnLButtonUp(nFlags, point);
}

void CLightView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/*	scr.m_sgm.RotateX(5);
	Invalidate();*/
	CView::OnTimer(nIDEvent);
}

void CLightView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
//	HBRUSH hbr = ::CreateSolidBrush(RGB(0,0,0));
	::SetClassLong(GetSafeHwnd(), GCL_HBRBACKGROUND, (DWORD)NULL);
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(1, 1000, NULL);
}
