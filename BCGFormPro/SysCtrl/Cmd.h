#pragma once



/*---------------------------------------------------
�ļ���: Cmd.h
��  ;: �������
��  ��: 2017.04.09
��  ��: 1.0
��  ��: �� ��
---------------------------------------------------*/

#include "stdafx.h"
#include <string>
class CCmd
{
public:
	//virtual std::string GetVersion() = 0;
	virtual int HandleData(unsigned char* ptr,int len ) = 0;
	virtual int MakeData(unsigned char* ptr, int len) = 0;
	virtual int GetLength() = 0;
	void show() { ; };
};