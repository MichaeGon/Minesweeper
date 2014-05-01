#ifndef ___MGVIEWCONTROLLER___
#define ___MGVIEWCONTROLLER___
#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glut.h>
#include "common.h"
#include "MGPiece.h"
#include "MGViewData.h"
using namespace std;

class MGViewController
{
private:
	// 描画の参考用データ
	MGViewData** data;

public:
	MGViewController(int argc, char** argv);
	~MGViewController();

	// dataから取得
	MGViewData& Data(int x, int y) const
	{
		return data[x][y];
	}

	// flag処理
	void setFlag(int x, int y)
	{
		data[x][y].reverseFlag();
	}

	// 押されたことを記録
	void setPush(int x, int y)
	{
		data[x][y].setPushed();
	}

	void viewMain();
};

#endif