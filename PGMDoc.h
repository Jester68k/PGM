
// PGMDoc.h : CPGMDoc クラスのインターフェイス
//


#pragma once


class CPGMDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CPGMDoc();
	DECLARE_DYNCREATE(CPGMDoc)

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 実装
public:
	int		block[16][4][16][16];	// ブロックの配列・最大サイズを用意
	int		topTen[10];
	int		pf_width, pf_height, block_type;
	UINT	drop_flag;
	int		speed[MAX_LEVEL];
	UINT	pattern_size;		// パターンのサイズ
	BOOL	color_tate_flag;			// 色縦フラグ
	BOOL	color_yoko_flag;			// 色横フラグ
	BOOL	color_naname_flag;		// 色斜めフラグ
	UINT	num_erase;			// 消滅するブロックの個数（縦・横・斜めなど）
	UINT	erase_jouken;		// 消滅条件
	UINT	num_patterns;
	BOOL	block_random_flag;
	UINT	num_colors;
	UINT	num_next;

	virtual ~CPGMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 検索ハンドラーの検索コンテンツを設定するヘルパー関数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
