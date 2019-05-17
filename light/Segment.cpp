// Segment.cpp: implementation of the Segment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "light.h"
#include "Segment.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Segment::Segment(CPoint3D cen, double rad):
	m_cir(cen),
	m_cen(0.0,0.0,0.0),
	m_rad(rad)
{

}

Segment::~Segment()
{

}

bool	Segment::Intersect(CPoint3D pt, ArrNormal& arr)
{
	arr.clear();
	bool flag = false; 
	if(sqrt(pt.x*pt.x+pt.y*pt.y)< m_rad)
	{
		double r2 = m_cir.x*m_cir.x + m_cir.y*m_cir.y + m_cir.z*m_cir.z;
		double a  = m_cir.x*pt.x + m_cir.y*pt.y + m_cir.z*sqrt(m_rad*m_rad - pt.x*pt.x - pt.y*pt.y);
		double b  = m_cir.x*pt.x + m_cir.y*pt.y - m_cir.z*sqrt(m_rad*m_rad - pt.x*pt.x - pt.y*pt.y);
		if (a > r2)
		{
			double z = sqrt(m_rad*m_rad - pt.x*pt.x -pt.y*pt.y);
			arr.push_back(CNormal(CPoint3D(pt.x, pt.y, z), CPoint3D(pt.x, pt.y, z)));
			flag = true;
		}
		if (b > r2)
		{
			double z = -sqrt(m_rad*m_rad - pt.x*pt.x - pt.y*pt.y);
			arr.push_back(CNormal(CPoint3D(pt.x, pt.y, z), CPoint3D(pt.x, pt.y, z)));
			flag = true;
		}
		if (m_cir.z != 0.0)
		{
			double z = 	(r2 - m_cir.x*pt.x - m_cir.y*pt.y )/m_cir.z;
			if( sqrt( (m_cir.x - pt.x)*(m_cir.x - pt.x) +
					  (m_cir.y - pt.y)*(m_cir.y - pt.y) +
					  (m_cir.z - z)   *(m_cir.z - z)      ) < 
				sqrt(m_rad*m_rad - r2))
			{
				arr.push_back(CNormal(CPoint3D(pt.x, pt.y, z), /*CPoint3D(-m_cir.x, -m_cir.y, -m_cir.z)*/CPoint3D(pt.x, pt.y, -m_cir.z)));		
				flag = true;
			}
		}
	}
	return flag;
}

void	Segment::RotateX(double ang)
{
	m_cir.RotateX(ang);
}

void	Segment::RotateY(double ang)
{
	m_cir.RotateY(ang);
}

void	Segment::RotateZ(double ang)
{
	m_cir.RotateZ(ang);
}

CPoint3D	Segment::GetTop(double a)
{
	double r = sqrt(m_cir.x*m_cir.x + m_cir.y*m_cir.y + m_cir.z*m_cir.z);
	return CPoint3D( m_rad/r*a*m_cir.x, m_rad/r*a*m_cir.y, m_rad/r*a*m_cir.z); 
}