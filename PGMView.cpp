
// PGMView.cpp : CPGMView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "PGM.h"
#endif

#include "resource.h"

#include "PGMDoc.h"
#include "PGMView.h"
#include "WizardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPGMView

IMPLEMENT_DYNCREATE(CPGMView, CView)

BEGIN_MESSAGE_MAP(CPGMView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_VIEW_PROPERTY, OnViewProperty)
	ON_COMMAND(ID_GAME_PLAY, OnGamePlay)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GAME_STOP, OnGameStop)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_GENERATE, OnEditGenerate)

	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CPGMView コンストラクション/デストラクション

CPGMView::CPGMView()
{
	// TODO: 構築コードをここに追加します。

}

CPGMView::~CPGMView()
{
}

BOOL CPGMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CPGMView 描画

void CPGMView::OnDraw(CDC* pDC)
{
	CPGMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	int i, pat, rotate, bx, by;
	CPen myPen(PS_SOLID, 1, RGB(0, 0, 0));
	CString str;
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	switch (mode) {
	case MODE_NORMAL:
		switch (pDoc->block_type) {
		case BLOCK_TYPE_ROTATE:
			playfield_sx = 16;
			playfield_sy = 16;
			DrawBlock(pDC, 0, 0, current_color);
			playfield_sy = 16 * 3;
			for (bx = 0; bx <= pDoc->num_colors; bx++)
				DrawBlock(pDC, bx, 0, bx);
			playfield_sy = 16 * 5;
			for (pat = 0; pat<pDoc->num_patterns; pat++)
				for (rotate = 0; rotate<4; rotate++)
					for (by = 0; by<pDoc->pattern_size; by++)
						for (bx = 0; bx<pDoc->pattern_size; bx++)
							DrawBlock(pDC, bx + pat*(pDoc->pattern_size + 1), by + rotate*(pDoc->pattern_size + 1), pDoc->block[pat][rotate][by][bx]);
			break;
		case BLOCK_TYPE_CIRCULATE:
			break;
		}
		break;
	case MODE_PLAY:
		DrawPlayfield();
		DrawMovingBlock();
		str.Format(_T("%10d"), score);
		pDC->TextOut(700, 100, _T("SCORE"));
		pDC->TextOut(700, 116, str);
		switch (pDoc->block_type) {
		case BLOCK_TYPE_ROTATE:
			for (i = 0; i < pDoc->num_next; i++)
				for (by = 0; by < pDoc->pattern_size; by++)
					for (bx = 0; bx < pDoc->pattern_size; bx++)
						DrawBlock(pDC, pDoc->pf_width + 2 + bx, i * (pDoc->pattern_size + 1) + by, next_block[i][by][bx]);
			break;
		case BLOCK_TYPE_CIRCULATE:
			for (i = 0; i<pDoc->num_next; i++)
				for (by = 0; by<pDoc->pattern_size; by++)
					DrawBlock(pDC, pDoc->pf_width + 2, i*(pDoc->pattern_size + 1) + by, next_block[i][by][0]);
			break;
		}
		break;
	}
}


// CPGMView 印刷

BOOL CPGMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CPGMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CPGMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}


// CPGMView 診断

#ifdef _DEBUG
void CPGMView::AssertValid() const
{
	CView::AssertValid();
}

void CPGMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPGMDoc* CPGMView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPGMDoc)));
	return (CPGMDoc*)m_pDocument;
}
#endif //_DEBUG


// CPGMView メッセージ ハンドラー



