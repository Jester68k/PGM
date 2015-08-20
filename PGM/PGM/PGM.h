
// PGM.h : PGM �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��

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
// ���̃N���X�̎����ɂ��ẮAPGM.cpp ���Q�Ƃ��Ă��������B
//

class CPGMApp : public CWinApp
{
public:
	CPGMApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPGMApp theApp;
