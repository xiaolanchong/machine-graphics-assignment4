// Point3D.cpp: implementation of the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "light.h"
#include "Point3D.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const double PI = 3.14159265359;

CPoint3D::CPoint3D(double ptx, double pty, double ptz):
	x(ptx),y(pty),z(ptz)
{

}

CPoint3D::~CPoint3D()
{

}


void	CPoint3D::RotateZ(double ang)
{
	ang = PI* ang/180.0;
	double xp = x, yp = y;
	x = cos(ang)*xp - sin(ang)*yp;
	y = sin(ang)*xp + cos(ang)*yp;
}

void	CPoint3D::RotateY(double ang)
{
	ang = PI* ang/180.0;
	double xp = x, zp = z;
	x = cos(ang)*xp - sin(ang)*zp;
	z = sin(ang)*xp + cos(ang)*zp;
}

void	CPoint3D::RotateX(double ang)
{
	ang = PI* ang/180.0;
	double yp = y, zp = z;
	y = cos(ang)*yp - sin(ang)*zp;
	z = sin(ang)*yp + cos(ang)*zp;
}

CNormal::CNormal(CPoint3D pt, CPoint3D norm) : 
	CPoint3D(pt.x, pt.y, pt.z),
	m_norm(norm.x, norm.y, norm.z)
{

}

CNormal::~CNormal()
{

}

void	CNormal::Normalize()
{
	double a = sqrt(m_norm.x * m_norm.x + m_norm.y *m_norm.y +m_norm.z* m_norm.z);
	m_norm.x /= a;
	m_norm.y /= a;
	m_norm.z /= a;
}