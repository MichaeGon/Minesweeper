#ifndef ___MGAPPLICATIONMAIN___
#define ___MGAPPLICATIONMAIN___
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "MGBoard.h"
#include "MGPiece.h"
#include "MGTimer.h"
#include "common.h"
using namespace std;

class MGApplicationMain
{
private:
	MGTimer timer;
	MGBoard model;

public:
	MGApplicationMain(int argc, char** argv);

	// model.board[x][y]�ɃA�N�Z�X����
	MGPiece& Board(int x, int y)
	{
		return model[x][y];
	}

	// model�擾
	const MGBoard& Model() const
	{
		return model;
	}

	// timer�擾
	MGTimer& Timer()
	{
		return timer;
	}

	// ���N���b�N���̋��� �����͉����ꂽ�}�X�̏ꏊ
	void leftClick(int x, int y);

	// �E�N���b�N���̋���
	void rightClick(int x, int y);

	// �A�v�����C�����[�v
	void appMain();

};

#endif