#include "MGApplicationMain.h"

namespace {
	MGApplicationMain* owner;
}

// 描画の際呼び出される 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// ボード基盤描画
	displayBoard();
	displayBombNum(owner->Model()->Bomb(),owner->Model()->getFlagNum());
	displayTime(owner->Timer()->getElapsedTime());

	if (!owner->First()) {
		// 押されたマス目とフラグ描画
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				if (owner->Board(i,j)->Pushed()) {
					// 押されたマスを描画
					displayPushedPiece(i, j, owner->Board(i,j)->Num());
				}
				else if (owner->Board(i, j)->Flag()) {
					// フラグが立ててあるマスを描画
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
		// クリアしてる状態でNewGameボタンが押されたとき
		owner->newGame();
	}
	else if (!owner->Board(x, y)->Flag()) {
		// フラグがたっているところは反応しないようにする
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
	// まずはメニュー描画
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
		// はじめて盤面を左クリックされたとき
		first = !first;

		// 爆弾を配置する
		model->initBomb(x, y);

		// タイマー開始
		timer->fire();
	}
	
	// オープン
	model->open(x, y);

	// 再描画
	glutPostRedisplay();

	// クリア判定
	// もし爆弾数と残り空いているマスの数が一致すればクリア
	if (model->isClear() && !clear) {
		clear = !clear;
		timer->stop();
	}
}

void MGApplicationMain::rightClick(int x, int y)
{
	// フラグ反転
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