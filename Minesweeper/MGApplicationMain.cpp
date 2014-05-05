#include "MGApplicationMain.h"

namespace {
	MGApplicationMain* owner;
	bool first = true; // はじめて左クリックされるまでtrueでいる
}

// 描画の際呼び出される 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// ボード基盤描画
	displayBoard();

	if (!first) {
		// 押されたマス目とフラグ描画
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				if (owner->Board(i,j).Pushed()) {
					// 押されたマスを描画
					displayPushedPiece(i, j, owner->Board(i,j).Num());
				}
				else if (owner->Board(i, j).Flag()) {
					// フラグが立ててあるマスを描画
					displayFlagPiece(i, j);
				}
			}
		}
	}

	glutSwapBuffers();
}

void left(int x, int y)
{
	owner->leftClick(x,y);
}

void right(int x, int y)
{
	owner->rightClick(x,y);
}

MGApplicationMain::MGApplicationMain(int argc, char** argv) : model()
{
	owner = this;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
}

MGApplicationMain::~MGApplicationMain()
{
}

void MGApplicationMain::appMain()
{
	// まずはウィンドウを表示してプレイヤーの指示待ちとする
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glClearColor(0.18, 0.18, 0.18, 1.0);
	glutMainLoop();
}

void MGApplicationMain::leftClick(int x, int y)
{
	if (first) {
		// はじめて盤面を左クリックされたとき
		first = !first;

		// 爆弾を配置する
		model.initBomb(x, y);
	}
	
	// オープン
	model.open(x, y);

	// 再描画
	glutPostRedisplay();

	// クリア判定
	// もし爆弾数と残り空いているマスの数が一致すればクリア
	if (model.getEmptyNum() == 0) {
		// クリア判定を書く
		cout << "\aClear\n";
	}
}

void MGApplicationMain::rightClick(int x, int y)
{
	// フラグ反転
	model[x][y].setFlag();

	glutPostRedisplay();
}