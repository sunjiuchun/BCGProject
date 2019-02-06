#include "stdafx.h"
#include "MyDataGrid.h"


BEGIN_MESSAGE_MAP(CMyDataGrid, CBCGPGridCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()




#define TEXT_VMARGIN	2

int CMyDataGrid::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	EnableMarkSortedColumn(FALSE);
	EnableHeader(TRUE, BCGP_GRID_HEADER_MOVE_ITEMS | BCGP_GRID_HEADER_SORT);
	EnableRowHeader(TRUE);
	EnableLineNumbers();
	SetClearInplaceEditOnEnter(FALSE);
	EnableInvertSelOnCtrl();
	



	int width = 200;
	InsertColumn(0, _T("ʱ��"), width);
	InsertColumn(1, _T("�ź����ͱ���"), width);
	InsertColumn(2, _T("Ƶ��(MHz)"), width);
	InsertColumn(3, _T("����(us)"), width);
	InsertColumn(4, _T("����(us)"), width);
	InsertColumn(5, _T("����(dBm)"), width);
	InsertColumn(6, _T("�������"), width);

	//SetColumnWidth(-1, 200);


	for (int i = 0; i < 7; ++i)
	{
		SetHeaderAlign(i, HDF_CENTER);
		SetColumnAlign(i, HDF_RIGHT);
	}


	for (int nRow = 0; nRow < 99; nRow++)
	{
		CBCGPGridRow* pRow = CreateRow(GetColumnCount());		
		AddRow(pRow, FALSE);
	}

	SetMyFont();


	//ModifyStyle( WS_VSCROLL, 0, 0);

	return 0;
}





void CMyDataGrid::SetRowHeight()
{
	if (m_bIsPrinting)
	{
		ASSERT_VALID(m_pPrintDC);

		// map to printer metrics
		HDC hDCFrom = ::GetDC(NULL);
		int nYMul = m_pPrintDC->GetDeviceCaps(LOGPIXELSY);	// pixels in print dc
		int nYDiv = ::GetDeviceCaps(hDCFrom, LOGPIXELSY);	// pixels in screen dc
		::ReleaseDC(NULL, hDCFrom);

		TEXTMETRIC tm;
		m_pPrintDC->GetTextMetrics(&tm);
		m_PrintParams.m_nBaseHeight = tm.tmHeight + ::MulDiv(2 * TEXT_VMARGIN, nYMul, nYDiv);
		m_PrintParams.m_nRowHeight = m_PrintParams.m_nBaseHeight;
		m_PrintParams.m_nLargeRowHeight = m_PrintParams.m_nBaseHeight;
		m_PrintParams.m_nButtonWidth = m_PrintParams.m_nBaseHeight;
	}
	else
	{
		CClientDC dc(this);
		HFONT hfontOld = SetCurrFont(&dc);

		TEXTMETRIC tm;
		dc.GetTextMetrics(&tm);
		m_nBaseHeight = tm.tmHeight + TEXT_VMARGIN;
		m_nBaseHeight = m_nBaseHeight + 5;
		m_nRowHeight = m_nBaseHeight;
		m_nLargeRowHeight = m_nBaseHeight;
		m_nButtonWidth = m_nBaseHeight;
		//SetRowHeaderWidth(10,1);
		::SelectObject(dc.GetSafeHdc(), hfontOld);
	}
}

void CMyDataGrid::SetMyFont()
{
	m_font;
	font = this->GetFont();
	LOGFONT lf;
	font->GetLogFont(&lf);
	lf.lfHeight = 20;
	lf.lfWeight = 700;
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("����"));
	m_font.CreateFontIndirect(&lf);
	this->SetFont(&m_font);
}

void CMyDataGrid::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CBCGPGridCtrl::OnLButtonDown(nFlags, point);
}


void CMyDataGrid::OnSize(UINT nType, int cx, int cy)
{
	CBCGPGridCtrl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������


	//CBCGPGridCtrl::AdjustLayout();
	CRect rectClient;
	GetClientRect(rectClient);
	int width_max = rectClient.right;
	int width = rectClient.right / 7;
	if (width < 100)
	{
		width = 260;
		for (int i = 0; i < 7; ++i)
		{
			SetColumnWidth(i, width);
		}
		return;
	}

	for (int i = 0; i < 6; ++i)
	{
		SetColumnWidth(i, width);
	}
		
	SetColumnWidth(6, width_max- 6* width);


	this->ShowScrollBar(SB_HORZ, FALSE);
	//Invalidate();	
	this->SetRedraw();
}
