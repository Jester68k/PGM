// WizardDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PGM.h"
#include "WizardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg ダイアログ


CWizardDlg::CWizardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizardDlg)
	m_pattern_num = 0;
	m_blockcolornum = 0;
	m_blockshapenum = 0;
	m_patternheight = 0;
	m_patternwidth = 0;
	m_blockrandom = FALSE;
	m_patternsize = 0;
	m_drop_flag = FALSE;
	m_shoumetsu_jouken = -1;
	m_nextnum = 3;
	//}}AFX_DATA_INIT
}


void CWizardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardDlg)
	DDX_Control(pDX, IDC_NEXTNUMSPIN, m_nextnumspin);
	DDX_Control(pDX, IDC_PATTERNSIZESPIN, m_patternsizespin);
	DDX_Control(pDX, IDC_BLOCKCOLORNUMSPIN, m_blockcolornumspin);
	DDX_Control(pDX, IDC_PATTERN_NUM_SPIN, m_patternspin);
	DDX_Control(pDX, IDC_SHOUMETSU_SPIN, m_shoumetsuspin);
	DDX_Control(pDX, IDC_PFWIDTHSPIN, m_pfwidthspin);
	DDX_Control(pDX, IDC_PFHEIGHTSPIN, m_pfheightspin);
	DDX_Text(pDX, IDC_PFHEIGHT, m_pfheight);
	DDV_MinMaxUInt(pDX, m_pfheight, 1, 32);
	DDX_Text(pDX, IDC_PFWIDTH, m_pfwidth);
	DDV_MinMaxUInt(pDX, m_pfwidth, 1, 32);
	DDX_Radio(pDX, IDC_ROTATE, m_blocktype);
	DDX_Check(pDX, IDC_COLORNANAME, m_colornaname);
	DDX_Check(pDX, IDC_COLORTATE, m_colortate);
	DDX_Check(pDX, IDC_COLORYOKO, m_coloryoko);
	DDX_Text(pDX, IDC_SHOUMETSU_NUM, m_shoumetsu_num);
	DDV_MinMaxUInt(pDX, m_shoumetsu_num, 2, 32);
	DDX_Text(pDX, IDC_PATTERN_NUM, m_pattern_num);
	DDV_MinMaxUInt(pDX, m_pattern_num, 1, 16);
	DDX_Text(pDX, IDC_BLOCKCOLORNUM, m_blockcolornum);
	DDV_MinMaxUInt(pDX, m_blockcolornum, 1, 16);
	DDX_Check(pDX, IDC_BLOCKRANDOM, m_blockrandom);
	DDX_Text(pDX, IDC_PATTERNSIZE, m_patternsize);
	DDV_MinMaxUInt(pDX, m_patternsize, 1, 16);
	DDX_Check(pDX, IDC_DROP_FLAG, m_drop_flag);
	DDX_Radio(pDX, IDC_YOKOLINE, m_shoumetsu_jouken);
	DDX_Text(pDX, IDC_NEXTNUM, m_nextnum);
	DDV_MinMaxUInt(pDX, m_nextnum, 0, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardDlg, CDialog)
	//{{AFX_MSG_MAP(CWizardDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg メッセージ ハンドラ

BOOL CWizardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_pfwidthspin.SetRange(1,MAX_WIDTH);
	m_pfheightspin.SetRange(1,MAX_HEIGHT);
	m_patternsizespin.SetRange(1,16);
	m_patternspin.SetRange(1,16);
	m_blockcolornumspin.SetRange(1,16);
	m_shoumetsuspin.SetRange(2,16);
	m_nextnumspin.SetRange(0,MAX_NEXT);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
