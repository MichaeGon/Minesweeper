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
	MGTimer* timer; // �^�C�}�[
	MGBoard* model; // �����f�[�^
	bool first; // �͂��߂č��N���b�N�����܂�true�ł���
	bool menu; // ���j���[��\�����邩�ǂ���
	bool clear; // �N���A�����true�ɂȂ�

public:
	MGApplicationMain(int argc, char** argv);
	~MGApplicationMain();

	// ���e�Œ�(fixed)/�ړ�(moving)�^�ŊJ�n
	// Type�ɂ�MGFixedBoard��MGMovingBoard������
	// ����ȊO�̌^���w�肵���ꍇ�͍l�����Ȃ�
	template <class Type> void init()
	{
		Type* ptr = dynamic_cast<Type*>(model);

		// ptr�����̎��_��NULL�̂Ƃ�
		if (!ptr) {
			// model,timer���I�u�W�F�N�g���w���Ă���Ƃ���
			if (model) {
				// �j������
				delete model;
				delete timer;
			}

			// Type�^���擾
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
	MGTimer* Timer()
	{
		return timer;
	}

	// first�擾
	bool First() const
	{
		return first;
	}

	// clear�擾
	bool Clear() const
	{
		return clear;
	}

	// menu�擾
	bool Menu() const
	{
		return menu;
	}

	// menu���]
	void setMenu()
	{
		menu = !menu;
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