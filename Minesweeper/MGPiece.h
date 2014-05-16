#ifndef ___MGPIECE___
#define ___MGPIECE___
#include <climits>
#include "common.h"

class MGPiece
{
protected:
	int num; // ���͂̔��e�� SENTINEL�ł��̃}�X�͔��e
	bool flag; // �t���O
	bool pushed; // �����ꂽ���ǂ���

public:
	MGPiece() :num(0), flag(false), pushed(false) {}
	virtual ~MGPiece() {}

	// num�擾
	int Num() const
	{
		return num;
	}

	// flag�擾
	bool Flag() const
	{
		return flag;
	}

	// pushed�擾
	bool Pushed() const
	{
		return pushed;
	}


	// num��SENTINEL������
	void setBomb()
	{
		num = SENTINEL;
	}

	// pushed��true�ɂ���
	void setPushed()
	{
		pushed = true;
	}

	// flag���]
	void setFlag()
	{
		flag = !flag;
	}


	// �ȉ��͉��Z�q���d��`

	// ���ӁFMGPiece�̃|�C���^�^p�ɑ΂��čs���Ƃ���++(*p) (*p)++�̂悤�ɂ������ł�����B
	// ++���Z�q��num�ɂ��čs��
	// �O�u�^
	MGPiece& operator++()
	{
		if (num < INT_MAX) {
			num++;
		}

		return *this;
	}
	// ��u�^
	MGPiece operator++(int)
	{
		MGPiece tmp = *this;
		if (num < INT_MAX) {
			num++;
		}

		return tmp;
	}
};

#endif