void CPGMView::OnViewProperty()
{
	CPGMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CWizardDlg wizard_dlg;

	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	wizard_dlg.m_pfwidth = pDoc->pf_width;	// playfield width
	wizard_dlg.m_pfheight = pDoc->pf_height;	// playfield height
	wizard_dlg.m_block_type = pDoc->block_type;
	wizard_dlg.m_pattern_size = pDoc->pattern_size;
	wizard_dlg.m_num_erase = pDoc->num_erase;
	wizard_dlg.m_erase_jouken = pDoc->erase_jouken;
	wizard_dlg.m_color_tate_flag = pDoc->color_tate_flag;
	wizard_dlg.m_color_yoko_flag = pDoc->color_yoko_flag;
	wizard_dlg.m_color_naname_flag = pDoc->color_naname_flag;
	wizard_dlg.m_num_patterns = pDoc->num_patterns;
	wizard_dlg.m_block_random_flag = pDoc->block_random_flag;
	wizard_dlg.m_num_colors = pDoc->num_colors;
	wizard_dlg.m_drop_flag = pDoc->drop_flag;
	if (wizard_dlg.DoModal() == IDOK) {
		pDoc->pf_width = wizard_dlg.m_pfwidth;
		pDoc->pf_height = wizard_dlg.m_pfheight;
		pDoc->block_type = wizard_dlg.m_block_type;
		pDoc->pattern_size = wizard_dlg.m_pattern_size;
		pDoc->num_erase = wizard_dlg.m_num_erase;
		pDoc->erase_jouken = wizard_dlg.m_erase_jouken;
		pDoc->color_tate_flag = wizard_dlg.m_color_tate_flag;
		pDoc->color_naname_flag = wizard_dlg.m_color_naname_flag;
		pDoc->color_yoko_flag = wizard_dlg.m_color_yoko_flag;
		pDoc->num_patterns = wizard_dlg.m_num_patterns;
		pDoc->block_random_flag = wizard_dlg.m_block_random_flag;
		pDoc->num_colors = wizard_dlg.m_num_colors;
		pDoc->drop_flag = wizard_dlg.m_drop_flag;
	}
	InvalidateRect(NULL, TRUE);
}

void CPGMView::OnGamePlay()
{
	CPGMDoc* pDoc = GetDocument();
	int x, y;
	CRect rect;

	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	GetClientRect(&rect);
	for (y = 0; y<MAX_HEIGHT; y++)
		for (x = 0; x<MAX_WIDTH; x++)
			playfield[y][x] = 0;
	drop_counter = 0;
	base_points = 10;
	pat = 0;
	mode = MODE_PLAY;
	playfield_sx = (rect.right - pDoc->pf_width * 16) / 2;
	playfield_sy = (rect.bottom - pDoc->pf_height * 16) / 2;
	score = 0;
	InitializeBlock();
	NewBlock();
	InvalidateRect(NULL, TRUE);
	SetTimer(0, 100, NULL);
}

void CPGMView::OnTimer(UINT nIDEvent)
{
	CPGMDoc* pDoc = GetDocument();

	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (++drop_counter>10) {
		drop_counter = 0;
		++y;
		if (CheckDropBlock()) {
			--y;
			DropBlock();
			base_points = 10;
			if (pDoc->drop_flag)
				while (EraseBlocks()) {
					base_points *= 2;
					InvalidateRect(NULL, FALSE);
				}
			else {
				EraseBlocks();
			}
			NewBlock();
		}
		InvalidateRect(NULL, FALSE);
	}
	CView::OnTimer(nIDEvent);
}

void CPGMView::OnCancelMode()
{
	CView::OnCancelMode();

	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください

}

void CPGMView::NewBlock()
{
	CPGMDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	CRect rect;
	int i, bx, by;

	switch (pDoc->block_type) {
	case BLOCK_TYPE_ROTATE:
		pat = next[0];
		for (i = 0; i < pDoc->num_next - 1; i++) {
			for (i = 0; i < pDoc->num_next - 1; i++) {
				next[i] = next[i + 1];
				for (by = 0; by < pDoc->pattern_size; by++)
					for (bx = 0; bx < pDoc->pattern_size; bx++)
						next_block[i][by][bx] = next_block[i + 1][by][bx];
			}

		}
		next[pDoc->num_next - 1] = rand() % pDoc->num_patterns;
		if (pDoc->block_random_flag) {
			for (by = 0; by < pDoc->pattern_size; by++)
				for (bx = 0; bx < pDoc->pattern_size; bx++)
					if (pDoc->block[pat][0][by][bx])
						pDoc->block[pat][0][by][bx] = rand() % pDoc->num_colors + 1;
			CopyBlocks(pat);
		}
		for (by = 0; by < pDoc->pattern_size; by++)
				for (bx = 0; bx < pDoc->pattern_size; bx++)
					next_block[pDoc->num_next-1][by][bx] = pDoc->block[next[pDoc->num_next-1]][0][by][bx];
		x = (pDoc->pf_width - pDoc->pattern_size) / 2;
		break;
	case BLOCK_TYPE_CIRCULATE:
		for (by = 0; by<pDoc->pattern_size; by++)
			pDoc->block[0][0][by][0] = next_block[0][by][0];
		for (i = 0; i<pDoc->num_next - 1; i++)
			for (by = 0; by<pDoc->pattern_size; by++)
				next_block[i][by][0] = next_block[i + 1][by][0];
		for (by = 0; by<pDoc->pattern_size; by++)
			next_block[pDoc->num_next - 1][by][0] = rand() % pDoc->num_colors + 1;
		x = (pDoc->pf_width - 1) / 2;
		break;
	}
	rotate = 0;
	y = 0;
	if (CheckDropBlock()) {
		DropBlock();
		DrawPlayfield();
		KillTimer(0);
		GetClientRect(&rect);
		rect.top = (rect.bottom-16)/ 2;
		pDC->DrawText(_T("GAME OVER"), &rect, DT_CENTER | DT_VCENTER);
		mode = MODE_GAMEOVER;
	}
}

