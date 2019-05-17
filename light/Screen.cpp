// Screen.cpp: implementation of the CScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "light.h"
#include "Screen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "Segment.h"

CScreen::CScreen(int xres, int yres):
	m_xres(xres),
	m_yres(yres),
	m_albuf(xres, yres),
	m_sgm(CPoint3D(50,30,-20), 120),
	m_light(0.0, 0.0, -100.0),
	m_view(0.0, 0.0, -100.0),
	m_hBmp(NULL)
{
	m_hBmp = (HBITMAP)::LoadImage(	::AfxGetInstanceHandle(), 
									_T("pic.bmp"), IMAGE_BITMAP,
									0, 0, LR_LOADFROMFILE   );
}

CScreen::~CScreen()
{
}

void	CScreen::Draw(CDC* pDC, int x, int y)
{
	CDC memDC, picDC;
	memDC.CreateCompatibleDC(pDC);
	picDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, m_xres, m_yres);
	memDC.SelectObject(&bmp);
/*	CBrush br;
	LOGBRUSH lb;
	lb.lbColor = RGB(0,127,0);
	lb.lbHatch = HS_CROSS;
	lb.lbStyle = BS_HATCHED;
	br.CreateBrushIndirect(&lb);
	memDC.SelectObject(&br);*/
//	memDC.PatBlt(0,0,m_xres, m_yres, SRCCOPY);
	picDC.SelectObject(CBitmap::FromHandle(m_hBmp));
	memDC.BitBlt(0,0,m_xres, m_yres, &picDC, 0, 0, SRCCOPY);
//	memDC.FillRect(CRect(0,0,m_xres, m_yres),&br);
	FillBuffer(0x7F);
	DrawSegment(&memDC);
	pDC->BitBlt(0, 0, m_xres, m_yres, &memDC, x, y, SRCCOPY);
}

void	CScreen::DrawSegment(CDC* pDC)
{
	ArrNormal arr;
	for(int i=0; i<m_xres;i+=1)
		for(int j=0; j<m_yres;j+=1)
		{
		if(	m_sgm.Intersect(CPoint3D(i-m_xres/2,j-m_yres/2, 0), arr))
		{
			for(int k=0;k<arr.size(); k++)
			{
				arr[k].Normalize();
		/*		if(m_albuf(i, j) > arr[k].z)
				{
					m_albuf(i, j) = arr[k].z;
					Color cl = SetColor(arr[k]);
					pDC->SetPixel(i,j, RGB(cl.r , cl.g , cl.b));
				}*/
				Color cl = SetColor(arr[k]);
				pDC->SetPixel(i, j, Blend(pDC, cl, i, j));
			}
		}
		}
	pDC->MoveTo( m_sgm.GetTop(1).x, m_sgm.GetTop(1).y);
	pDC->LineTo( m_sgm.GetTop(1.2).x, m_sgm.GetTop(1.2).y);
}

void	CScreen::FillBuffer(int alpha)
{
	for(int i =0; i < m_xres;i++)
		for( int j=0; j<m_yres; j++)
			m_albuf(i,j) = 50;
}

CScreen::Color	CScreen::SetColor(const CNormal& pt)
{
	Color Ambient  = Color(60,  0, 0,127);
	Color Diffuse  = Color(255, 0, 0,127);
	Color Specular = Color(255, 255, 255,0);
	const double sharp = 50.0;
	double cosa = -pt.GetNormal().z;
	double dc = cosa;
	dc = dc < 0.0?0.0:dc;
	double sc = cosa<0.0?0.0:pow(cosa, sharp);
	sc = sc < 0.0?0.0:sc;
	Diffuse.r *= dc;
	Diffuse.g *= dc;
	Diffuse.b *= dc;
	Diffuse.a *= dc;
	Specular.r *= sc;
	Specular.g *= sc;
	Specular.b *= sc;
	Specular.a *= sc;
	Color cl(	Diffuse.r + Specular.r + Ambient.r,
				Diffuse.g + Specular.g + Ambient.g,
				Diffuse.b + Specular.b + Ambient.b,
				Diffuse.a + Specular.a + Ambient.a);
	cl.Normalize();
	return cl;
}

void CScreen::Color::Normalize()
{
	r = r<0?0:r;
	r = r>255?255:r;
	g = g<0?0:g;
	g = g>255?255:g;
	b = b<0?0:b;
	b = b>255?255:b;
	a = a<0?0:a;
	a = a>255?255:a;
}

COLORREF CScreen::Blend(CDC* pDC, const CScreen::Color& cl, int x, int y)
{
	double c1 = m_albuf(x,y)/double(m_albuf(x,y) + cl.a);
	double c2 = cl.a/double(m_albuf(x,y) + cl.a);
	COLORREF rgb = pDC->GetPixel(x,y);
	Color res(	cl.r*c2 +  c1 * GetRValue(rgb),
				cl.g*c2 +  c1 * GetGValue(rgb),
				cl.b*c2 +  c1 * GetBValue(rgb),
				cl.a*c2 +  c1 * m_albuf(x,y));
	res.Normalize();
	m_albuf(x,y) = res.a;
	return RGB(res.r, res.g, res.b);
}