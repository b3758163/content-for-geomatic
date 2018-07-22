#include "stdafx.h"
#include "CoorSystem.h"


CCoorSystem* CCoorSystem::m_pInstance = new CCoorSystem();
void CCoorSystem::SetRData()
{
	vector<vector<CCoorPoint>> LineData;
	vector<vector<CCoorPoint>> PointData;
	vector<CCoorPoint> PartData;
	int i, n;
	//µã²¿·Ö
	n = m_RoadData.size();
	PartData.clear();
	for (i = 0;i < n;i++)
	{
		PartData.push_back(CCoorPoint(
			m_RoadData[i].m_x, m_RoadData[i].m_y, m_RoadData[i].strID
		));
	}
	PointData.push_back(PartData);
	PartData.clear();

	n = m_KnowData.size();
	for (i = 0;i < n;i++)
	{
		PartData.push_back(CCoorPoint(
			m_KnowData[i].m_x, m_KnowData[i].m_y, m_KnowData[i].strID
		));
	}
	PointData.push_back(PartData);
	PartData.clear();
	//line part
	n = m_KnowData.size();
	for (i = 0;i < n;i++)
	{
		PartData.push_back(CCoorPoint(
			m_KnowData[i].m_x,
			m_KnowData[i].m_y,
			m_KnowData[i].strID
		));
	}
	LineData.push_back(PartData);
	PartData.clear();

	n = m_HData1.size();
	if (n > 0)
	{
		PartData.push_back(CCoorPoint(m_HData1[0].m_x, m_HData1[0].m_y, m_HData1[0].strID));
		PartData.push_back(CCoorPoint(m_HData1[n-1].m_x, m_HData1[n-1].m_y, m_HData1[n-1].strID));
	}
	LineData.push_back(PartData);
	PartData.clear();

	n = m_HData2.size();
	if (n > 0)
	{
		PartData.push_back(CCoorPoint(m_HData2[0].m_x, m_HData2[0].m_y, m_HData2[0].strID));
		PartData.push_back(CCoorPoint(m_HData2[n - 1].m_x, m_HData2[n - 1].m_y, m_HData2[n - 1].strID));
	}
	LineData.push_back(PartData);
	PartData.clear();

	/*n = m_VData.size();
	if (n > 0)
	{
		PartData.push_back(CCoorPoint(m_VData[0].m_x, m_VData[0].m_y, m_VData[0].strID));
		PartData.push_back(CCoorPoint(m_VData[n - 1].m_x, m_VData[n - 1].m_y, m_VData[n - 1].strID));
	}
	LineData.push_back(PartData);
	PartData.clear();*/
	m_RoadS.SetData(LineData, PointData, 0, 3, L"Road",6,4);//
}

void CCoorSystem::SetHData()
{
	vector<vector<CCoorPoint>> LineData;
	vector<vector<CCoorPoint>> PointData;
	vector<CCoorPoint> PartData;

	int i,n;
	n = m_HData1.size();
	for (i = 0;i < n;i++)
	{
		PartData.push_back(CCoorPoint(
			i,
			m_HData1[i].m_h,
			m_HData1[i].strID
			));
	}
	LineData.push_back(PartData);
	PartData.clear();

	n = m_HData2.size();
	for (i = 0;i < n;i++)
	{
		PartData.push_back(
			CCoorPoint(
			i,
			m_HData2[i].m_h,
			m_HData2[i].strID
			)
		);
	}
	LineData.push_back(PartData);
	m_HScale.SetData(LineData,PointData,2,3 ,L"Horizental",5,5);
}

void CCoorSystem::SetVData()
{
	vector<vector<CCoorPoint>> LineData;
	vector<vector<CCoorPoint>> PointData;
	vector<CCoorPoint> PartData;

	int i, n;
	n = m_VData.size();
	for (i = 0;i < n;i++)
	{
		PartData.push_back(
			CCoorPoint(
				i,
				m_VData[i].m_h,
				m_VData[i].strID
		)
		);
	}
	LineData.push_back(PartData);

	m_VScale.SetData(LineData,PointData,1,3,L"Vertical",5,5);
}

void CCoorSystem::SetData(
	std::vector<CDataPoint> RoadData, 
	std::vector<CDataPoint> KnowData,
	std::vector<CDataPoint> VData, 
	std::vector<CDataPoint> HData1, 
	std::vector<CDataPoint> HData2
)
{
	m_RoadData = RoadData;
	m_KnowData = KnowData;
	m_VData = VData;
	m_HData1 = HData1;
	m_HData2 = HData2;
	SetVData();
	SetHData();
	SetRData();
 }

