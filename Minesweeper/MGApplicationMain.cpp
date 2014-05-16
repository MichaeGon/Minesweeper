#include "MGApplicationMain.h"

namespace {
	MGApplicationMain* owner;
	bool first = true; // �͂��߂č��N���b�N�����܂�true�ł���
	bool clear = false; // �N���A�����true�ɂȂ�
}

// �`��̍یĂяo����� 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// �{�[�h��Օ`��
	displayBoard();
	displayBombNum(owner->Model()->Bomb(),owner->Model()->getFlagNum());
	displayTime(owner->Timer().getElapsedTime());

	if (!first) {
		// �����ꂽ�}�X�ڂƃt���O�`��
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				if (owner->Board(i,j)->Pushed()) {
					// �����ꂽ�}�X��`��
					displayPushedPiece(i, j, owner->Board(i,j)->Num());
				}
				else if (owner->Board(i, j)->Flag()) {
					// �t���O�����ĂĂ���}�X��`��
					displayFlagPiece(i, j);
				}
			}
		}
	}

	if (clear) {
		displayGrayBand();
		displaySentenceOnBandRandom(" Congratulations!");
	}

	glutSwapBuffers();
}

void left(int x, int y)
{
	if (clear) {
		// �N���A���Ă��Ԃ�NewGame�{�^���������ꂽ�Ƃ�
		owner->newGame();
	}
	else if (!owner->Board(x, y)->Flag()) {
		// �t���O�������Ă���Ƃ���͔������Ȃ��悤�ɂ���
		owner->leftClick(x, y);
	}
}

void right(int x, int y)
{
	if (!first && !clear) {
		owner->rightClick(x, y);
	}
}

MGApplicationMain::MGApplicationMain(int argc, char** argv) :timer()
{
	owner = this;

	model = new MGFixedBoard();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
}

MGApplicationMain::~MGApplicationMain()
{
	delete model;
}

void MGApplicationMain::appMain()
{
	// �܂��̓E�B���h�E��\�����ăv���C���[�̎w���҂��Ƃ���
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glClearColor(0.18, 0.18, 0.18, 1.0);
	glutMainLoop();
}

void MGApplicationMain::leftClick(int x, int y)
{
	if (first) {
		// �͂��߂ĔՖʂ����N���b�N���ꂽ�Ƃ�
		first = !first;

		// ���e��z�u����
		model->initBomb(x, y);

		// �^�C�}�[�J�n
		timer.fire();
	}
	
	// �I�[�v��
	model->open(x, y);

	// �ĕ`��
	glutPostRedisplay();

	// �N���A����
	// �������e���Ǝc��󂢂Ă���}�X�̐�����v����΃N���A
	if (model->isClear() && !clear) {
		clear = !clear;
		timer.Stop();
	}
}

void MGApplicationMain::rightClick(int x, int y)
{
	// �t���O���]
	(*model)[x][y]->setFlag();

	glutPostRedisplay();
}

void MGApplicationMain::newGame()
{
	clear = false;
	first = true;
	timer.newGame();
	model->newGame();

	glutPostRedisplay();
}