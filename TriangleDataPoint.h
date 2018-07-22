#pragma once
#include <vector>
const double EPC = 0.000001;
class CLine;
class CDataPoint;
bool operator==(CDataPoint p1,CDataPoint p2);
bool operator==(CLine p1, CLine p2);
class CDataPoint
{
	friend bool operator==(CDataPoint p1, CDataPoint p2);
private:
	double m_X, m_Y, m_H;
	CString m_PointName;
public:
	CDataPoint();
	CDataPoint(double x, double y,double h = 0 , CString pointName = L"NNAME");
	void SetPoint(double x, double y, double h = 0, CString pointName = L"NNAME");
	~CDataPoint();
public:
	double X();
	double Y();
	double H();
	CString PointName();
	double Distance(CDataPoint point);
};

class CLine
{
	friend bool operator==(CLine p1, CLine p2);
private:
	CDataPoint m_OriPoint, m_TerPoint;
public:
	CLine();
	CLine(CDataPoint oriPoint, CDataPoint terPoint);	
	void SetLine(CDataPoint oriPoint, CDataPoint terPoint);
public:
	CDataPoint OriPoint();
	CDataPoint TerPoint();
};

class CTriangle
{
private:
	CDataPoint m_P1, m_P2, m_P3;
	CLine m_L1, m_L2, m_L3;
	CDataPoint m_Center;
	double m_R;
public:
	CDataPoint P1();
	CDataPoint P2();
	CDataPoint P3();
	CLine L1();
	CLine L2();
	CLine L3();
public:
	CTriangle();
	CTriangle(CDataPoint p1, CDataPoint p2, CDataPoint p3);
	CTriangle(CLine line,CDataPoint p1);
	void SetTriangle(CDataPoint p1, CDataPoint p2, CDataPoint p3);
	void SetTriangle(CLine line, CDataPoint p1);
	double GetVolume(double baseHeight);
private:
	void GetCR(CDataPoint p1,CDataPoint p2,CDataPoint p3);
public:
	bool IsInfluence(CDataPoint point);
	bool ContainPoint(std::vector<CString> Names);
};
