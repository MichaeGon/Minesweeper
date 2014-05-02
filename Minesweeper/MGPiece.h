#ifndef ___MGPIECE___
#define ___MGPIECE___
#include <climits>
#include "common.h"
using namespace std;

class MGPiece
{
protected:
	unsigned long group; // �O���[�v
	int num; // ���͂̔��e�� SENTINEL�ł��̃}�X�͔��e
	bool flag; // �t���O
	bool pushed; // �����ꂽ���ǂ���

public:
	MGPiece() :group(0), num(0), flag(false), pushed(false) {}

	// �ϊ��R���X�g���N�^
	MGPiece(unsigned long val)
	{
		group = val;
	}
	MGPiece(int val)
	{
		num = val;
	}

	~MGPiece(){}

	// group�擾
	unsigned long Group() const
	{
		return group;
	}

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

	// |=��group�ɓK�p����
	MGPiece& operator|=(const MGPiece& right)
	{
		group |= right.group;

		return *this;
	}

	// &��group�ɓK�p����
	friend unsigned long operator&(const MGPiece& left, const MGPiece& right)
	{
		return left.group & right.group;
	}
};

#endif