void CPGMView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	KillTimer(0);
}

int CPGMView::CheckDropBlock()
{
	CPGMDoc* pDoc = GetDocument();
	int bx, by;

	switch (pDoc->block_type) {
	case BLOCK_TYPE_ROTATE:
		for (by = 0; by<pDoc->pattern_size; by++)
			for (bx = 0; bx<pDoc->pattern_size; bx++) {
				if ((x + bx<0 || x + bx >= pDoc->pf_width) && pDoc->block[pat][rotate][by][bx])
					return 1;
				if (y + by >= pDoc->pf_height && pDoc->block[pat][rotate][by][bx])
					return 1;
				if (x + bx >= 0 && x + bx<pDoc->pf_width && y + by<pDoc->pf_height && pDoc->block[pat][rotate][by][bx] && playfield[y + by][x + bx])
					return 1;
			}
		break;
	case BLOCK_TYPE_CIRCULATE:
		if (y + pDoc->pattern_size>pDoc->pf_height)
			return 1;
		if (x<0 || x >= pDoc->pf_width)
			return 1;
		for (by = 0; by<pDoc->pattern_size; by++)
			if (playfield[y + by][x] && pDoc->block[0][0][by][0])
				return 1;
		break;
	}
	return 0;
}

void CPGMView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CPGMDoc* pDoc = GetDocument();
	int color;

	if (mode == MODE_PLAY) {
		switch (nChar) {
		case VK_LEFT:
		case VK_NUMPAD4:
			x--;
			if (CheckDropBlock())
				x++;
			break;
		case VK_RIGHT:
		case VK_NUMPAD6:
			x++;
			if (CheckDropBlock())
				x--;
			break;
		case VK_DOWN:
		case VK_NUMPAD2:
			y++;
			if (CheckDropBlock()) {
				y--;
				DropBlock();
				if (pDoc->drop_flag)
					while (EraseBlocks())
						InvalidateRect(NULL, FALSE);
				else
					EraseBlocks();
				NewBlock();
				drop_counter = 0;
			}
			break;
		case VK_SPACE:
		case VK_NUMPAD5:
			switch (pDoc->block_type) {
			case BLOCK_TYPE_ROTATE:
				if (++rotate >= 4)
					rotate = 0;
				if (CheckDropBlock()) {
					--rotate;
					if (rotate<0)
						rotate = 4 - 1;
				}
				break;
			case BLOCK_TYPE_CIRCULATE:
				color = pDoc->block[0][0][pDoc->pattern_size - 1][0];
				for (int by = pDoc->pattern_size - 1 - 1; by >= 0; by--)
					pDoc->block[pat][0][by + 1][0] = pDoc->block[pat][0][by][0];
				pDoc->block[pat][0][0][0] = color;
				break;
			}
			break;
		}
	}
	InvalidateRect(NULL, FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPGMView::DrawPlayfield()
{
	CPGMDoc* pDoc = GetDocument();
	CBrush myBrush;
	CBrush* pOldBrush;
	CClientDC dc(this);

	for (int y = 0; y<pDoc->pf_height; y++)
		for (int x = 0; x<pDoc->pf_width; x++) {
			myBrush.CreateSolidBrush(color_code[playfield[y][x]]);
			pOldBrush = dc.SelectObject(&myBrush);
			dc.Rectangle(playfield_sx + x * 16, playfield_sy + y * 16, playfield_sx + (x + 1) * 16 - 1, playfield_sy + (y + 1) * 16 - 1);
			dc.SelectObject(pOldBrush);
			myBrush.DeleteObject();
		}
}

void CPGMView::DrawBlock(CDC* pDC, int x, int y, int color)
{
	CPGMDoc* pDoc = GetDocument();
	CBrush myBrush;
	CBrush* pOldBrush;

	myBrush.CreateSolidBrush(color_code[color]);
	pOldBrush = pDC->SelectObject(&myBrush);
	pDC->Rectangle(playfield_sx + x * 16, playfield_sy + y * 16, playfield_sx + (x + 1) * 16 - 1, playfield_sy + (y + 1) * 16 - 1);
	pDC->SelectObject(pOldBrush);
	myBrush.DeleteObject();
}

void CPGMView::OnGameStop()
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CPGMDoc* pDoc = GetDocument();

	KillTimer(0);
	mode = MODE_NORMAL;
	InvalidateRect(NULL, TRUE);
}

