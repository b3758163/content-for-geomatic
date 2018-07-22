#include "stdafx.h"
#include "Calculation.h"
#include <algorithm>

CCalculation::CCalculation()
{
}


CCalculation::~CCalculation()
{
}

void CCalculation::ReadData()
{
	CStdioFile file;
	CFileDialog fd(true,L"txt",0,6UL,L"数据文件(*.txt)|*.txt||");
	CString line;
	CString buff;
	std::vector<CString>data;
	if (fd.DoModal() != IDOK)
	{
		return;
	}
	m_OriPoint.clear();
	m_OutLine.clear();
	m_Grids.clear();
	m_ValidGrids.clear();
	m_Grids.clear();
	file.Open(fd.GetPathName(),CFile::modeRead);//第一个参数写错过 fd 写成了file
	while (file.ReadString(line))
	{
		data.clear();
		while (line.GetLength() > 0)
		{
			buff = line.SpanExcluding(L",");
			data.push_back(buff);
			line.Delete(0,buff.GetLength()+1);
		}
		m_OriPoint.push_back(CMyPoint(_ttof(data[1]),_ttof(data[2]),_ttof(data[3]),data[0]));
	}
}

void CCalculation::GetDataRange()
{
	int count = m_OriPoint.size();
	int  i = 0;
	double minX, minY, maxX, maxY;
	if (count > 0)
	{
		minX = m_OriPoint[i].X();
		maxX = minX;
		minY = m_OriPoint[i].Y();
		maxY = minY;
	}
	for (i = 0;i < count;i++)
	{
		if (m_OriPoint[i].X() < minX)
		{
			minX = m_OriPoint[i].X();
		}
		else if (m_OriPoint[i].X() > maxX)
		{
			maxX = m_OriPoint[i].X();
		}
		if (m_OriPoint[i].Y() < minY)
		{
			minY = m_OriPoint[i].Y();
		}
		else if (m_OriPoint[i].Y() > maxY)
		{
			maxY = m_OriPoint[i].Y();
		}
	}
	m_DataRange.SetRange(minX, minY, maxX, maxY, m_GridLength);
	m_Grids = m_DataRange.GetGrid();
	m_PowerRange = (maxX - minX + maxY - minY)*m_NerScale;
}

void CCalculation::GetOutLine()
{
	GetFirstLine();
	GetRestLine();
}

void CCalculation::GetFirstLine()
{
	m_OutLine.clear();
	CMyPoint firstPoint = GetFirstPoint();
	std::vector<CLine> lines;
	int count = m_OriPoint.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		if (!(firstPoint == m_OriPoint[i]))
			lines.push_back(CLine(firstPoint, m_OriPoint[i]));
	}
	std::sort(lines.begin(), lines.end(), SortLineInc);
	if (lines.size() > 0)
	{
		m_OutLine.push_back(lines[0]);
	}
	else
	{
		AfxMessageBox(L"获取第一条边出现错误");
	}
}

void CCalculation::GetRestLine()
{
	CMyPoint lastPoint = m_OutLine[m_OutLine.size() - 1].TerPoint();
	while (!(lastPoint == m_OutLine[0].OriPoint()))
	{
		lastPoint = m_OutLine[m_OutLine.size() - 1].TerPoint();
		m_OutLine.push_back(GetLeftLine(m_OutLine[m_OutLine.size() - 1]));
	}
}

CMyPoint CCalculation::GetFirstPoint()
{
	CMyPoint minPoint;
	int count = m_OriPoint.size();
	int i = 0;
	double minX, minY;
	if (count > 0)
	{
		minX = m_OriPoint[i].X();
		minY = m_OriPoint[i].Y();
		minPoint = m_OriPoint[0];
	}
	for (i = 0;i < count;i++)
	{
		if (m_OriPoint[i].Y() < minY || (m_OriPoint[i].Y() == minY&&m_OriPoint[i].X() < minX))
		{
			minX = m_OriPoint[i].X();
			minY = m_OriPoint[i].Y();
			minPoint = m_OriPoint[i];
		}
	}
	return minPoint;
}