void CCoorSystem::SetScreen(int x, int y)
{
	m_HScale.SetScreen(x,y);
	m_VScale.SetScreen(x,y);
	m_RoadS.SetScreen(x,y);
}


void CCoorSystem::PDraw(CDC * dc)
{
	m_RoadS.PDraw(dc);
	m_VScale.PDraw(dc);
	m_HScale.PDraw(dc);

}

void CCoorSystem::DDraw()
{
	CDxf dxf;
	dxf.begin();
	m_RoadS.DDraw(dxf);
	m_VScale.DDraw(dxf);
	m_HScale.DDraw(dxf);
	dxf.end();
}

CCoorSystem::CCoorSystem()
{
}

CCoorSystem::~CCoorSystem()
{
}

CCoorPoint::CCoorPoint()
{
}

CCoorPoint::CCoorPoint(double x, double y, CString pointName)
{
	SetPoint(x, y, pointName);
}

void CCoorPoint::SetPoint(double x, double y, CString pointName)
{
	m_X = x;
	m_Y = y;
	m_PointName = pointName;
}

void CScale::SetData(vector<vector<CCoorPoint>> LinePoint, vector<vector<CCoorPoint>> PointData, int rows, int count, CString Title, int XCount, int YCount)
{
	int i, j, n ,m;
	double minX, maxX, minY, maxY;
	m_LineData = LinePoint;
	m_PointData = PointData;
	m_YAdd = m_SCP.m_Y * 2 / count*rows;
	m_XCount = XCount;
	m_YCount = YCount;
	m_Rows = rows;
	m_RowCount = count;
	m_Title = Title;
	n = LinePoint.size();
	if (n > 0)
	{
		m = LinePoint[0].size();
		minX = LinePoint[0][0].m_X;
		minY = LinePoint[0][0].m_Y;
		maxX = minX;
		maxY = minY;
	}
	for (i = 0; i < n; i++)
	{
		m = LinePoint[i].size();
		for (j = 0; j < m; j++)
		{
			if (LinePoint[i][j].m_X < minX)
				minX = LinePoint[i][j].m_X;
			else if (LinePoint[i][j].m_X > maxX)
				maxX = LinePoint[i][j].m_X;
			if (LinePoint[i][j].m_Y < minY)
				minY = LinePoint[i][j].m_Y;
			else if (LinePoint[i][j].m_Y > maxY)
				maxY = LinePoint[i][j].m_Y;
		}
	}
	n = PointData.size();
	if (n > 0)
		m = PointData[0].size();

	for (i = 0; i < n; i++)
	{
		m = PointData[i].size();
		for (j = 0; j < m; j++)
		{
			if (PointData[i][j].m_X < minX)
				minX = PointData[i][j].m_X;
			else if (PointData[i][j].m_X > maxX)
				maxX = PointData[i][j].m_X;
			if (PointData[i][j].m_Y < minY)
				minY = PointData[i][j].m_Y;
			else if (PointData[i][j].m_Y > maxY)
				maxY = PointData[i][j].m_Y;
		}
	}
	m_DCP.SetPoint((minX+maxX)/2,(minY+maxY)/2);
	m_BTL.SetPoint(minX,minY);
	m_Width = maxX - minX;
	m_Length = maxX - minX;
}

void CScale::SetScreen(int x, int y)
{
	m_SCP.SetPoint(x/2,y/2);
	m_XScale = m_Width / x;
	m_YScale = m_Length / y;
	m_YAdd = y / m_RowCount*m_Rows;
}

double CScale::PX(double x)
{
	return (x-m_DCP.m_X)/1.4/m_XScale+ m_SCP.m_X;
}

double CScale::PY(double y)
{
	return ((m_DCP.m_Y - y)/1.4/m_YScale + m_SCP.m_Y)/4;
}

double CScale::DX(double x)
{
	return PX(x);
}

double CScale::DY(double y)
{
	return ((y= m_DCP.m_Y)/1.4/m_YScale + m_SCP.m_Y)/4;
}

CString CScale::GetString(double num)
{
	CString strNum;
	strNum.Format(L"%.0f",num);
	return strNum;
}

void CScale::PDraw(CDC * dc)
{
	Initial();
	PInitial(dc);
	PAxis();
	PLine();
	PPoint();
}

void CScale::DDraw(CDxf dxf)
{
	if(DBegin(dxf));
	DAxis();
	DLine();
	DPoint();
	DEnd();
}

