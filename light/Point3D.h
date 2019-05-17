// Point3D.h: interface for the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT3D_H__85CB5776_921D_45C2_B48C_037C2C550828__INCLUDED_)
#define AFX_POINT3D_H__85CB5776_921D_45C2_B48C_037C2C550828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

class CPoint3D  
{
public:
	CPoint3D(double ptx, double pty, double ptz);
	virtual ~CPoint3D();
	void	RotateX(double ang);
	void	RotateY(double ang);
	void	RotateZ(double ang);
	double x,y,z;
};

class CNormal: public CPoint3D  
{
public:
	CNormal(CPoint3D pt, CPoint3D norm);
	CPoint3D GetNormal() const { return m_norm; };
	void	Normalize();
	virtual ~CNormal();

private:
	CPoint3D m_norm;
};

#endif // !defined(AFX_POINT3D_H__85CB5776_921D_45C2_B48C_037C2C550828__INCLUDED_)
