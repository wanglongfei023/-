#pragma once
#include "Sys.h"


class CBack
{
public:
	CBack(void);
	~CBack(void);
public:
	HBITMAP m_hBmpBackDown;   //  ����ͼƬ
	HBITMAP m_hBmpBackUp;
	int x;
	int y;
public:
	void BackInit(HINSTANCE hIns);
	void BackMove();
	void BackShow(HDC hMemDC);
};

