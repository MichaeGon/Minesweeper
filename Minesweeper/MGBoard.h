#ifndef ___MGBOARD___
#define ___MGBOARD___
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include "common.h"
#include "MGPiece.h"
using namespace std;

class MGBoard
{
private:
	// 盤面データ
	MGPiece** board;
	// 最新グループ(次に作るグループ)
	unsigned long latest;
	// 爆弾の数
	int bomb;

	// グループ化のための関数
	void sync(int i, int j, int x, int y);
	void syncall(int i, int j);

public:

	// グループ操作に関するエラー
	class MGGroupError {
	private:
		string err;

	public:
		MGGroupError() :err("\aエラー：グループ数の上限をオーバーしました\n盤面を小さくしてからもう一度新規にゲームをやり直してください\n"){}
		~MGGroupError(){}

		friend ostream& operator<<(ostream& s, const MGGroupError& err)
		{
			return s << err.err;
		}
	};

	MGBoard();
	~MGBoard();

	// ゲーム開始時の爆弾配置
	// 引数にははじめて左クリックされたマス目の位置
	void initBomb(int x0, int y0);

	// オープン処理
	void open(int x, int y);

	// グループ化
	void grooping();

	// 新規グループ作成
	// 受け取った引数の要素のところに新規グループを作る
	void newGroup(int x, int y);



	// 以下は演算子多重定義

	// boardを通常の配列のように指定できるようにする
	MGPiece*& operator[](int x)
	{
		// セーフティガード
		if (x >= sqrNum || x < 0) {
			cout << "\aエラー： 不正な配列の要素の指定です。\n 終了します。何か入力してください:";
			int some;
			cin >> some;
			exit(1);
		}
		else {
			return board[x];
		}
	}
	
};

#endif