
// DNA_Show.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDNA_ShowApp: 
// �йش����ʵ�֣������ DNA_Show.cpp
//

class CDNA_ShowApp : public CWinApp
{
public:
	CDNA_ShowApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDNA_ShowApp theApp;