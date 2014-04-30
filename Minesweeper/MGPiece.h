#ifndef ___MGPIECE___
#define ___MGPIECE___
#include "common.h"

class MGPiece
{
private:
	unsigned long group; // グループ
	int num; // 周囲の爆弾数 SENTINELでそのマスは爆弾
	bool flag; // フラグ

public:
	MGPiece() :group(0), num(0), flag(false) {}
	~MGPiece();
};

#endif