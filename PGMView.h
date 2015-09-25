
// PGMView.h : CPGMView �N���X�̃C���^�[�t�F�C�X
//

#pragma once


class CPGMView : public CView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CPGMView();
	DECLARE_DYNCREATE(CPGMView)

// ����
public:
	CPGMDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����
public:
	int playfield[32][32];	// �v���C�t�B�[���h�̔z��E�ő�T�C�Y��p��
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

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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

#ifndef _DEBUG  // PGMView.cpp �̃f�o�b�O �o�[�W����
inline CPGMDoc* CPGMView::GetDocument() const
   { return reinterpret_cast<CPGMDoc*>(m_pDocument); }
#endif

