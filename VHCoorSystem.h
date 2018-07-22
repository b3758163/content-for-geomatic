#pragma once
#include <vector>
#include "DXf.h"
#include "Calculation.h"
#include "CoorSystem.h"
using namespace std;
class CCoorPoint
{
public:
	double m_X, m_Y;
	CString m_PointName;
public:
	CCoorPoint();
	CCoorPoint(double x, double y ,CString pointName = L"NNAME");
	void SetPoint(double x, double y ,CString pointName = L"NNAME");
};
class CScale
{
public:
	CCoorPoint m_BTL;
	CCoorPoint m_DCP;
	CCoorPoint m_SCP;
	CString m_Title;
	double m_XScale;
	double m_YScale;
	bool b_SMark = false;
	double m_Width;
	double m_Length;
	double m_YAdd = 0;
	int m_Rows;
	int m_RowCount;
public:
	vector<vector<CCoorPoint>>m_LineData;
	vector<vector<CCoorPoint>> m_PointData;
public:
	void SetData(
		vector<vector<CCoorPoint>> LinePoint, 
		vector<vector<CCoorPoint>> PointData,
		int rows, 
		int count,
		CString Title=L"NNAME",
		int XCount= 8, 
		int YCount = 8
	);
	void SetScreen(int x, int y);
private:
	double PX(double x);
	double PY(double y);
	double DX(double x);
	double DY(double y);
	CString GetString(double num);
public:
	void PDraw(CDC * dc);
	void DDraw(CDxf dxf);
private:
	CDC * m_pDc;
	CDxf m_Dxf ;
private:
	double m_GridLength;
	double m_GridWidth;
	int m_XCount = 8;//加参数设置方格总数
	int m_YCount = 8;
	void Initial();
private://PDraw();
	void PInitial(CDC *dc);
	void PAxis();
	void PLine();
	void PPoint();
private:
	void DBegin(CDxf dxf);
	void DAxis();
	void DLine();
	void DPoint();
	void DEnd();

};

class CCoorSystem
{

private:
	CScale m_RoadS;
	CScale m_VScale;
	CScale m_HScale;
public:
	vector<CDataPoint> m_RoadData = {};
	vector<CDataPoint> m_VData = {};
	vector<CDataPoint> m_HData1 = {};
	vector<CDataPoint> m_HData2 = {};
	vector<CDataPoint> m_KnowData = {};
public:
	void SetVData();
	void SetHData();
	void SetRData();

	void SetData(
		std::vector<CDataPoint>m_RoadData,
		std::vector<CDataPoint>m_KnowData,
		std::vector<CDataPoint>m_VData,
		std::vector<CDataPoint>m_HData1,
		std::vector<CDataPoint>m_HData2
	);
	void SetScreen(int x, int y);
public:
	void PDraw(CDC *dc);
	void DDraw();
private:
	static CCoorSystem *m_pInstance; 
	CCoorSystem();
	~CCoorSystem();
public:
	static CCoorSystem* GetInstance()
	{
		return m_pInstance;
	}
};

class ListUpdate
{
private:
	CString GetString(double num);
public:
	void Update(CListCtrl &listCtrl, std::vector<std::vector<CDataPoint>> data);
};
