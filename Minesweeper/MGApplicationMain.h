#ifndef ___MGAPPLICATIONMAIN___
#define ___MGAPPLICATIONMAIN___
#include "MGBoard.h"
#include "MGFixedBoard.h"
#include "MGMovingBoard.h"
#include "MGPiece.h"
#include "MGFixedPiece.h"
#include "MGMovingPiece.h"
#include "MGTimer.h"
#include "MGFixedTimer.h"
#include "MGMovingTimer.h"
#include "common.h"
#include <GL/glut.h>

class MGApplicationMain
{
private:
	MGTimer* timer; // タイマー
	MGBoard* model; // 内部データ
	bool first; // はじめて左クリックされるまでtrueでいる
	bool menu; // メニューを表示するかどうか
	bool clear; // クリアすればtrueになる

public:
	MGApplicationMain(int argc, char** argv);
	~MGApplicationMain();

	// 爆弾固定(fixed)/移動(moving)型で開始
	// TypeにはMGFixedBoardかMGMovingBoardが入る
	// それ以外の型を指定した場合は考慮しない
	template <class Type> void init()
	{
		Type* ptr = dynamic_cast<Type*>(model);

		// ptrがこの時点でNULLのとき
		if (!ptr) {
			// model,timerがオブジェクトを指しているときは
			if (model) {
				// 破棄する
				delete model;
				delete timer;
			}

			// Type型を取得
			model = new Type();
			
			MGFixedBoard* judge = dynamic_cast<MGFixedBoard*>(model);
			if (judge) {
				timer = new MGFixedTimer();
			}
			else {
				timer = new MGMovingTimer();
			}
		}
	}

	// model.board[x][y]にアクセスする
	MGPiece* Board(int x, int y)
	{
		return (*model)[x][y];
	}

	// model取得
	MGBoard* Model()
	{
		return model;
	}

	// timer取得
	MGTimer* Timer()
	{
		return timer;
	}

	// first取得
	bool First() const
	{
		return first;
	}

	// clear取得
	bool Clear() const
	{
		return clear;
	}

	// menu取得
	bool Menu() const
	{
		return menu;
	}

	// menu反転
	void setMenu()
	{
		menu = !menu;
	}

	// 新規ゲーム開始
	void newGame();

	// 左クリック時の挙動 引数は押されたマスの場所
	void leftClick(int x, int y);

	// 右クリック時の挙動
	void rightClick(int x, int y);

	// アプリメインループ
	void appMain();

};

#endif