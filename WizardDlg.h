#if !defined(AFX_WIZARDDLG_H__A5373D57_2997_46D2_A37F_9CA5132B281A__INCLUDED_)
#define AFX_WIZARDDLG_H__A5373D57_2997_46D2_A37F_9CA5132B281A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg ダイアログ

class CWizardDlg : public CDialog
{
// コンストラクション
public:
	CWizardDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CWizardDlg)
	enum { IDD = IDD_WIZARD };
	CSpinButtonCtrl	m_numnextspin;
	CSpinButtonCtrl	m_patternsizespin;
	CSpinButtonCtrl	m_numcolorsspin;
	CSpinButtonCtrl	m_numpatternsspin;
	CSpinButtonCtrl	m_numerasespin;
	CSpinButtonCtrl	m_pfwidthspin;
	CSpinButtonCtrl	m_pfheightspin;
	UINT	m_pfheight;
	UINT	m_pfwidth;
	int		m_block_type;
	BOOL	m_color_tate_flag;
	BOOL	m_color_yoko_flag;
	BOOL	m_color_naname_flag;
	int		m_erase_jouken;
	UINT	m_num_erase;
	UINT	m_num_colors;
	UINT	m_num_patterns;
	UINT	m_pf_height;
	UINT	m_pf_width;
	BOOL	m_block_random_flag;
	UINT	m_pattern_size;
	BOOL	m_drop_flag;
	int		m_shoumetsu_jouken;
	UINT	m_num_next;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CWizardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CWizardDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangePatternSize();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_WIZARDDLG_H__A5373D57_2997_46D2_A37F_9CA5132B281A__INCLUDED_)
