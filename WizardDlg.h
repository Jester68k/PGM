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
	CSpinButtonCtrl	m_nextnumspin;
	CSpinButtonCtrl	m_patternsizespin;
	CSpinButtonCtrl	m_patternwidthspin;
	CSpinButtonCtrl	m_patternheightspin;
	CSpinButtonCtrl	m_blockcolornumspin;
	CSpinButtonCtrl	m_patternspin;
	CSpinButtonCtrl	m_shoumetsuspin;
	CSpinButtonCtrl	m_pfwidthspin;
	CSpinButtonCtrl	m_pfheightspin;
	UINT	m_pfheight;
	UINT	m_pfwidth;
	int	m_blocktype;
	BOOL	m_colornaname;
	BOOL	m_colortate;
	BOOL	m_coloryoko;
	UINT	m_shoumetsu_num;
	UINT	m_pattern_num;
	UINT	m_blockcolornum;
	UINT	m_blockshapenum;
	UINT	m_patternheight;
	UINT	m_patternwidth;
	BOOL	m_blockrandom;
	UINT	m_patternsize;
	BOOL	m_drop_flag;
	int		m_shoumetsu_jouken;
	UINT	m_nextnum;
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_WIZARDDLG_H__A5373D57_2997_46D2_A37F_9CA5132B281A__INCLUDED_)
