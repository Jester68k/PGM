
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
	block_type = wizard_dlg.m_blocktype = 1;			// 落下ブロックの変化タイプ：循環（縦）
	pattern_size = wizard_dlg.m_patternsize = 3;		// 横１個
	shoumetsu_num = wizard_dlg.m_shoumetsu_num = 3;		// ３個以上
	shoumetsu_jouken = wizard_dlg.m_shoumetsu_jouken = SHOUMETSU_LINE;	// 横一列揃い
	colornaname = wizard_dlg.m_colornaname = TRUE;
	colortate = wizard_dlg.m_colortate = TRUE;
	coloryoko = wizard_dlg.m_coloryoko = TRUE;
	pattern_num = wizard_dlg.m_pattern_num = 1;
	blockrandom = wizard_dlg.m_blockrandom = TRUE;
	blockcolornum = wizard_dlg.m_blockcolornum = 7;
	drop_flag = wizard_dlg.m_drop_flag = TRUE;
	next_num = wizard_dlg.m_nextnum = 3;
	if (wizard_dlg.DoModal() == IDOK) {
		pf_width = wizard_dlg.m_pfwidth;
		pf_height = wizard_dlg.m_pfheight;
		block_type = wizard_dlg.m_blocktype;
		pattern_size = wizard_dlg.m_patternsize;
		shoumetsu_num = wizard_dlg.m_shoumetsu_num;
		shoumetsu_jouken = wizard_dlg.m_shoumetsu_jouken;
		colornaname = wizard_dlg.m_colornaname;
		colortate = wizard_dlg.m_colortate;
		coloryoko = wizard_dlg.m_coloryoko;
		pattern_num = wizard_dlg.m_pattern_num;
		blockrandom = wizard_dlg.m_blockrandom;
		blockcolornum = wizard_dlg.m_blockcolornum;
		drop_flag = wizard_dlg.m_drop_flag;
		next_num = wizard_dlg.m_nextnum;
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
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
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
