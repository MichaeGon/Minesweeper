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
	// �`��̎Q�l�p�f�[�^
	MGViewData** data;

public:
	MGViewController(int argc, char** argv);
	~MGViewController();

	// data����擾
	MGViewData& Data(int x, int y) const
	{
		return data[x][y];
	}

	// flag����
	void setFlag(int x, int y)
	{
		data[x][y].reverseFlag();
	}

	// �����ꂽ���Ƃ��L�^
	void setPush(int x, int y)
	{
		data[x][y].setPushed();
	}

	void viewMain();
};

#endif