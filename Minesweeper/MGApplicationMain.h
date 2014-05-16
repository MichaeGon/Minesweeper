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

	// model.board[x][y]�ɃA�N�Z�X����
	MGPiece* Board(int x, int y)
	{
		return (*model)[x][y];
	}

	// model�擾
	MGBoard* Model()
	{
		return model;
	}

	// timer�擾
	MGTimer& Timer()
	{
		return timer;
	}

	// �V�K�Q�[���J�n
	void newGame();

	// ���N���b�N���̋��� �����͉����ꂽ�}�X�̏ꏊ
	void leftClick(int x, int y);

	// �E�N���b�N���̋���
	void rightClick(int x, int y);

	// �A�v�����C�����[�v
	void appMain();

};

#endif