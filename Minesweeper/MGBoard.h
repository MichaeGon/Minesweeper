#ifndef ___MGBOARD___
#define ___MGBOARD___
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "common.h"
#include "MGPiece.h"
using namespace std;

class MGBoard
{
protected:
	// 盤面データ
	MGPiece*** board;
	// 爆弾の数
	int bomb;

public:

	MGBoard();
	~MGBoard();

	// 新規ゲーム用初期化
	virtual void newGame() = 0;

	// ゲーム開始時の爆弾配置
	// 引数にははじめて左クリックされたマス目の位置
	virtual void initBomb(int x0, int y0);

	// オープン処理
	virtual void open(int x, int y);

	// flagがたっている数を取得
	virtual int getFlagNum() const
	{
		int count = 0;
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				if (board[i][j]->Flag() && !board[i][j]->Pushed()) {
					count++;
				}
			}
		}

		return count;
	}

	// 配置された爆弾数取得
	int Bomb() const
	{
		return bomb;
	}

	// クリアかどうか。trueでクリア
	bool isClear();


	// 以下は演算子多重定義

	// boardを通常の配列のように指定できるようにする
	// 注意：ポインタに適用するときは (*p)[i][j]のようにカッコでくくる。
	MGPiece** operator[](int x)
	{
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