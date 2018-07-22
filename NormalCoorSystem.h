#pragma once
#include <vector>
#include "DataPoint.h"
//����㣬������ϵ���õ��ĵ�
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
//����ϵͳ�����ڻ��ƽ����е�ͼ�κ�dxfͼ�ε�����ת��ϵͳ
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
	//���ƽ���ͼ�β���
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
	//����DXFͼ�β���
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