void CPGMView::DrawMovingBlock()
{
	CPGMDoc* pDoc = GetDocument();
	CClientDC dc(this);
	int bx, by;

	switch (pDoc->block_type) {
	case BLOCK_TYPE_ROTATE:
		for (by = 0; by<pDoc->pattern_size; by++)
			for (bx = 0; bx<pDoc->pattern_size; bx++)
				if (x + bx >= 0 && x + bx<pDoc->pf_width && y + by<pDoc->pf_height && pDoc->block[pat][rotate][by][bx])
					DrawBlock(&dc, x + bx, y + by, pDoc->block[pat][rotate][by][bx]);
		break;
	case BLOCK_TYPE_CIRCULATE:
		for (by = 0; by<pDoc->pattern_size; by++)
			DrawBlock(&dc, x, y + by, pDoc->block[0][0][by][0]);
		break;
	}
}

void CPGMView::DropBlock()
{
	CPGMDoc* pDoc = GetDocument();
	int bx, by;

	switch (pDoc->block_type) {
	case BLOCK_TYPE_ROTATE:
		for (by = 0; by<pDoc->pattern_size; by++)
			for (bx = 0; bx<pDoc->pattern_size; bx++)
				if (pDoc->block[pat][rotate][by][bx])
					playfield[y + by][x + bx] = pDoc->block[pat][rotate][by][bx];
		break;
	case BLOCK_TYPE_CIRCULATE:
		for (by = 0; by<pDoc->pattern_size; by++)
			if (pDoc->block[0][0][by][0])
				playfield[y + by][x] = pDoc->block[0][0][by][0];
		break;
	}
}

void CPGMView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPGMDoc* pDoc = GetDocument();

	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	int bx, by, px, py, color;

	switch (mode) {
	case MODE_NORMAL:
		switch (pDoc->block_type) {
		case BLOCK_TYPE_ROTATE:
			px = point.x - playfield_sx;
			py = point.y - playfield_sy;
			pat = px / ((pDoc->pattern_size + 1) * 16);
			bx = px % ((pDoc->pattern_size + 1) * 16) / 16;
			rotate = py / ((pDoc->pattern_size + 1) * 16);
			by = py % ((pDoc->pattern_size + 1) * 16) / 16;
			if (pat >= 0 && pat<16 && rotate >= 0 && rotate<4 && bx >= 0 && bx<pDoc->pattern_size && by >= 0 && by<pDoc->pattern_size)
				pDoc->block[pat][rotate][by][bx] = current_color;
			else
				if (point.x >= 16 && point.x<16 + 16 * (pDoc->num_colors + 1) && point.y >= 16 * 3 && point.y<16 * 4) {
					color = (point.x - 16) / 16;
					if (color >= 0 && color <= pDoc->num_colors)
						current_color = color;
				}
			break;
		}
		InvalidateRect(NULL, FALSE);
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CPGMView::OnEditGenerate()
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CPGMDoc* pDoc = GetDocument();
	int bx, by, bx2, by2;

	for (pat = 0; pat<pDoc->num_patterns; pat++)
		for (rotate = 0; rotate<4 - 1; rotate++)
			for (by = 0, bx2 = pDoc->pattern_size - 1; by<pDoc->pattern_size; by++, bx2--)
				for (bx = 0, by2 = 0; bx<pDoc->pattern_size; bx++, by2++)
					pDoc->block[pat][rotate + 1][by2][bx2] = pDoc->block[pat][rotate][by][bx];
	InvalidateRect(NULL, FALSE);
}


