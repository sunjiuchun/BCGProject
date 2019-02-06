/*---------------------------------------------------
�ļ���: TransData_Com.h
��  ;: ����ͨ����
��  ��: 2017.04.08
��  ��: 1.0
��  ��: �� ��
---------------------------------------------------*/


#pragma once
#include "stdafx.h"
#include "TransData.h"
#include <mmsystem.h>


#pragma comment(lib,"winmm")

class TransData_Com : public TransData
{
public:

	//�ⲿ�ӿ�
	void SendData(char* src, int len);	
	void Initial();




	bool ReadStopped();
	void SetReadStartFlag(bool bStarted);
	TransData_Com();
	~TransData_Com();
	bool	Init(const CString &com, int baudrate, int readbufsize, int iName);
	bool	SetReadSize(int size);
	void	WriteData(char *array, int size);
	void	WriteDataThread(char *array, int size);
	void	BeginRead(void);
	void	StopRead(void);
	char * 	GetReadData(int &iSize);
	static void CALLBACK SendProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

private:

	bool    m_bReadStarted;
	HANDLE	m_hCom;
	char	*m_pArray;
	char    *m_pCommandLine;
	HWND	m_hWnd;
	bool	m_isContinue;
	int		m_iReadSize;
	int		m_iReadBufferSize;
	int		m_iReadSizeResult;
	int		m_iName;

	char    *m_pWriteArray;
	int		m_iWriteSize;

	bool	InitComm(const CString &com, int baudrate);
	UINT	Read(void);
	UINT	Write(void);
	static	UINT RunRead(LPVOID lpparam);
	static	UINT RunWrite(LPVOID lpparam);
	MMRESULT Timerld;
};