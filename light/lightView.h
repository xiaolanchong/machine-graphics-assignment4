// lightView.h : interface of the CLightView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHTVIEW_H__A26DEFFB_DA81_4EFD_AFB3_1ECAA598930F__INCLUDED_)
#define AFX_LIGHTVIEW_H__A26DEFFB_DA81_4EFD_AFB3_1ECAA598930F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Screen.h"

class CLightView : public CView
{
protected: // create from serialization only
	CLightView();
	DECLARE_DYNCREATE(CLightView)

// Attributes
public:
	CLightDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	enum STATE { ST_NONE, ST_DRAG };
	virtual ~CLightView();

	CScreen scr;
	STATE	m_st;
	CPoint  m_Prev;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLightView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in lightView.cpp
inline CLightDoc* CLightView::GetDocument()
   { return (CLightDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTVIEW_H__A26DEFFB_DA81_4EFD_AFB3_1ECAA598930F__INCLUDED_)
