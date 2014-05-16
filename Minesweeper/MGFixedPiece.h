#ifndef ___MGFIXEDPIECE___
#define ___MGFIXEDPIECE___
#include "MGPiece.h"

class MGFixedPiece :
	public MGPiece
{
protected:
	// グループ
	unsigned long group;

public:
	MGFixedPiece() :MGPiece(), group(0) {}
	// 変換コンストラクタ
	MGFixedPiece(unsigned long val)
	{
		group = val;
	}
	~MGFixedPiece() {}

	// group取得
	unsigned long Group() const
	{
		return group;
	}


	// 以下は演算子多重定義

	// |=はgroupに適用する
	MGFixedPiece& operator|=(const MGFixedPiece& right)
	{
		group |= right.group;

		return *this;
	}

	// &はgroupに適用する
	friend unsigned long operator&(const MGFixedPiece& left, const MGFixedPiece& right)
	{
		return left.group & right.group;
	}
};

#endif