void CScale::DDraw()
{

}



void CScale::Initial()
{
	m_GridLength = m_Length / m_YCount;
	m_GridWidth = m_Length / m_XCount;
}

void CScale::PInitial(CDC * dc)
{
	m_pDc = dc;
}

void CScale::PAxis()
{
	int i;
	double oriX, oriY, terX, terY;
	//X
	oriX = PX(m_BTL.m_X);
	oriY = PY(m_BTL.m_Y)+m_YAdd;
	terX = PX(m_BTL.m_X + m_GridWidth * m_XCount);
	terY = oriY;
	m_pDc->MoveTo(oriX, oriY);
	m_pDc->LineTo(terX, terY);
	for (i = 0; i <= m_XCount; i++)
	{
		oriX = PX(m_BTL.m_X + i*m_GridWidth);
		terX = oriX;
		oriY = PY(m_BTL.m_Y) + m_YAdd;
		terY = oriY + 5;
		m_pDc->MoveTo(oriX, oriY);
		m_pDc->LineTo(terX, terY);
		m_pDc->DrawText(GetString(m_BTL.m_X + i* m_GridWidth),
			CRect(terX - 20,terY,terX + 50,terY + 30),
			0
			);
	}
	//Y
	oriX = PX(m_BTL.m_X);
	oriY = PY(m_BTL.m_Y) + m_YAdd;
	terX = oriX;
	terY = PY(m_BTL.m_Y + m_GridLength*m_YCount)+ m_YAdd;
	m_pDc->MoveTo(oriX, oriY);
	m_pDc->LineTo(terX, terY);

	for (i = 0; i <= m_YCount; i++)
	{
		oriX = PX(m_BTL.m_X);
		terX = oriX - 5;
		oriY = PY(m_BTL.m_Y + i*m_GridLength) + m_YAdd;
		terY = oriY;
		m_pDc->MoveTo(oriX, oriY);
		m_pDc->LineTo(terX, terY);
		m_pDc->DrawText(GetString(m_BTL.m_Y + i* m_GridLength),
			CRect(terX - 35, terY-15, terX, terY + 15),
			0
		);
	}
}

void CScale::PLine()
{
	int i, j;
	int n, m;
	double x, y;
	n = m_LineData.size();
	if (n > 0)
		m = m_LineData[0].size();
	for (i = 0; i < n; i++)
	{
		m = m_LineData[i].size();
		for (j = 0; j < m; j++)
		{
			x = PX(m_LineData[i][j].m_X);
			y = PY(m_LineData[i][j].m_Y) + m_YAdd;
			if (j == 0)
			{
				m_pDc->MoveTo(x, y);
			}
			else {
				m_pDc->LineTo(x, y);
			}
			m_pDc->DrawText(m_LineData[i][j].m_PointName,CRect(x-2,y-2,x+2,y+2),0);
		}
	}
}

void CScale::PPoint()
{
	int i, j, n, m;
	double x, y;
	n = m_PointData.size();
	if (n > 0)
		m = m_PointData[0].size();
	for (i = 0; i < n; i++)
	{
		m = m_PointData[i].size();
		for (j = 0; j < m; j++)
		{
			x = PX(m_PointData[i][j].m_X);
			y = PY(m_PointData[i][j].m_Y);
			m_pDc->Ellipse(x - 2, y - 2, x + 2, y + 2);
		}
	}
}

void CScale::DBegin(CDxf * dxf)
{
	m_Dxf = dxf;
}

CString ListUpdate::GetString(double num)
{
	CString strNum;
	strNum.Format(L"%f",num);
	return strNum;
}

void ListUpdate::Update(CListCtrl & listCtrl, std::vector<std::vector<CDataPoint>> data)
{
	int row;
	int i,j,n,m;
	n = data.size();
	listCtrl.DeleteAllItems();
	if (n > 0)
	{
		m = data[0].size();
	}
	for (i = 0;i < n;i++)
	{
		m = data[i].size();
		for (j = 0;j < m;j++)
		{
			row = listCtrl.GetItemCount();
			listCtrl.InsertItem(row, data[i][j].strID);
			listCtrl.SetItemText(row,1,GetString(data[i][j].m_K));
			listCtrl.SetItemText(row, 2, GetString(data[i][j].m_x));
			listCtrl.SetItemText(row, 3, GetString(data[i][j].m_y));
			listCtrl.SetItemText(row, 4, GetString(data[i][j].m_h));
		}
	}
	
}
