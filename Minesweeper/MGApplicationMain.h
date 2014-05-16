#ifndef ___MGAPPLICATIONMAIN___
#define ___MGAPPLICATIONMAIN___
#include <cstdlib>
#include <GL/glut.h>
#include "MGBoard.h"
#include "MGFixedBoard.h"
#include "MGFixedPiece.h"
#include "MGPiece.h"
#include "MGTimer.h"
#include "common.h"

class MGApplicationMain
{
private:
	MGTimer timer;
	MGBoard* model;

public:
	MGApplicationMain(int argc, char** argv);
	~MGApplicationMain();

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
	MGTimer& Timer()
	{
		return timer;
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