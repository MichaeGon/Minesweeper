#include "MGApplicationMain.h"

namespace {
	MGApplicationMain* owner;
}

// �`��̍یĂяo����� 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// �{�[�h��Օ`��
	displayBoard();
	displayBombNum(owner->Model()->Bomb(),owner->Model()->getFlagNum());
	displayTime(owner->Timer()->getElapsedTime());

	if (!owner->First()) {
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

	if (owner->Clear()) {
		displayGrayBand();
		displaySentenceOnBandRandom(" Congratulations!");
	}

	glutSwapBuffers();
}

void left(int x, int y)
{
	if (owner->Clear()) {
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
	if (!owner->First() && !owner->Clear()) {
		owner->rightClick(x, y);
	}
}

MGApplicationMain::MGApplicationMain(int argc, char** argv) :first(true), menu(true), clear(false)
{
	owner = this;

	model = NULL;
	timer = NULL;

	init<MGFixedBoard>();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
}

MGApplicationMain::~MGApplicationMain()
{
	delete model;
	delete timer;
}

void MGApplicationMain::appMain()
{
	// �܂��̓��j���[�`��
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
		timer->fire();
	}
	
	// �I�[�v��
	model->open(x, y);

	// �ĕ`��
	glutPostRedisplay();

	// �N���A����
	// �������e���Ǝc��󂢂Ă���}�X�̐�����v����΃N���A
	if (model->isClear() && !clear) {
		clear = !clear;
		timer->stop();
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
	timer->newGame();
	model->newGame();

	glutPostRedisplay();
}