#include "stdafx.h"
#include "DataPoint.h"


CDataPoint::CDataPoint()
{
}

CDataPoint::CDataPoint(double x, double y, double h, CString pointName)
{
	SetPoint(x, y, h, pointName);
}

void CDataPoint::SetPoint(double x, double y, double h, CString pointName)
{
	m_X = x;
	m_Y = y;
	m_H = h;
	m_PointName = pointName;
}


CDataPoint::~CDataPoint()
{
}

double CDataPoint::X()
{
	return m_X;
}

double CDataPoint::Y()
{
	return m_Y;
}

double CDataPoint::H()
{
	return m_H;
}

CString CDataPoint::PointName()
{
	return m_PointName;
}

double CDataPoint::Distance(CDataPoint point)
{
	double x1, x2, y1, y2;
	double distance;
	x1 = this->m_X;
	y1 = this->m_Y;
	x2 = point.X();
	y2 = point.Y();
	distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return distance;
}

bool operator==(CDataPoint p1, CDataPoint p2)
{
	if ((fabs(p1.X() - p2.X()) < EPC) && (fabs(p1.Y() - p2.Y()) <= EPC))
		return true;
	else
		return false;
}

bool operator==(CLine l1, CLine l2)
{
	if ((l1.OriPoint() == l2.OriPoint() && l1.TerPoint() == l2.TerPoint()) ||
		(l1.OriPoint() == l2.TerPoint() && l1.TerPoint() == l2.OriPoint()))
		return true;
	else
		return false;
}

CLine::CLine()
{
}

CLine::CLine(CDataPoint oriPoint, CDataPoint terPoint)
{
	SetLine(oriPoint, terPoint);
}

void CLine::SetLine(CDataPoint oriPoint, CDataPoint terPoint)
{
	m_OriPoint = oriPoint;
	m_TerPoint = terPoint;
}

CDataPoint CLine::OriPoint()
{
	return m_OriPoint;
}

CDataPoint CLine::TerPoint()
{
	return m_TerPoint;
}

CDataPoint CTriangle::P1()
{
	return m_P1;
}

CDataPoint CTriangle::P2()
{
	return m_P2;
}

CDataPoint CTriangle::P3()
{
	return m_P3;
}

CLine CTriangle::L1()
{
	return m_L1;
}

CLine CTriangle::L2()
{
	return m_L2;
}

CLine CTriangle::L3()
{
	return m_L3;
}

CTriangle::CTriangle()
{

}

CTriangle::CTriangle(CDataPoint p1, CDataPoint p2, CDataPoint p3)
{
	SetTriangle(p1, p2, p3);
}

CTriangle::CTriangle(CLine line, CDataPoint p1)
{
	SetTriangle(line, p1);
}

void CTriangle::SetTriangle(CDataPoint p1, CDataPoint p2, CDataPoint p3)
{
	m_P1 = p1;
	m_P2 = p2;
	m_P3 = p3;
	m_L1.SetLine(p1, p2);
	m_L2.SetLine(p1, p3);
	m_L3.SetLine(p2, p3);
	GetCR(p1, p2, p3);
}

void CTriangle::SetTriangle(CLine line, CDataPoint p1)
{
	SetTriangle(line.OriPoint(), line.TerPoint(), p1);
}

double CTriangle::GetVolume(double baseHeight)
{
	double volume;
	double S;
	double h;
	double x1, x2, x3, y1, y2, y3;
	x1 = m_P1.X();
	x2 = m_P2.X();
	x3 = m_P3.X();
	y1 = m_P1.Y();
	y2 = m_P2.Y();
	y3 = m_P3.Y();
	S = abs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1)) / 2;
	h = (m_P1.H() + m_P2.H() + m_P3.H()) / 3 - baseHeight;
	volume = S*h;
	return volume;
}

void CTriangle::GetCR(CDataPoint p1, CDataPoint p2, CDataPoint p3)
{
	double x1, x2, x3, y1, y2, y3;
	double x, y, r;
	x1 = p1.X();
	x2 = p2.X();
	x3 = p3.X();
	y1 = p1.Y();
	y2 = p2.Y();
	y3 = p3.Y();
	//
	x = ((y2 - y1)*(y3*y3 - y1*y1 + x3*x3 - x1*x1) - (y3 - y1)*(y2*y2 - y1*y1 + x2*x2 - x1*x1)) / (2 * (x3 - x1)*(y2 - y1) - 2 * (x2 - x1)*(y3 - y1));
	y = ((x2 - x1)*(x3*x3 - x1*x1 + y3*y3 - y1*y1) - (x3 - x1)*(x2*x2 - x1*x1 + y2* y2 - y1*y1)) / (2 * (y3 - y1)*(x2 - x1) - 2 * (y2 - y1)*(x3 - x1));
	r = sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1));
	m_Center.SetPoint(x, y);
	m_R = r;
}

bool CTriangle::IsInfluence(CDataPoint point)
{
	if (m_Center.Distance(point) > m_R)
		return false;
	else
 		return true;
}

bool CTriangle::ContainPoint(std::vector<CString> Names)
{
	int count = Names.size();
	int i = 0;
	int num = 0;
	for (i = 0;i < count;i++)
	{
		if (m_P1.PointName() == Names[i])
		{
			num++;
		}
		else if (m_P2.PointName() == Names[i])
		{
			num++;
		}
		else if(m_P3.PointName() == Names[i])
		{
			num++;
		}
	}
	if (num > 0)
		return true;
	else
		return false;
}
