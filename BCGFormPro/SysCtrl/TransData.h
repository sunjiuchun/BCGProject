/*---------------------------------------------------
�ļ���: TransData.h
��  ;: ͨ�Ż���
��  ��: 2017.04.08
��  ��: 1.0
��  ��: �� ��
---------------------------------------------------*/

#pragma once

#include "stdafx.h"
#include "Buffer.h"

class TransData
{
public:
	virtual void SendData(char* src, int len) = 0;	
	virtual void Initial() = 0;
	void Set_pBuffer_recv(CBuffer* pBuffer);
	void Set_pBuffer_send(CBuffer* pBuffer);

public:
	CBuffer* m_pBuffer_recv;
	CBuffer* m_pBuffer_send;
};