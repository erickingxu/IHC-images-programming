// voronoi.h : voronoi Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CvoronoiApp:
// �йش����ʵ�֣������ voronoi.cpp
//

class CvoronoiApp : public CWinApp
{
public:
	CvoronoiApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CvoronoiApp theApp;