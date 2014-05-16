#ifndef ___MGFIXEDPIECE___
#define ___MGFIXEDPIECE___
#include "MGPiece.h"

class MGFixedPiece :
	public MGPiece
{
protected:
	// �O���[�v
	unsigned long group;

public:
	MGFixedPiece() :MGPiece(), group(0) {}
	// �ϊ��R���X�g���N�^
	MGFixedPiece(unsigned long val)
	{
		group = val;
	}
	~MGFixedPiece() {}

	// group�擾
	unsigned long Group() const
	{
		return group;
	}


	// �ȉ��͉��Z�q���d��`

	// |=��group�ɓK�p����
	MGFixedPiece& operator|=(const MGFixedPiece& right)
	{
		group |= right.group;

		return *this;
	}

	// &��group�ɓK�p����
	friend unsigned long operator&(const MGFixedPiece& left, const MGFixedPiece& right)
	{
		return left.group & right.group;
	}
};

#endif