
// PGMDoc.cpp : CPGMDoc �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "PGM.h"
#endif

#include "PGMDoc.h"

#include <propkey.h>

#include "WizardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPGMDoc

IMPLEMENT_DYNCREATE(CPGMDoc, CDocument)

BEGIN_MESSAGE_MAP(CPGMDoc, CDocument)
END_MESSAGE_MAP()


// CPGMDoc �R���X�g���N�V����/�f�X�g���N�V����

CPGMDoc::CPGMDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CPGMDoc::~CPGMDoc()
{
}

BOOL CPGMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B
	CWizardDlg wizard_dlg;

	int x, y, rotate, num;

	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	for (num = 0; num<16; num++)
		for (rotate = 0; rotate<4; rotate++)
			for (y = 0; y<16; y++)
				for (x = 0; x<16; x++)
					block[num][rotate][y][x] = 0;
	pf_width = wizard_dlg.m_pfwidth = 10;
	pf_height = wizard_dlg.m_pfheight = 20;
	block_type = wizard_dlg.m_block_type = 1;			// �����u���b�N�̕ω��^�C�v�F�z�i�c�j
	pattern_size = wizard_dlg.m_pattern_size = 3;		// ���P��
	num_erase = wizard_dlg.m_num_erase = 3;		// �R�ȏ�
	erase_jouken = wizard_dlg.m_erase_jouken = ERASE_LINE;	// ��񑵂�
	color_tate_flag = wizard_dlg.m_color_tate_flag = TRUE;
	color_yoko_flag = wizard_dlg.m_color_yoko_flag = TRUE;
	color_naname_flag = wizard_dlg.m_color_naname_flag = TRUE;
	num_patterns = wizard_dlg.m_num_patterns = 1;
	block_random_flag = wizard_dlg.m_block_random_flag = TRUE;
	num_colors = wizard_dlg.m_num_colors = 7;
	drop_flag = wizard_dlg.m_drop_flag = TRUE;
	num_next = wizard_dlg.m_num_next = 3;

	if (wizard_dlg.DoModal() == IDOK) {
		pf_width = wizard_dlg.m_pfwidth;
		pf_height = wizard_dlg.m_pfheight;
		block_type = wizard_dlg.m_block_type;
		pattern_size = wizard_dlg.m_pattern_size;
		num_erase = wizard_dlg.m_num_erase;
		erase_jouken = wizard_dlg.m_erase_jouken;
		color_tate_flag = wizard_dlg.m_color_tate_flag;
		color_yoko_flag = wizard_dlg.m_color_yoko_flag;
		color_naname_flag = wizard_dlg.m_color_naname_flag;
		num_patterns = wizard_dlg.m_num_patterns;
		block_random_flag = wizard_dlg.m_block_random_flag;
		num_colors = wizard_dlg.m_num_colors;
		drop_flag = wizard_dlg.m_drop_flag;
		num_next = wizard_dlg.m_num_next;
	}

	static int first = 0;
	if (!first) {
		srand((unsigned)time(NULL));
		first = 1;
	}
	return TRUE;
}


// CPGMDoc �V���A����

void CPGMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << pf_width;
		ar << pf_height;
		ar << block_type;
		ar << pattern_size;
		ar << num_erase;
		ar << erase_jouken;
		ar << color_tate_flag << color_yoko_flag << color_naname_flag;
		ar << num_patterns;
		ar << block_random_flag;
		ar << num_colors;
		ar << drop_flag;
		ar << num_next;
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
		for (int num = 0; num < 16; num++)
			for (int rotate = 0; rotate < 4; rotate++)
				for (int y = 0; y < 16; y++)
					for (int x = 0; x < 16; x++)
						ar << block[num][rotate][y][x];
	}
	else
	{
		ar >> pf_width;
		ar >> pf_height;
		ar >> block_type;
		ar >> pattern_size;
		ar >> num_erase;
		ar >> erase_jouken;
		ar >> color_tate_flag >> color_yoko_flag >> color_naname_flag;
		ar >> num_patterns;
		ar >> block_random_flag;
		ar >> num_colors;
		ar >> drop_flag;
		ar >> num_next;
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
		for (int num = 0; num < 16; num++)
			for (int rotate = 0; rotate < 4; rotate++)
				for (int y = 0; y < 16; y++)
					for (int x = 0; x < 16; x++)
						ar >> block[num][rotate][y][x];
	}
}

#ifdef SHARED_HANDLERS

//�k���ł̃T�|�[�g
void CPGMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ���̃R�[�h��ύX���ăh�L�������g�̃f�[�^��`�悵�܂�
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �����n���h���[�̃T�|�[�g
void CPGMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// �h�L�������g�̃f�[�^���猟���R���e���c��ݒ肵�܂��B
	// �R���e���c�̊e������ ";" �ŋ�؂�K�v������܂�

	// ��:      strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPGMDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPGMDoc �f�f

#ifdef _DEBUG
void CPGMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPGMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPGMDoc �R�}���h
