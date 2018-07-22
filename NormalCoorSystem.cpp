#include "stdafx.h"
#include "CoorSystem.h"

CCoorSystem * CCoorSystem:: m_pInstance = new CCoorSystem();

CCoorSystem::CCoorSystem()
{
}


CCoorSystem::~CCoorSystem()
{
}

CString CListUpdate::GetString(double num)
{
	CString strNum;
	strNum.Format(L"%f",num);
	return strNum;
}

void CListUpdate::Update(CListCtrl & listCtrl, std::vector<CDataPoint> data, bool bClear)
{
	int count = data.size();
	int i = 0;
	int row = 0;
	if (bClear == true)
	{
		listCtrl.DeleteAllItems();
	}
	for (i = 0;i < count;i++)
	{
		row = listCtrl.GetItemCount();
		listCtrl.InsertItem(row,data[i].strID);
		listCtrl.SetItemText(row, 1,GetString(data[i].m_X));
		listCtrl.SetItemText(row, 2, GetString(data[i].m_Y));
		listCtrl.SetItemText(row, 3, GetString(data[i].m_Z));
		listCtrl.SetItemText(row, 4, GetString(data[i].m_B));
		listCtrl.SetItemText(row, 5, GetString(data[i].m_L));
		listCtrl.SetItemText(row, 6, GetString(data[i].m_H));
	}
}

CCoorPoint::CCoorPoint(double x, double y, CString pointName)
{
	SetPoint(x,y,pointName);
}

void CCoorPoint::SetPoint(double x, double y, CString pointName)
{
	m_X = x;
	m_Y = y;
	m_PointName = pointName;
}

void CCoorPoint::Move(double x, double y)
{
	m_X += x;
	m_Y += y;

}

double CCoorPoint::X()
{
	return m_X;
}

double CCoorPoint::Y()
{
	return m_Y;
}

CString CCoorPoint::PointName()
{
	return m_PointName;
}

void CCoorSystem::InitialData()
{

	double minX, minY, maxX, maxY;
	int count = m_PaintData.size();
	int i = 0;
	if (count > 0)
	{
		minX = m_PaintData[i].X();
		minY = m_PaintData[i].Y();
		maxX = minX;
		maxY = minY;
	}
	for (i = 0;i < count;i++)
	{
		if (m_PaintData[i].X() < minX)
		{
			minX = m_PaintData[i].X();
		}
		else if (m_PaintData[i].X() > maxX)
		{
			maxX = m_PaintData[i].X();
		}
		if (m_PaintData[i].Y() < minY)
		{
			minY = m_PaintData[i].Y();
		}
		else if (m_PaintData[i].Y() > maxY)
		{
			maxY = m_PaintData[i].Y();
		}
	}
	m_Width = maxX - minX;
	m_Length = maxY - minY;
	m_DCP.SetPoint((minX+maxX)/2,(minY + maxY)/2);
	m_BTL.SetPoint(minX,minY);
}

void CCoorSystem::SetData(std::vector<CDataPoint> data)
{
	
	int count = data.size();
	int i = 0;
	m_PaintData.clear();
	for (i = 0;i < count;i++)
	{
		m_PaintData.push_back(CCoorPoint(data[i].m_X,data[i].m_Y,data[i].strID));
	}
	InitialData();
}

void CCoorSystem::CoorMove(int x, int y, int nFlags)
{
	double dX, dY;
	if (nFlags == 1)
	{
		dX = (x - m_MPS.X())*m_Wheel*m_Scale;
		dY = (y - m_MPS.Y())*m_Wheel*m_Scale;
		m_DCP.Move(-dX, dY);
	}
	m_MPS.SetPoint(x, y);
}

void CCoorSystem::SetScreen(int x, int y)
{
	double XScale, YScale;
	m_SCP.SetPoint(x / 2, y / 2);
	XScale = m_Width / x;
	YScale = m_Length / y;
	if (XScale > YScale)
		m_Scale = XScale;
	else
		m_Scale = YScale;
}

void CCoorSystem::Wheel(int zDelta)
{
	m_Wheel *= (1.0 - 0.2*zDelta / 120);
}

double CCoorSystem::PX(double x)
{
	return (x-m_DCP.X())/m_Scale/m_Wheel + m_SCP.X();
}

double CCoorSystem::PY(double y)
{
	return (m_DCP.Y() - y)/m_Wheel/m_Scale + m_SCP.Y();
}
double CCoorSystem::DX(double x)
{
	return PX(x);
}
double CCoorSystem::DY(double y)
{
	return (y - m_DCP.Y())/m_Wheel/m_Scale + m_SCP.Y();
}

CString CCoorSystem::GetString(double num)
{
	CString strNum;
	strNum.Format(L"%f",num);
	return strNum;
}

void CCoorSystem::Initial()
{
	m_GridLength = m_Length / m_XCount;
	m_GridWidth = m_Width / m_YCount;
}

void CCoorSystem::DrawPaint(CDC * dc)
{
	m_pDc = dc;
	Initial();
	PAxis();
	PPoint();
}

void CCoorSystem::PAxis()
{
	double x, y;
	int i;
	//X
	x = PX(m_BTL.X());
	y = PY(m_BTL.Y());
	m_pDc->MoveTo(x, y);
	x = PX(m_BTL.X() + m_Width);
	m_pDc->LineTo(x, y);
	for (i = 0;i < m_XCount;i++)
	{
		x = PX(m_BTL.X() + i*m_GridWidth);
		y = PY(m_BTL.Y());
		m_pDc->MoveTo(x, y);
		y += 5;
		m_pDc->LineTo(x, y);
		m_pDc->DrawTextW(GetString(m_PaintData[i].X()), CRect(x - 40, y, x+40, y + 20), 0);
	}
	//Y
	x = PX(m_BTL.X());
	y = PY(m_BTL.Y());
	m_pDc->MoveTo(x, y);
	y = PY(m_BTL.Y() + m_Length);
	m_pDc->LineTo(x, y);
	for (i = 0;i < m_XCount;i++)
	{
		x = PX(m_BTL.X() );
		y = PY(m_BTL.Y()+i* m_GridLength);
		m_pDc->MoveTo(x, y);
		x -= 5;
		m_pDc->LineTo(x, y);
		m_pDc->DrawTextW(GetString(m_PaintData[i].Y()),CRect(x-80,y,x,y+20),0);
	}
}

void CCoorSystem::PPoint()
{
	double x, y;
	int count = m_PaintData.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		x = PX(m_PaintData[i].X());
		y = PY(m_PaintData[i].Y());
		m_pDc->Rectangle(x-2,y-2,x+2,y+2);
		m_pDc->DrawTextW(m_PaintData[i].PointName(), CRect(x, y, x + 100, y + 30),0);

	}
}
