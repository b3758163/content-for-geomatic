#include "stdafx.h"
#include "Data.h"

bool operator==(CMyPoint & p1, CMyPoint & p2)
{

	return (p1.X() == p2.X() && p1.Y() == p2.Y());
}

bool operator==(CLine & l1, CLine & l2)
{
	return ((l1.OriPoint() == l2.OriPoint()) && (l1.TerPoint() == l2.TerPoint()))
		|| ((l1.OriPoint() == l2.TerPoint()) && (l1.TerPoint() == l2.OriPoint()));

}

CMyPoint::CMyPoint()
{
}

CMyPoint::CMyPoint(double x, double y, double h, CString pointName)
	:m_X(x), m_Y(y), m_H(h), m_PointName(pointName)
{

}

void CMyPoint::SetPoint(double x, double y, double h, CString pointName)
{
	m_X = x;
	m_Y = y;
	m_H = h;
	m_PointName = pointName;
}

double CMyPoint::X()
{
	return m_X;
}

double CMyPoint::Y()
{
	return m_Y;
}

double CMyPoint::H()
{
	return m_H;
}

double CMyPoint::GetDistance(CMyPoint p)
{
	double deltaX = p.X() - m_X;
	double deltaY = p.Y() - m_Y;
	return sqrt(deltaX*deltaX + deltaY + deltaY);
}

CString CMyPoint::PointName()
{
	return m_PointName;
}

CLine::CLine()
{

}

CLine::CLine(CMyPoint oriPoint, CMyPoint terPoint)
{
	SetLine(oriPoint, terPoint);
}

void CLine::SetLine(CMyPoint oriPoint, CMyPoint terPoint)
{
	double Epc = 0.000001;
	double deltaX, deltaY;
	double angle;
	m_OriPoint = oriPoint;
	m_TerPoint = terPoint;
	deltaX = terPoint.X() - oriPoint.X();
	deltaY = terPoint.Y() - oriPoint.Y();
	angle = atan(fabs(deltaY / deltaX));
	if		  (fabs(deltaY) < Epc&&deltaX > 0)
		m_Azimuth = 0;
	else if (fabs(deltaY) < Epc&&deltaX < 0)
		m_Azimuth = PI;
	else if (fabs(deltaX) < Epc&&deltaY > 0)
		m_Azimuth = PI / 2;
	else if (fabs(deltaX) < Epc&&deltaY < 0)
		m_Azimuth = PI * 3 / 2;
	else if (deltaX > 0 && deltaY > 0)
		m_Azimuth = angle;
	else if (deltaX > 0 && deltaY < 0)
		m_Azimuth = 2 * PI - angle;
	else if (deltaX < 0 && deltaY>0)
		m_Azimuth = PI - angle;
	else if (deltaX < 0 && deltaY < 0)
		m_Azimuth = angle + PI;
	if (fabs(deltaX) < Epc)
		IsVertical = true;
	else
	{
		m_Slope = deltaY / deltaX;
		m_Intercept = oriPoint.Y() - m_Slope*oriPoint.X();
	}

}

double CLine::Azimuth()
{
	return m_Azimuth;
}

double CLine::Slope()
{
	return m_Slope;
}

double CLine::Intercept()
{
	return m_Intercept;
}

CMyPoint CLine::OriPoint()
{
	return m_OriPoint;
}

CMyPoint CLine::TerPoint()
{
	return m_TerPoint;
}

CGrid::CGrid()
{
}

CGrid::CGrid(CMyPoint bottomLeft, double gridLength)
	:m_BottomLeft(bottomLeft), m_GridLength(gridLength)
{

}

CGrid::~CGrid()
{
}

void CGrid::SetH(std::vector<double> h)
{
	m_H = h;
}

double CGrid::GetVolume(double baseHeight)
{
	double volume;
	int count = m_H.size();
	int i = 0;
	double H = 0;
	for (i = 0;i < count;i++)
	{
		H += m_H[i];
	}
	H = H / count;
	H -= baseHeight;
	volume = H*m_GridLength*m_GridLength;
	return volume;
}

CMyPoint CGrid::CentPoint()
{
	return CMyPoint(m_BottomLeft.X() + 0.5*m_GridLength, m_BottomLeft.Y() + 0.5*m_GridLength);
}

std::vector<CMyPoint> CGrid::GetGridPoint()
{
	double x = m_BottomLeft.X();
	double y = m_BottomLeft.Y();
	std::vector<CMyPoint>points;
	points.push_back(m_BottomLeft);
	points.push_back(CMyPoint(x, y + m_GridLength));
	points.push_back(CMyPoint(x + m_GridLength, y));
	points.push_back(CMyPoint(x + m_GridLength, y + m_GridLength));
	return points;
}

CDataRange::CDataRange()
{

}

CDataRange::CDataRange(CMyPoint bottomLeft, double width, double length, double gridLength)

{
	SetRange(bottomLeft, width, length, gridLength);
}

void CDataRange::SetRange(double minX, double minY, double maxX, double maxY, double GridLength)
{
	CMyPoint bottomLeft(minX, minY);
	double width = maxX - minX;
	double length = maxY - minY;
	SetRange(bottomLeft, width, length, GridLength);
}

void CDataRange::SetRange(CMyPoint bottomLeft, double width, double length, double gridLength)
{
	m_Width = width;
	m_Length = length;
	m_BottomLeft = bottomLeft;
	m_GridLength = gridLength;
	m_XCount = (int)(width / gridLength) + 1;
	m_YCount = (int)(length / gridLength) + 1;
}

std::vector<CGrid> CDataRange::GetGrid()
{
	std::vector<CGrid> grids;
	double x = m_BottomLeft.X();
	double y = m_BottomLeft.Y();
	int i = 0, j = 0;
	for (i = 0;i < m_XCount;i++)
	{
		for (j = 0;j < m_YCount;j++)
		{
			grids.push_back(CGrid(CMyPoint(x+i*m_GridLength,y+j*m_GridLength),m_GridLength));
		}
	}
	return grids;
}

double CDataRange::Length()
{
	return m_Length;
}

double CDataRange::Width()
{
	return m_Width;
}

int CDataRange::XCount()
{
	return m_XCount;
}

int CDataRange::YCount()
{
	return m_YCount;
}

int CDataRange::GetGridCount()
{
	return m_XCount*m_YCount;
}
