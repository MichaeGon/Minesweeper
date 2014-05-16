#ifndef ___MGPIECE___
#define ___MGPIECE___
#include <climits>
#include "common.h"

class MGPiece
{
protected:
	int num; // 周囲の爆弾数 SENTINELでそのマスは爆弾
	bool flag; // フラグ
	bool pushed; // 押されたかどうか

public:
	MGPiece() :num(0), flag(false), pushed(false) {}
	virtual ~MGPiece() {}

	// num取得
	int Num() const
	{
		return num;
	}

	// flag取得
	bool Flag() const
	{
		return flag;
	}

	// pushed取得
	bool Pushed() const
	{
		return pushed;
	}


	// numにSENTINELを入れる
	void setBomb()
	{
		num = SENTINEL;
	}

	// pushedをtrueにする
	void setPushed()
	{
		pushed = true;
	}

	// flag反転
	void setFlag()
	{
		flag = !flag;
	}


	// 以下は演算子多重定義

	// 注意：MGPieceのポインタ型pに対して行うときは++(*p) (*p)++のようにかっこでくくる。
	// ++演算子はnumについて行う
	// 前置型
	MGPiece& operator++()
	{
		if (num < INT_MAX) {
			num++;
		}

		return *this;
	}
	// 後置型
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