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

	// model.board[x][y]�ɃA�N�Z�X����
	MGPiece& Board(int x, int y)
	{
		return model[x][y];
	}

	// ���N���b�N���̋��� �����͉����ꂽ�}�X�̏ꏊ
	void leftClick(int x, int y);

	// �E�N���b�N���̋���
	void rightClick(int x, int y);

	// �A�v�����C�����[�v
	void appMain();

};

#endif