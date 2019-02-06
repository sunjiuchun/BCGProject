#include "stdafx.h"
#include "TransData_Udp.h"
#include <afxsock.h>




void TransData_Udp::SendData(char* src, int len) {

}
void TransData_Udp::Initial() {

	SetNet(STR_LOCALIP, I_LOCALPORT , STR_REMOTEIP, I_REMOTEPORT);
}


TransData_Udp::TransData_Udp()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("�����׽���ʧ��"));
		return;
	}
	m_socketServer = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == m_socketServer)
	{
		AfxMessageBox(_T("�׽��ִ���ʧ��"));
		return;
	}
}


TransData_Udp::~TransData_Udp()
{

}

void TransData_Udp::SetNet(CString ip1, int port1, CString ip2, int port2)
{
	str_localIP = ip1;
	str_remoteIP = ip2;
	i_localPort = port1;
	i_remotePort = port2;


	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(i_localPort);
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���Ͷ˵�ַ ��������Ip
	int retval = bind(m_socketServer, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
	if (SOCKET_ERROR == retval)
	{
		closesocket(m_socketServer);
		AfxMessageBox(_T("��ʧ��"));
		return;
	}


	RECVPARAM *pRecvParam = new RECVPARAM;
	pRecvParam->buff_recv = m_pBuffer_recv;
	pRecvParam->sock = m_socketServer;

	m_hThread = CreateThread(NULL, 0, RecvProc,(LPVOID)(pRecvParam), 0, NULL);
	CloseHandle(m_hThread);

	//���Ͷ�1��������
	m_socketClient = socket(AF_INET, SOCK_DGRAM, 0);
	addrSrv.sin_addr.S_un.S_addr = inet_addr((LPSTR)(LPCTSTR)str_remoteIP); //���ն˵�ַ
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(i_remotePort);
	connect(m_socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));


	//UINT m_TimerId = ::SetTimer(NULL, 0, 1000, SendProc);
	Timerld = timeSetEvent(40, 0, (LPTIMECALLBACK)SendProc, NULL, TIME_PERIODIC);
	if (Timerld == NULL)
		AfxMessageBox(L"���ͻ�������ʱ������ʧ��");
}


DWORD WINAPI TransData_Udp::RecvProc(LPVOID lpParameter)
{
	SOCKET	sock_serve = ((RECVPARAM*)lpParameter)->sock;
	CBuffer *buff_recv = ((RECVPARAM*)lpParameter)->buff_recv;

	SOCKADDR_IN addrFrom;
	BYTE recvBuf[2000];
	int len = sizeof(SOCKADDR);
	memset(recvBuf, 0, 2000);
	while (TRUE)
	{
		int recvlen = recvfrom(sock_serve, (char *)recvBuf, 5000, 0, (SOCKADDR*)&addrFrom, &len);
		if (SOCKET_ERROR == recvlen)
			continue;
		buff_recv->AddData((char*)recvBuf, recvlen);
	}
	return 0;
}


void TransData_Udp::SendProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//UINT m_TimerId = ::SetTimer(NULL, 0, 1000, TimerProc);
	//int a = 10;
	//���ͻ����е�����
}