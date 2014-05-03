#ifndef ___MGAPPLICATIONMAIN___
#define ___MGAPPLICATIONMAIN___
#include <cstdlib>
#include <GL/glut.h>
#include "MGBoard.h"
#include "MGPiece.h"
#include "common.h"
using namespace std;

class MGApplicationMain
{
private:
	MGBoard model;

public:
	MGApplicationMain(int argc, char** argv);

	~MGApplicationMain();

	// model.board[x][y]にアクセスする
	MGPiece& Board(int x, int y)
	{
		return model[x][y];
	}

	// 左クリック時の挙動 引数は押されたマスの場所
	void leftClick(int x, int y);

	// 右クリック時の挙動
	void rightClick(int x, int y);

	// アプリメインループ
	void appMain();

};

#endif