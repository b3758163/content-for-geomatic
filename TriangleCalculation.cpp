#include "stdafx.h"
#include "Calculation.h"


bool CCalculation::ReadData()
{
	CStdioFile file;
	CFileDialog fd(true, L"txt", 0, 6UL, L"数据文件(*.txt)|*.txt||");
	if (fd.DoModal() != IDOK)
	{
		return false;
	}
	file.Open(fd.GetPathName(), CFile::modeRead);
	CString buff, line;
	std::vector<CString> data;
	m_OriPoint.clear();
	while (file.ReadString(line))	
	{
		data.clear();
		while (line.GetLength() > 0)
		{
			line.Remove(L' ');
			buff = line.SpanExcluding(L",");
			line.Delete(0, buff.GetLength() + 1);
			data.push_back(buff);
		}
		m_OriPoint.push_back(CDataPoint(
			_ttof(data[1]),
			_ttof(data[2]),
			_ttof(data[3]),
			data[0]
		));
	}
	return true;
}

void CCalculation::GetOriTriangle()
{
	CDataPoint p1, p2, p3, p4;
	double minX, minY, maxX, maxY;
	int count = m_OriPoint.size();
	int i = 0;
	if (count > 0)
	{
		minX = m_OriPoint[0].X();
		minY = m_OriPoint[0].Y();
		maxX = minX;
		maxY = minY;
	}
	for (i = 0;i < count;i++)
	{
		if (m_OriPoint[i].X() < minX)
			minX = m_OriPoint[i].X();
		else if (m_OriPoint[i].X() > maxX)
			maxX = m_OriPoint[i].X();
		if (m_OriPoint[i].Y() < minY)
			minY = m_OriPoint[i].Y();
		else if (m_OriPoint[i].Y() > maxY)
			maxY = m_OriPoint[i].Y();
	}
	p1.SetPoint(minX - 1, minY - 1, 0, L"P1");
	p2.SetPoint(minX - 1, maxY + 1, 0, L"P2");
	p3.SetPoint(maxX + 1, maxY + 1, 0, L"P3");
	p4.SetPoint(maxX + 1, minY - 1, 0, L"P4");
	m_T1.push_back(CTriangle(p1, p2, p3));
	m_T1.push_back(CTriangle(p1, p4, p3));
}

void CCalculation::GetTriangle()
{
	int count = m_OriPoint.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		GetinfTri(m_OriPoint[i]);
		GetLine();
		DeleteLine();
		GetNewTri(m_OriPoint[i]);
	}
}

void CCalculation::GetinfTri(CDataPoint point)
{
	int count = m_T1.size();
	int i = 0;
	m_T2.clear();
	std::vector<CTriangle> bT;
	for (i = 0;i < count;i++)
	{
		if (m_T1[i].IsInfluence(point))
		{
			m_T2.push_back(m_T1[i]);
		}
		else
		{
			bT.push_back(m_T1[i]);
		}
	}
	m_T1.clear();
	m_T1 = bT;
}

void CCalculation::GetLine()
{
	m_L1.clear();
	int count =m_T2.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		m_L1.push_back(m_T2[i].L1());
		m_L1.push_back(m_T2[i].L2());
		m_L1.push_back(m_T2[i].L3());
	}
}

void CCalculation::DeleteLine()
{
	int count = m_L1.size();
	int i = 0;
	std::vector<CLine> bL;
	for (i = 0;i < count;i++)
	{
		if (SameCount(m_L1[i])<2)
		{
			bL.push_back(m_L1[i]);
		}
	}
	m_L1.clear();
	m_L1 = bL;
}

void CCalculation::GetNewTri(CDataPoint point)
{
	int count = m_L1.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		m_T1.push_back(CTriangle(m_L1[i],point));
	}
}

int CCalculation::SameCount(CLine line)
{
	int num = 0;
	int count = m_L1.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		if (line == m_L1[i])
		{
			num++;
		}
	}
	return num;
}

void CCalculation::DeleteOutLine()
{
	int count = m_T1.size();
	int i = 0;
	std::vector<CTriangle> bT;
	std::vector<CString>  names = { L"P1",L"P2",L"P3",L"P4" };
	for (i = 0;i < count;i++)
	{
		if (!m_T1[i].ContainPoint(names))
		{
			bT.push_back(m_T1[i]);
		}
	}
	m_T1 = bT;
}

void CCalculation::GetVolume()
{
	int count = m_T1.size();
	int i = 0;
	double volume;
	m_Volume = 0;
	for (i = 0;i < count;i++)
	{
		volume = m_T1[i].GetVolume(m_BaseHeight);
		m_Volumes.push_back(volume);
		m_Volume += volume;
	}
}

void CCalculation::SortVolume()
{
	sort(m_Volumes.begin(), m_Volumes.end(), sortAddin);
}

bool CCalculation::sortAddin(double a, double b)
{
	return a<b;
}

void CCalculation::Calculate()
{
	ReadData();
	GetOriTriangle();
	GetTriangle();
	DeleteOutLine();
	GetVolume();
	SortVolume();
	CString strNum;
	strNum.Format(L"%.3f",m_Volume);
	AfxMessageBox(strNum);

}

CCalculation::CCalculation()
{
}

CCalculation::~CCalculation()
{
}