CLine CCalculation::GetLeftLine(CLine p)
{
	std::vector<CLine> bLines;
	int count = m_OriPoint.size();
	int i = 0;
	int index;
	for (i = 0;i < count;i++)
	{
		if (!(p.TerPoint() == m_OriPoint[i]))
		{
			if (p.OriPoint() == m_OriPoint[i])
				bLines.push_back(p);
			else
				bLines.push_back(CLine(p.TerPoint(), m_OriPoint[i]));
		}
	}
	sort(bLines.begin(), bLines.end(), SortLineInc);
	for (i = 0;i < count;i++)
	{
		if (bLines[i] == p)
		{
			index = i;
			break;
		}
	}
	if (index < count - 2)
	{
		index++;
	}
	else
	{
		index = 0;
	}


	return bLines[index];
}

bool CCalculation::SortLineInc(CLine & l1, CLine & l2)
{
	return l1.Azimuth() < l2.Azimuth();
}

void CCalculation::GetValidGrid()
{
	int count = m_Grids.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		if (isValid(m_Grids[i]))
		{
			m_ValidGrids.push_back(m_Grids[i]);
		}
	}
}

bool CCalculation::isValid(CGrid grid)
{
	CMyPoint p = grid.CentPoint();
	int count = m_OutLine.size();
	int i = 0;
	int LeftCount = 0;
	for (i = 0;i < count;i++)
	{
		if (IsLeft(p, m_OutLine[i]))
			LeftCount++;
	}
	return LeftCount % 2;
}

bool CCalculation::IsLeft(CMyPoint p, CLine line)
{
	double lineX = (p.Y() - line.Intercept()) / line.Slope();
	if ((p.Y() - line.TerPoint().Y())*(p.Y() - line.OriPoint().Y()) > 0)
		return false;
	if (lineX > p.X())
		return true;
	else
		return false;
}

void CCalculation::GetH()
{
	int count = m_ValidGrids.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		m_ValidGrids[i].SetH(GetGridH(m_ValidGrids[i]));
	}
}

std::vector<double> CCalculation::GetGridH(CGrid grid)
{
	std::vector<CMyPoint> points= grid.GetGridPoint();
	std::vector<double> h;
	int count = points.size();
	int i = 0;
	for (i = 0;i < count;i++)
	{
		h.push_back(GetPointH(points[i]));
	}
	return h;
}

double CCalculation::GetPointH(CMyPoint p)
{
	std::vector<double> bDistance;
	std::vector<CMyPoint> bPoint;
	int count = m_OriPoint.size();
	int i = 0;
	double distance;
	double deno = 0, num= 0;
	for (i = 0;i < count;i++)
	{
		distance = p.GetDistance(m_OriPoint[i]);
		if (distance < m_PowerRange)
		{
			bDistance.push_back(distance);
			bPoint.push_back(m_OriPoint[i]);
		}
	}
	count = bPoint.size();
	for (i = 0;i < count;i++)
	{
		num += bPoint[i].H() / bDistance[i];
		deno = 1 / bDistance[i];
	}
	return num / deno;
}

void CCalculation::GetVolume()
{
	int count = m_ValidGrids.size();
	int i = 0;
	double volume;
	m_Volume = 0;
	m_Volumes.clear();
	for (i = 0;i < count;i++)
	{
		volume = m_ValidGrids[i].GetVolume(m_BaseHeight);
		m_Volumes.push_back(volume);
		m_Volume += volume;
	}
}

void CCalculation::Calculate()
{
	ReadData();
	GetDataRange();
	GetOutLine();
	GetValidGrid();
	GetH();
	GetVolume();
	CString text;
	text.Format(L"%f",m_Volume);
	AfxMessageBox(text);
}

std::vector<CLine> CCalculation::OutLine()
{
	return m_OutLine;
}

std::vector<double> CCalculation::Volumes()
{
	return m_Volumes;
}
