// Segment.h: interface for the Segment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEGMENT_H__DBB5DE1E_86D1_4088_ACA9_7CBA10ECA1B2__INCLUDED_)
#define AFX_SEGMENT_H__DBB5DE1E_86D1_4088_ACA9_7CBA10ECA1B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point3D.h"
#include <vector>
#include <math.h>

using std::vector;

typedef vector<CNormal> ArrNormal;

class Segment  
{
public:
	Segment(CPoint3D cir, double rad);
	bool		Intersect(CPoint3D pt, ArrNormal& arr);
	virtual		~Segment();
	void		RotateX(double ang);
	void		RotateY(double ang);
	void		RotateZ(double ang);
	CPoint3D	GetTop(double a);
private:
	CPoint3D	m_cen;
	CPoint3D	m_cir;
	double		m_rad;
};

#endif // !defined(AFX_SEGMENT_H__DBB5DE1E_86D1_4088_ACA9_7CBA10ECA1B2__INCLUDED_)
