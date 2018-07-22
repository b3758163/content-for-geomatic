#include "stdafx.h"
#include "Dxf.h"


CString CDxf::GetString(double num)
{
	CString strNum;
	strNum.Format(L"%f",num);
	return strNum;
}

bool CDxf::Begin()
{
	CFileDialog fd(true,L"dxf",L"resultDxf",6UL,L"dxf图形交换文件(*.dxf)|*.dxf||");
	if (fd.DoModal() != IDOK)
		return false;
	m_File.Open(fd.GetPathName(),CFile::modeCreate|CFile::modeWrite);
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"SECTION\n");
	m_File.WriteString(L"2\n");
	m_File.WriteString(L"ENTITIES\n");

	return true;
}

void CDxf::Point(double x, double y)
{
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"POINT\n");
	m_File.WriteString(L"10\n");
	m_File.WriteString(GetString(x)+L"\n");
	m_File.WriteString(L"20\n");
	m_File.WriteString(GetString(y) + L"\n");
	m_File.WriteString(L"30\n");
	m_File.WriteString(L"0\n");

}

void CDxf::Line(double x1, double y1, double x2, double y2)
{
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"LINE\n");
	m_File.WriteString(L"8\n");
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"10\n");
	m_File.WriteString(GetString(x1) + L"\n");
	m_File.WriteString(L"20\n");
	m_File.WriteString(GetString(y1) + L"\n");
	m_File.WriteString(L"30\n");
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"11\n");
	m_File.WriteString(GetString(x2) + L"\n");
	m_File.WriteString(L"21\n");
	m_File.WriteString(GetString(y2) + L"\n");
	m_File.WriteString(L"31\n");
	m_File.WriteString(L"0\n");
}

void CDxf::Text(double x, double y, CString text)
{
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"TEXT\n");
	m_File.WriteString(L"8\n");
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"10\n");
	m_File.WriteString(GetString(x)+"\n");
	m_File.WriteString(L"20\n");
	m_File.WriteString(GetString(y)+L"\n");
	m_File.WriteString(L"30\n");
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"40\n");
	m_File.WriteString(L"10\n");
	m_File.WriteString(L"1\n");
	m_File.WriteString(text+L"\n");
}

void CDxf::End()
{
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"ENDSEC\n");
	m_File.WriteString(L"0\n");
	m_File.WriteString(L"EOF\n");
	m_File.Close();
}

CDxf CDxf::operator=(const CDxf & dxf)
{
	return dxf;
}

CDxf::CDxf()
{
}


CDxf::~CDxf()
{
}
