
// PGM.h : PGM アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル

extern int color_code[];

const int MAX_WIDTH = 32;
const int MAX_HEIGHT = 32;
const int MAX_LEVEL = 100;
const int MAX_NEXT = 5;
const int BLOCK_TYPE_ROTATE = 0;
const int BLOCK_TYPE_CIRCULATE = 1;
const int MODE_NORMAL = 0;
const int MODE_PLAY = 1;
const int MODE_GAMEOVER = 2;
const int WINDOW_W = 640;
const int WINDOW_H = 480;
const int SHOUMETSU_YOKOLINE = 0;
const int SHOUMETSU_LINE = 1;
const int SHOUMETSU_RINSETSU = 2;

// CPGMApp:
// このクラスの実装については、PGM.cpp を参照してください。
//

class CPGMApp : public CWinApp
{
public:
	CPGMApp();


// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPGMApp theApp;
