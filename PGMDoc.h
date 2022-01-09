
// PGMDoc.h : CPGMDoc �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CPGMDoc : public CDocument
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CPGMDoc();
	DECLARE_DYNCREATE(CPGMDoc)

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ����
public:
	int		block[16][4][16][16];	// �u���b�N�̔z��E�ő�T�C�Y��p��
	int		topTen[10];
	int		pf_width, pf_height, block_type;
	UINT	drop_flag;
	int		speed[MAX_LEVEL];
	UINT	pattern_size;		// �p�^�[���̃T�C�Y
	BOOL	color_tate_flag;			// �F�c�t���O
	BOOL	color_yoko_flag;			// �F���t���O
	BOOL	color_naname_flag;		// �F�΂߃t���O
	UINT	num_erase;			// ���ł���u���b�N�̌��i�c�E���E�΂߂Ȃǁj
	UINT	erase_jouken;		// ���ŏ���
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

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �����n���h���[�̌����R���e���c��ݒ肷��w���p�[�֐�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
