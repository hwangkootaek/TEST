
// Puzzle.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPuzzleApp:
// �� Ŭ������ ������ ���ؼ��� Puzzle.cpp�� �����Ͻʽÿ�.
//

class CPuzzleApp : public CWinApp
{
public:
	CPuzzleApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPuzzleApp theApp;