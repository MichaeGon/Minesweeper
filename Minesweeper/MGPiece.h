#ifndef ___MGPIECE___
#define ___MGPIECE___
#include <climits>
#include "common.h"
using namespace std;

class MGPiece
{
protected:
	unsigned long group; // グループ
	int num; // 周囲の爆弾数 SENTINELでそのマスは爆弾
	bool flag; // フラグ
	bool pushed; // 押されたかどうか

public:
	MGPiece() :group(0), num(0), flag(false), pushed(false) {}

	// 変換コンストラクタ
	MGPiece(unsigned long val)
	{
		group = val;
	}
	MGPiece(int val)
	{
		num = val;
	}

	~MGPiece(){}

	// group取得
	unsigned long Group() const
	{
		return group;
	}

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

	// |=はgroupに適用する
	MGPiece& operator|=(const MGPiece& right)
	{
		group |= right.group;

		return *this;
	}

	// &はgroupに適用する
	friend unsigned long operator&(const MGPiece& left, const MGPiece& right)
	{
		return left.group & right.group;
	}
};

#endif