#pragma once


/*---------------------------------------------------
�ļ���: CmdData.h
��  ;: ��������
��  ��: 2017.04.09
��  ��: 1.0
��  ��: �� ��
---------------------------------------------------*/


#include "Cmd.h"
class CCmdData : public CCmd 
{
public:
	CCmdData();
	~CCmdData();
	int HandleData(unsigned char* ptr, int len) ;
	int MakeData(unsigned char* ptr, int len) ;
	int GetLength();
private:
	int data1;
	int data2;
	int data3;
	int m_length;
};