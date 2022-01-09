
// PGMDoc.cpp : CPGMDoc クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
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


// CPGMDoc コンストラクション/デストラクション

CPGMDoc::CPGMDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

}

CPGMDoc::~CPGMDoc()
{
}

BOOL CPGMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。
	CWizardDlg wizard_dlg;

	int x, y, rotate, num;

	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	for (num = 0; num<16; num++)
		for (rotate = 0; rotate<4; rotate++)
			for (y = 0; y<16; y++)
				for (x = 0; x<16; x++)
					block[num][rotate][y][x] = 0;
	pf_width = wizard_dlg.m_pfwidth = 10;
	pf_height = wizard_dlg.m_pfheight = 20;
	block_type = wizard_dlg.m_block_type = 1;			// 落下ブロックの変化タイプ：循環（縦）
	pattern_size = wizard_dlg.m_pattern_size = 3;		// 横１個
	num_erase = wizard_dlg.m_num_erase = 3;		// ３個以上
	erase_jouken = wizard_dlg.m_erase_jouken = ERASE_LINE;	// 一列揃い
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


// CPGMDoc シリアル化

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
		// TODO: 格納するコードをここに追加してください。
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
		// TODO: 格納するコードをここに追加してください。
		for (int num = 0; num < 16; num++)
			for (int rotate = 0; rotate < 4; rotate++)
				for (int y = 0; y < 16; y++)
					for (int x = 0; x < 16; x++)
						ar >> block[num][rotate][y][x];
	}
}

#ifdef SHARED_HANDLERS

//縮小版のサポート
void CPGMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// このコードを変更してドキュメントのデータを描画します
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

// 検索ハンドラーのサポート
void CPGMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ドキュメントのデータから検索コンテンツを設定します。
	// コンテンツの各部分は ";" で区切る必要があります

	// 例:      strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CPGMDoc 診断

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


// CPGMDoc コマンド
