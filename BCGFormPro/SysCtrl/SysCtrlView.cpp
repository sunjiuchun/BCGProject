// SysCtrlView.cpp : implementation of the CSysCtrlView class
//

#include "stdafx.h"
#include "SysCtrl.h"

#include "SysCtrlDoc.h"
#include "SysCtrlView.h"
#include "TransData_Manager.h"
#include "TransData.h"
#include "TransData_Com.h"
#include "TransData_Udp.h"




#include "ProtocolData.h"
#include "ProtocolData_protocol1.h"
#include "ProtocolData_protocol2.h"
#include "ProtocolData_Manager.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSysCtrlView

IMPLEMENT_DYNCREATE(CSysCtrlView, CView)

BEGIN_MESSAGE_MAP(CSysCtrlView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
	ON_REGISTERED_MESSAGE(BCGM_CHANGEVISUALMANAGER, OnChangeVisualManager)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CSysCtrlView construction/destruction

CSysCtrlView::CSysCtrlView()
{
	// TODO: add construction code here

}

CSysCtrlView::~CSysCtrlView()
{
}

BOOL CSysCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs	
	return CView::PreCreateWindow(cs);
}

// CSysCtrlView drawing

void CSysCtrlView::OnDraw(CDC* /*pDC*/)
{
	CSysCtrlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	AdjustLayout();
	pGridCtrl->SetVisualManagerColorTheme(15);

	// TODO: add draw code for native data here
}


// CSysCtrlView printing

void CSysCtrlView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CSysCtrlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSysCtrlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSysCtrlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSysCtrlView diagnostics

#ifdef _DEBUG
void CSysCtrlView::AssertValid() const
{
	CView::AssertValid();
}

void CSysCtrlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSysCtrlDoc* CSysCtrlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSysCtrlDoc)));
	return (CSysCtrlDoc*)m_pDocument;
}
#endif //_DEBUG


// CSysCtrlView message handlers

LRESULT CSysCtrlView::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if ((lp & PRF_CLIENT) == PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC) wp);
		ASSERT_VALID(pDC);
		
		OnDraw(pDC);
	}
	
	return 0;
}

LRESULT CSysCtrlView::OnChangeVisualManager(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return 0;
}


int CSysCtrlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������


	CRect rectClient;
	GetClientRect(rectClient);
	pGridCtrl = new CMyDataGrid();
	ASSERT_VALID(pGridCtrl);
	if (!pGridCtrl->Create(WS_CHILD, rectClient, this, 1))
	{
		ASSERT(FALSE);
		return -1;
	}
	pGridCtrl->ShowWindow(SW_SHOW);



	//��ʼ�����ܻ���ͷ��ͻ���
	m_pBuffer_recv = new CBuffer();
	m_pBuffer_send = new CBuffer();

	//�������������
	pTrans_Manager = TransData_Manager::GetInstance();	

	//��������
	TransData* p_com = new TransData_Com;
	p_com->Set_pBuffer_recv(m_pBuffer_recv);
	p_com->Set_pBuffer_send(m_pBuffer_send);
	p_com->Initial();		
	pTrans_Manager->SetTrans(L"COM", p_com);


	//����UDP
	TransData* p_udp = new TransData_Udp;
	p_udp->Set_pBuffer_recv(m_pBuffer_recv);
	p_udp->Set_pBuffer_send(m_pBuffer_send);
	p_udp->Initial();
	pTrans_Manager->SetTrans(L"UDP", p_udp);



	//����Э�������
	pProtocol_Manager = ProtocolData_Manager::GetInstance();
	pProtocol_Manager->Set_pBuffer_recv(m_pBuffer_recv);
	pProtocol_Manager->Set_pBuffer_send(m_pBuffer_send);

	//����Э��һ
	ProtocolData* p_Protocol1 = new ProtocolData_protocol1;
	pProtocol_Manager->SetProtocols(L"Э��һ", p_Protocol1);

	//����Э���
	ProtocolData* p_Protocol2 = new ProtocolData_protocol2;
	pProtocol_Manager->SetProtocols(L"Э���", p_Protocol2);


	//Э�������Ԥ��������
	pProtocol_Manager->BeginPreHandleThread();



	return 0;
}


void CSysCtrlView::AdjustLayout()
{
	if (pGridCtrl->GetSafeHwnd() == NULL)
		return;
	CRect rectClient;
	GetClientRect(rectClient);
	pGridCtrl->SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	//pGridCtrl->SetMyFont();
}