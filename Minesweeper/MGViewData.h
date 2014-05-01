#ifndef ___MGVIEWDATA___
#define ___MGVIEWDATA___

#include "MGPiece.h"
class MGViewData :
	public MGPiece
{
protected:
	// フラグ
	bool flag;
	// 押されたかどうか
	bool pushed;

public:

	MGViewData() :flag(false), pushed(false){}

	// 変換コンストラクタ
	MGViewData(const MGPiece& piece)
	{
		group = piece.Group();
		num = piece.Num();
	}

	~MGViewData() {}

	// flag取得
	bool Flag()
	{
		return flag;
	}

	// flag反転
	void reverseFlag()
	{
		flag = !flag;
	}

	// pushed取得
	bool Pushed()
	{
		return pushed;
	}

	// pushedをセットする
	void setPushed()
	{
		pushed = true;
	}


};

#endif