// Screen.h: interface for the CScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREEN_H__33A24C5C_DDCD_4E42_BD70_88711475907C__INCLUDED_)
#define AFX_SCREEN_H__33A24C5C_DDCD_4E42_BD70_88711475907C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Segment.h"
#include "templ.h"

class CScreen/* : CDC */
{
public:
	CScreen(int xres, int yres);
	void	Draw(CDC* pDC, int x, int y);
	virtual ~CScreen();

private:
	struct		Color
	{
		Color():
			r(0), g(0), b(0), a(0) {};
		Color(int cr, int cg, int cb, int ca):
			r(cr), g(cg), b(cb), a(ca) {};
		Color(int cr, int cg, int cb):
			r(cr), g(cg), b(cb), a(0xFF) {};
		void	Normalize();
		int		r,g,b,a;
	};
	void		DrawSegment(CDC* pDC);
	void		FillBuffer(int alpha);
	Color		SetColor(const CNormal& pt);
	COLORREF	Blend(CDC* pDC, const Color& cl, int x, int y);

private:
	int				m_xres;
	int				m_yres;
	CPoint3D		m_light;
	CPoint3D		m_view;
	
//	CBitmap bmp;
	
	Array2D<int>	m_albuf;
	HBITMAP			m_hBmp;
public:
	Segment			m_sgm;
};

#endif // !defined(AFX_SCREEN_H__33A24C5C_DDCD_4E42_BD70_88711475907C__INCLUDED_)
