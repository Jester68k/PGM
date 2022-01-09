// WizardDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CWizardDlg �_�C�A���O


CWizardDlg::CWizardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizardDlg)
	m_block_type = BLOCK_TYPE_CIRCULATE;
	m_num_colors = 0;
	m_num_patterns = 0;
	m_pfwidth = 0;
	m_pfheight = 0;
	m_block_random_flag = FALSE;
	m_pattern_size = 0;
	m_drop_flag = FALSE;
	m_erase_jouken = ERASE_LINE;
	m_num_next = 3;
	//}}AFX_DATA_INIT
}


void CWizardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardDlg)
	DDX_Control(pDX, IDC_NUM_NEXT_SPIN, m_numnextspin);
	DDX_Control(pDX, IDC_PATTERN_SIZE_SPIN, m_patternsizespin);
	DDX_Control(pDX, IDC_NUM_COLORS_SPIN, m_numcolorsspin);
	DDX_Control(pDX, IDC_NUM_PATTERNS_SPIN, m_numpatternsspin);
	DDX_Control(pDX, IDC_NUM_ERASE_SPIN, m_numerasespin);
	DDX_Control(pDX, IDC_PFWIDTHSPIN, m_pfwidthspin);
	DDX_Control(pDX, IDC_PFHEIGHTSPIN, m_pfheightspin);
	DDX_Text(pDX, IDC_PFHEIGHT, m_pfheight);
	DDV_MinMaxUInt(pDX, m_pfheight, 1, 32);
	DDX_Text(pDX, IDC_PFWIDTH, m_pfwidth);
	DDV_MinMaxUInt(pDX, m_pfwidth, 1, 32);
	DDX_Radio(pDX, IDC_ROTATE, m_block_type);
	DDX_Check(pDX, IDC_COLORNANAME, m_color_naname_flag);
	DDX_Check(pDX, IDC_COLORTATE, m_color_tate_flag);
	DDX_Check(pDX, IDC_COLORYOKO, m_color_yoko_flag);
	DDX_Text(pDX, IDC_NUM_ERASE, m_num_erase);
	DDV_MinMaxUInt(pDX, m_num_erase, 2, 20);
	DDX_Text(pDX, IDC_NUM_PATTERNS, m_num_patterns);
	DDV_MinMaxUInt(pDX, m_num_patterns, 1, 16);
	DDX_Text(pDX, IDC_NUM_COLORS, m_num_colors);
	DDV_MinMaxUInt(pDX, m_num_colors, 1, 16);
	DDX_Check(pDX, IDC_BLOCKRANDOM, m_block_random_flag);
	DDX_Text(pDX, IDC_PATTERN_SIZE, m_pattern_size);
	DDV_MinMaxUInt(pDX, m_pattern_size, 1, 16);
	DDX_Check(pDX, IDC_DROP_FLAG, m_drop_flag);
	DDX_Radio(pDX, IDC_YOKOLINE, m_erase_jouken);
	DDX_Text(pDX, IDC_NUM_NEXT, m_num_next);
	DDV_MinMaxUInt(pDX, m_num_next, 0, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardDlg, CDialog)
	//{{AFX_MSG_MAP(CWizardDlg)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_PATTERN_SIZE, &CWizardDlg::OnEnChangePatternSize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg ���b�Z�[�W �n���h��

BOOL CWizardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	m_pfwidthspin.SetRange(1,MAX_WIDTH);
	m_pfheightspin.SetRange(1,MAX_HEIGHT);
	m_patternsizespin.SetRange(1,16);
	m_numpatternsspin.SetRange(1,16);
	m_numcolorsspin.SetRange(1,16);
	m_numerasespin.SetRange(2,16);
	m_numnextspin.SetRange(0,MAX_NEXT);
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}


void CWizardDlg::OnEnChangePatternSize()
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A���̃R���g���[����
	// ���̒ʒm�𑗐M����ɂ́ACDialog::OnInitDialog() �֐����I�[�o�[���C�h���A
	// CRichEditCtrl().SetEventMask() ���֐����Ăяo���܂��B
	// OR ��Ԃ� ENM_CHANGE �t���O���}�X�N�ɓ���ČĂяo���K�v������܂��B

	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����Ă��������B
}
