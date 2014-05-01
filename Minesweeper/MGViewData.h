#ifndef ___MGVIEWDATA___
#define ___MGVIEWDATA___

#include "MGPiece.h"
class MGViewData :
	public MGPiece
{
protected:
	// �t���O
	bool flag;
	// �����ꂽ���ǂ���
	bool pushed;

public:

	MGViewData() :flag(false), pushed(false){}

	// �ϊ��R���X�g���N�^
	MGViewData(const MGPiece& piece)
	{
		group = piece.Group();
		num = piece.Num();
	}

	~MGViewData() {}

	// flag�擾
	bool Flag()
	{
		return flag;
	}

	// flag���]
	void reverseFlag()
	{
		flag = !flag;
	}

	// pushed�擾
	bool Pushed()
	{
		return pushed;
	}

	// pushed���Z�b�g����
	void setPushed()
	{
		pushed = true;
	}


};

#endif