void CPGMView::CopyBlocks(int pat)
{
	CPGMDoc* pDoc = GetDocument();
	int bx, by, bx2, by2;

	for (rotate = 0; rotate<4 - 1; rotate++)
		for (by = 0, bx2 = pDoc->pattern_size - 1; by<pDoc->pattern_size; by++, bx2--)
			for (bx = 0, by2 = 0; bx<pDoc->pattern_size; bx++, by2++)
				pDoc->block[pat][rotate + 1][by2][bx2] = pDoc->block[pat][rotate][by][bx];
}

BOOL CPGMView::EraseBlocks()
{
	CPGMDoc* pDoc = GetDocument();
	int flag = 0, bx, by, bx2, by2, blk_count, erase_sy, line_count, sx, sy;
	BOOL rensa_flag = FALSE;

	for (by = 0; by < pDoc->pf_height; by++)
		for (bx = 0; bx < pDoc->pf_width; bx++)
			erasing_playfield[by][bx] = 0;

	switch (pDoc->erase_jouken) {
	case ERASE_YOKO1LINE:
		erase_sy = -1;
		line_count = 0;
		for (by = pDoc->pf_height - 1; by >= 0; by--) {
			blk_count = 0;
			for (bx = 0; bx < pDoc->pf_width; bx++) {
				if (playfield[by][bx])
					++blk_count;
			}
			if (blk_count == pDoc->pf_width) {
				line_count++;
				if (line_count == 1)
					erase_sy = by;
			}
		}
		if (line_count)
			score += base_points * pow((double)2, (double)line_count - 1);
		break;
	case ERASE_LINE:
		// 一直線・縦
		if (pDoc->color_tate_flag) {
			for (bx = 0; bx < pDoc->pf_width; bx++) {
				blk_count = 1;
				sy = 0;
				for (by = 1; by < pDoc->pf_height - 1; by++) {
					if (playfield[by][bx] != 0 && playfield[by - 1][bx] == playfield[by][bx]) {
						if (blk_count == 1) {
							blk_count = 2;
							sy = by - 1;
						}
						else
							blk_count++;
					}
					else {
						if (blk_count >= pDoc->num_erase) {
							for (by2 = sy; by2 < by; by2++)
								erasing_playfield[by2][bx] = 1;
						}
						blk_count = 1;
					}
				}
				if (blk_count >= pDoc->num_erase) {
					for (by2 = sy; by2 < by; by2++)
						erasing_playfield[by2][bx] = 1;
				}
			}
		}
		// 一直線・横
		if (pDoc->color_yoko_flag) {
			for (by = 0; by < pDoc->pf_height; by++) {
				sx = 0;
				blk_count = 1;
				for (bx = 1; bx < pDoc->pf_width; bx++) {
					if (playfield[by][bx] != 0 && playfield[by][bx - 1] == playfield[by][bx]) {
						if (blk_count == 1) {
							blk_count = 2;
							sx = bx - 1;
						}
						else
							blk_count++;
					}
					else {
						if (blk_count >= pDoc->num_erase) {
							for (bx2 = sx; bx2 < bx; bx2++)
								erasing_playfield[by][bx2] = 1;
						}
						blk_count = 1;
					}
				}
				if (blk_count >= pDoc->num_erase) {
					for (bx2 = sx; bx2 < bx; bx2++)
						erasing_playfield[by][bx2] = 1;
				}
			}
		}
		if (pDoc->color_naname_flag) {
			//　右下方向
			for (by = 0; by <= pDoc->pf_height - 1 - 1; by++) {
				blk_count = 1;
				sx = 0;
				sy = by;
				for (bx2 = 1, by2 = by + 1; bx2 <= pDoc->pf_width - 1; bx2++, by2++) {
					if (playfield[by2][bx2] != 0 && playfield[by2 - 1][bx2 - 1] == playfield[by2][bx2]) {
						if (blk_count == 0) {
							blk_count = 2;
							sx = bx - 1;
							sy = by - 1;
						}
						else
							blk_count++;
					}
					else {
						if (blk_count >= pDoc->num_erase) {
							for (; sx <= bx2; sx++, sy++)
								erasing_playfield[sy][sx] = 1;
						}
						blk_count = 1;
					}
					if (blk_count >= pDoc->num_erase) {
						for (; sx <= bx2; sx++, sy++)
							erasing_playfield[sy][sx] = 1;
					}
				}
			}
			for (bx = 1; bx <= pDoc->pf_width - 1 - 1; bx++) {
				blk_count = 1;
				sx = bx;
				sy = 0;
				for (bx2 = bx + 1, by2 = 1; by2 <= pDoc->pf_height - 1; bx2++, by2++) {
					if (playfield[by2][bx2] != 0 && playfield[by2 - 1][bx2 - 1] == playfield[by2][bx2]) {
						if (blk_count == 0) {
							blk_count = 1;
							sx = bx - 1;
							sy = by - 1;
						}
						else
							blk_count++;
					}
					else {
						if (blk_count >= pDoc->num_erase) {
							for (; sx <= bx2; sx++, sy++)
								erasing_playfield[sy][sx] = 1;
						}
						blk_count = 1;
					}
				}
				if (blk_count >= pDoc->num_erase)
					for (; sx <= bx2; sx++, sy++)
						erasing_playfield[sy][sx] = -1;
			}
			// 右上方向
			for (by = pDoc->pf_height - 1; by > 0; by--) {
				blk_count = 1;
				sx = 0;
				sy = by;
				for (bx2 = 1, by2 = by - 1; bx2 <= pDoc->pf_width - 1 - 1; bx2++, by2--) {
					if (playfield[by2][bx2] != 0 && playfield[by2 + 1][bx2 - 1] == playfield[by2][bx2]) {
						if (blk_count == 1) {
							blk_count = 2;
							sx = bx2 - 1;
							sy = by2 + 1;
						}
						else
							blk_count++;
					}
					else {
						if (blk_count >= pDoc->num_erase) {
							for (; sx <= bx2; sx++, sy--)
								erasing_playfield[sy][sx] = 1;
						}
						blk_count = 1;
					}
				}
				if (blk_count >= pDoc->num_erase)
					for (; sx <= bx2; sx++, sy--)
						erasing_playfield[by2][bx2] = 1;
			}
			for (bx = 1, by = pDoc->pf_height - 1; bx <= pDoc->pf_width - 1 - 1; bx++) {
				blk_count = 1;
				sx = bx;
				sy = 0;
				for (bx2 = bx + 1, by2 = pDoc->pf_height - 1; bx2 <= pDoc->pf_width - 1 - 1; bx2++, by2--) {
					if (playfield[by2][bx2] != 0 && playfield[by2 + 1][bx2 - 1] == playfield[by2][bx2]) {
						if (blk_count == 0) {
							blk_count = 2;
							sx = bx2 - 1;
							sy = by2 + 1;
						}
						else
							blk_count++;
					}
					else {
						if (blk_count >= pDoc->num_erase) {
							for (; sx <= bx2; sx++, sy--)
								erasing_playfield[sy][sx] = 1;
						}
						blk_count = 1;
					}
				}
				if (blk_count >= pDoc->num_erase) {
					for (; sx <= bx2; sx++, sy--)
						erasing_playfield[sy][sx] = 1;
				}
			}
		}
		break;
	case ERASE_RINSETSU:
		for (by = 0; by < pDoc->pf_height; by++)
			for (bx = 0; bx < pDoc->pf_width; bx++) {
				if (!erasing_playfield[by][bx] && playfield[by][bx]) { // 消えるブロックは処理する必要がないためこうしている
					for (by2 = 0; by2 < pDoc->pf_height; by2++)
						for (bx2 = 0; bx2 < pDoc->pf_width; bx2++)
							cPlayfield[by2][bx2] = 0;
					cPlayfield[by][bx] = playfield[by][bx];
					rinsetsu_count = 1;
					SearchBlock(bx, by);
					if (rinsetsu_count >= pDoc->num_erase) {
						for (by2 = 0; by2 < pDoc->pf_height; by2++)
							for (bx2 = 0; bx2 < pDoc->pf_width; bx2++)
								if (cPlayfield[by2][bx2])
									erasing_playfield[by2][bx2] = 1;
					}
				}
			}
		break;
	}
	// ブロックの消去処理
	switch (pDoc->erase_jouken) {
	case ERASE_YOKO1LINE:
		if (line_count) {
			int loop_cnt;
			for (by = erase_sy, loop_cnt=erase_sy-line_count; loop_cnt; --by, --loop_cnt)
				for (bx = 0; bx < pDoc->pf_width; bx++)
					playfield[by][bx] = playfield[by-line_count][bx];
			for (loop_cnt=line_count; loop_cnt; --by, --loop_cnt)
				for (bx = 0; bx < pDoc->pf_width; bx++)
					playfield[by][bx] = 0;
		}
		break;
	default:
		for (by = 0; by < pDoc->pf_height; by++) {
			for (bx = 0; bx < pDoc->pf_width; bx++) {
				if (erasing_playfield[by][bx]) {
					playfield[by][bx] = 0;
					rensa_flag = TRUE;
					if (pDoc->erase_jouken != ERASE_YOKO1LINE)
						score += base_points;
				}
			}
		}
		break;
	}

	// 固定されたブロックの落下処理
	if (pDoc->drop_flag) {
		for (bx = 0; bx<pDoc->pf_width; bx++) {
			for (by = by2 = pDoc->pf_height-1; by2 >= 0; by--, by2--) {
				while (by2>0 && playfield[by2][bx]==0)
					by2--;
				playfield[by][bx] = playfield[by2][bx];
			}
			if (by2<by)
				for (; by >= 0; by--)
					playfield[by][bx] = 0;
		}
	}
	return rensa_flag;
}

