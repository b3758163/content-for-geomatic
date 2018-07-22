#pragma once
#include<vector>
#include<cmath>
#define PI 3.1415926535
class CMyPoint;
class CLine;
class CGrid;
class CDataRange;
bool operator==(CMyPoint& p1,  CMyPoint& p2);
bool operator==(CLine& l1, CLine&l2);

class CMyPoint
{
	friend bool operator==(CMyPoint& p1,  CMyPoint& p2);
private:
	double m_X, m_Y, m_H;
	CString m_PointName;
public:
	CMyPoint();
	CMyPoint(double x, double y, double h = 0, CString pointName = L"NNAME");
	void SetPoint(double x, double y, double h = 0, CString pointName = L"NNAME");
public:
	double X();
	double Y();
	double H();
	double GetDistance(CMyPoint p);
	CString PointName();
};

class CLine
{
	friend bool operator==(CLine &l1, CLine &l2);
private:
	CMyPoint m_OriPoint, m_TerPoint;
	double m_Azimuth;
	double m_Slope, m_Intercept;
	bool IsVertical;
public:
	CLine();
	CLine(CMyPoint oriPoint, CMyPoint terPoint);
	void SetLine(CMyPoint oriPoint, CMyPoint terPoint);
public:
	double Azimuth();
	double Slope();
	double Intercept();
	CMyPoint OriPoint();
	CMyPoint TerPoint();
};

class CGrid
{
protected:
	CMyPoint m_BottomLeft;
private:
	double m_GridLength;
	std::vector<double> m_H;
public:
	CGrid();
	CGrid(CMyPoint bottomLeft, double gridLength);
	~CGrid();
	void SetH(std::vector<double> h);
	double GetVolume(double baseHeight);
	CMyPoint CentPoint();
	std::vector<CMyPoint> GetGridPoint();
};

class CDataRange :public CGrid
{
private:
	double m_Length;
	double m_Width;
	double m_GridLength;
	int m_XCount;
	int m_YCount;
public:
	CDataRange();
	CDataRange(CMyPoint bottomLeft, double width, double length,double gridLength);
	void SetRange(double minX, double minY, double maxX, double maxY, double GridLength);
	void SetRange(CMyPoint bottomLeft,double width, double length, double gridLength);
public:
	std::vector<CGrid> GetGrid();
public:
	double Length();
	double Width();
	int XCount();
	int YCount();
	int GetGridCount();

};