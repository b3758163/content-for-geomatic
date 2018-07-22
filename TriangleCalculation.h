#pragma once
#include <vector>
#include <algorithm>
#include "DataPoint.h"
class CCalculation
{
public:
	std::vector<CDataPoint> m_OriPoint;
	std::vector<CTriangle> m_T1;
	std::vector<double> m_Volumes;
	double m_Volume;
	double m_BaseHeight = 9;
private:
	std::vector<CTriangle> m_T2;
	std::vector<CLine> m_L1;
	
private:
	//获取数据
	bool ReadData();
private:
	void GetOriTriangle();
private:	
	void GetTriangle();
	void GetinfTri(CDataPoint point);
	void GetLine();
	void DeleteLine();
	void GetNewTri(CDataPoint point);
	int SameCount(CLine line);
private:
	void DeleteOutLine();
private:
	void GetVolume();
private:
	void SortVolume();
	static bool sortAddin(double a, double b);
public:
	void Calculate();

public:
	CCalculation();
	~CCalculation();
};

