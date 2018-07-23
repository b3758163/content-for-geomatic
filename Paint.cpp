CPaintDC dc(this); // device context for painting
	CRgn rgn;
	dc.BeginPath();
	dc.MoveTo(15,15);
	dc.LineTo(15,60);
	dc.LineTo(60,60);
	dc.LineTo(60,15);
	dc.LineTo(15,15);
	dc.EndPath();
	//rgn.CreateFromPath(&dc);
	CBrush brush;
	brush.CreateSolidBrush(RGB(56,78,90));
	dc.SelectObject(brush);
	dc.FillPath();
	//dc.FillRgn(&rgn,&brush);