void CPGMView::InitializeBlock()
{
	CPGMDoc* pDoc = GetDocument();
	int i;

	for (i = 0; i<pDoc->num_next; i++) {
		next[i] = 0;
		for (y = 0; y<pDoc->pattern_size; y++)
			for (x = 0; x<pDoc->pattern_size; x++)
				next_block[i][y][x] = 0;
	}
	for (i = 0; i<pDoc->num_next; i++)
		NewBlock();
}

void CPGMView::SearchBlock(int x, int y)
{
	CPGMDoc* pDoc = GetDocument();
	int color;

	if (x<0 || x >= pDoc->pf_width || y<0 || y >= pDoc->pf_height)
		return;
	color = playfield[y][x];
	if (0 == color) 
		return;
	if (pDoc->color_tate_flag) {
		if (y + 1<pDoc->pf_height && playfield[y + 1][x] == color && 0==cPlayfield[y+1][x]) {
			cPlayfield[y+1][x] = color;
			rinsetsu_count++;
			SearchBlock(x, y + 1);
		}
		if (y - 1 >= 0 && playfield[y - 1][x] == color && 0 == cPlayfield[y - 1][x]) {
			cPlayfield[y-1][x] = color;
			rinsetsu_count++;
			SearchBlock(x, y - 1);
		}
	}
	if (pDoc->color_yoko_flag) {
		if (x + 1 < pDoc->pf_width && playfield[y][x + 1] == color && 0 == cPlayfield[y][x + 1]) {
			cPlayfield[y][x + 1] = color;
			rinsetsu_count++;
			SearchBlock(x + 1, y);
		}
		if (x - 1 >= 0 && playfield[y][x - 1] == color && 0 == cPlayfield[y][x - 1]) {
			cPlayfield[y][x - 1] = color;
			rinsetsu_count++;
			SearchBlock(x - 1, y);
		}
	}

	if (pDoc->color_naname_flag) {
		if (y + 1<pDoc->pf_height && x + 1<pDoc->pf_width && playfield[y + 1][x + 1]==color && 0 == cPlayfield[y + 1][x + 1]) {
			cPlayfield[y + 1][x + 1] = color;
			rinsetsu_count++;
			SearchBlock(x + 1, y + 1);
		}
		if (y - 1 >= 0 && x + 1 < pDoc->pf_width && playfield[y - 1][x + 1] == color && 0 == cPlayfield[y - 1][x + 1]) {
			cPlayfield[y - 1][x + 1] = color;
			rinsetsu_count++;
			SearchBlock(x + 1, y - 1);
		}
	if (y + 1 < pDoc->pf_height && x - 1 >= 0 && playfield[y + 1][x - 1] == color && 0 == cPlayfield[y + 1][x - 1]) {
			cPlayfield[y + 1][x - 1] = color;
			rinsetsu_count++;
			SearchBlock(x - 1, y + 1);
		}
		if (y - 1 >= 0 && x + 1 < pDoc->pf_width && playfield[y - 1][x + 1] == color && 0 == cPlayfield[y - 1][x + 1]) {
			cPlayfield[y - 1][x + 1] = color;
			rinsetsu_count++;
			SearchBlock(x - 1, y - 1);
		}
	}
}

int CPGMView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	score = 0;
	mode = MODE_NORMAL;
	current_color = 7;	// white
	return 0;
}
