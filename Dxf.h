#pragma once
class CDxf
{
private:
	CStdioFile m_File;
private:
	CString GetString(double num);
public:
	bool Begin();
	void Point(double x, double y);
	void Line(double x1, double y1, double x2, double y2);
	void Text(double x, double y, CString text);
	void End();
public:
	CDxf operator=(const CDxf& dxf);
	CDxf();
	~CDxf();
};

