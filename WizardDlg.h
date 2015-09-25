#if !defined(AFX_WIZARDDLG_H__A5373D57_2997_46D2_A37F_9CA5132B281A__INCLUDED_)
#define AFX_WIZARDDLG_H__A5373D57_2997_46D2_A37F_9CA5132B281A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg �_�C�A���O

class CWizardDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CWizardDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
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


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CWizardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CWizardDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_WIZARDDLG_H__A5373D57_2997_46D2_A37F_9CA5132B281A__INCLUDED_)
