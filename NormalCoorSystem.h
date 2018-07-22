#pragma once
#include <vector>
#include "DataPoint.h"
//坐标点，在坐标系中用到的点
class CCoorPoint
{
private:
	double m_X, m_Y;
	CString m_PointName;
public:
	CCoorPoint(double x =0, double y = 0, CString pointName = L"NNAME");
	void SetPoint(double x=0, double y=0,CString pointName = L"NNAME");
	void Move(double x, double y);
public:
	double X();
	double Y();
	CString PointName();
};
//坐标系统，用于绘制界面中的图形和dxf图形的坐标转换系统
class CCoorSystem
{
private:
	CCoorPoint m_BTL;
	CCoorPoint m_DCP;
	CCoorPoint m_SCP;
	CCoorPoint m_MPS;
	std::vector<CCoorPoint> m_PaintData;
	double m_Width;
	double m_Length;
	double m_Scale;
	double m_Wheel=1.4;
	void InitialData();
public:
	void SetData(std::vector<CDataPoint> data);
	void CoorMove(int x, int y, int nFlags);
	void SetScreen(int x, int y);
	void Wheel(int zDelta);
private:
	double PX(double x);
	double PY(double y);
	double DX(double x);
	double DY(double y);
	CString GetString(double num);
	//绘制界面图形部分
private:
	CDC *m_pDc;
	int m_XCount = 8;
	int m_YCount = 8;
	double m_GridLength;
	double m_GridWidth;
	void Initial();
public:
	void DrawPaint(CDC *dc);
private:
	void PAxis();
	void PPoint();
	//绘制DXF图形部分
private:
public:
private:

private:
	static CCoorSystem * m_pInstance;
	CCoorSystem();
	~CCoorSystem();
public:
	static CCoorSystem* GetInstance()
	{
		return m_pInstance;
	}
};

class CListUpdate
{
private:
	CString GetString(double num);
public:
	void Update(CListCtrl &listCtrl, std::vector<CDataPoint> data, bool bClear);
};