#pragma once
#include<vector>
#include"Data.h"
class CCalculation
{
public:
	double m_GridLength = 1;
	double m_BaseHeight = 9;
	double m_NerScale = 0.4;
private:
	std::vector<CMyPoint> m_OriPoint;
	std::vector<CLine> m_OutLine;
	std::vector<CGrid> m_Grids;
	std::vector<CGrid> m_ValidGrids;
	std::vector<double> m_Volumes;
	double m_Volume;
	double m_PowerRange;
	CDataRange m_DataRange;
public:
	void ReadData();
private:
	void GetDataRange();
private:
	void GetOutLine();
	void GetFirstLine();
	void GetRestLine();
	CMyPoint GetFirstPoint();
	CLine GetLeftLine(CLine line);
	static bool SortLineInc(CLine& l1,CLine& l2);
private:
	void GetValidGrid();
	bool isValid(CGrid grid);
	bool IsLeft(CMyPoint p, CLine line);
private:
	void GetH();
	std::vector<double> GetGridH(CGrid grid);
	double GetPointH(CMyPoint);

private:
	void GetVolume();
	
private:
public:
	void Calculate();
	std::vector<CLine> OutLine();
	std::vector<double> Volumes();
public:
	CCalculation();
	~CCalculation();
};

