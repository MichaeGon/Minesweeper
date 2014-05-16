#ifndef ___MGFIXEDBOARD___
#define ___MGFIXEDBOARD___
#include <iostream>
#include <string>
#include "MGFixedPiece.h"
#include "MGBoard.h"
using namespace std;

class MGFixedBoard :
	public MGBoard
{
protected:
	// 最新グループ
	unsigned long latest;

public:
	MGFixedBoard();
	~MGFixedBoard();

	// グループ操作に関するエラー
	class MGGroupError {
	private:
		string err;

	public:
		MGGroupError() :err("\aエラー：グループ数の上限をオーバーしました\n盤面を小さくしてからもう一度新規にゲームをやり直してください\n"){}

		friend ostream& operator<<(ostream& s, const MGGroupError& err)
		{
			return s << err.err;
		}
	};

	// 新規ゲーム用初期化
	void newGame();

	// ゲーム開始時の爆弾配置
	// 引数にははじめて左クリックされたマス目の位置
	void initBomb(int x0, int y0);

	// オープン処理
	void open(int x, int y);

protected:
	// グループ化のための関数
	void sync(int i, int j, int x, int y);
	void syncall(int i, int j);

	// グループ化
	void grooping();

	// 新規グループ作成
	// 受け取った引数の要素のところに新規グループを作る
	void newGroup(int x, int y);
};

#endif