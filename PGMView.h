
// PGMView.h : CPGMView クラスのインターフェイス
//

#pragma once


class CPGMView : public CView
{
protected: // シリアル化からのみ作成します。
	CPGMView();
	DECLARE_DYNCREATE(CPGMView)

// 属性
public:
	CPGMDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	int playfield[32][32];	// プレイフィールドの配列・最大サイズを用意
	int playfield_sx, playfield_sy, x, y, pat, rotate, counter, mode, current_color;
	int cPlayfield[MAX_HEIGHT][MAX_WIDTH], rinsetsu_count;
	int score, next[MAX_NEXT], next_block[MAX_NEXT][MAX_HEIGHT][MAX_WIDTH];
	CAsyncSocket socket;
	virtual ~CPGMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	void InitializeBlock();
	void SearchBlock(int x, int y, int color);
	BOOL EraseBlocks();
	void CopyBlocks(int pat);
	void DropBlock();
	void DrawMovingBlock();
	void DrawBlock(CDC* pDC, int x, int y, int color);
	void DrawPlayfield();
	int CheckDropBlock();
	void NewBlock();
	//{{AFX_MSG(CPGMView)
	afx_msg void OnViewProperty();
	afx_msg void OnGamePlay();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancelMode();
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGameStop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditGenerate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // PGMView.cpp のデバッグ バージョン
inline CPGMDoc* CPGMView::GetDocument() const
   { return reinterpret_cast<CPGMDoc*>(m_pDocument); }
#endif

