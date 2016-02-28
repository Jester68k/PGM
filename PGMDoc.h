
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
	int block[16][4][16][16];	// �u���b�N�̔z��E�ő�T�C�Y��p��
	int topTen[10];
	int pf_width, pf_height, block_type, drop_flag;
	int speed[MAX_LEVEL];
	UINT	pattern_size;
	BOOL	colornaname;
	BOOL	colortate;
	BOOL	coloryoko;
	UINT	shoumetsu_num;		// ���ł���u���b�N�̌��i�c�E���E�΂߂Ȃǁj
	UINT	shoumetsu_jouken;	// ���ŏ���
	UINT	pattern_num;
	BOOL	blockrandom;
	UINT	blockcolornum;
	UINT	next_num;

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
