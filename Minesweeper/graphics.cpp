#include <cstdlib>
#include <GL/glut.h>
#include "common.h"
using namespace std;

char* title = "Minesweeper";
int sqrNum = 20;
int width = 600;
int height = 600;

namespace {

	// マス目の一辺大きさ
	const int sqrSize = 50;

	// 数字集
	char* numbers = "012345678";

	// 色の列挙体 配列colorsを指定するのに使用するのを想定(2とついているもののほうが暗い色)
	enum color { Gray, Blue, Green, Red, Blue2, Brown, Green2, Red2, Purple, Yellow };
	// 色配列
	double colors[][3] = {
		{ 0.95, 0.95, 0.95 },
		{ 0.25, 0.25, 1.0 },
		{ 0.0, 0.75, 0.0 },
		{ 0.9, 0.1, 0.1 },
		{ 0.4, 0.4, 1.0 },
		{ 0.6, 0.25, 0.1 },
		{ 0.28, 0.73, 0.42 },
		{ 0.6, 0.0, 0.0 },
		{ 0.3, 0.0, 0.3 },
		{ 1.0, 1.0, 0.0 }
	};
}


// マス目描画
void displayPiece(int x, int y, double color[])
{
	glColor3dv(color);
	glBegin(GL_QUADS);
	glVertex2d(sqrSize*(x + 1), sqrSize*(y + 1));
	glVertex2d(sqrSize*(x + 1.95), sqrSize*(y + 1));
	glVertex2d(sqrSize*(x + 1.95), sqrSize*(y + 1.95));
	glVertex2d(sqrSize*(x + 1), sqrSize*(y + 1.95));
	glEnd();
}

// 押されたマス目の描画
void displayPushedPiece(int x, int y, int num)
{
	// マス目の色をGrayにする
	displayPiece(x, y, colors[Gray]);

	// 数字描画
	glColor3dv(colors[num]);
	glRasterPos2d(sqrSize*(x + 1)+sqrSize*1.5 / 5.0, sqrSize*(y + 1)+sqrSize*4.0 / 5.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[num]);
}

// フラグマス描画
void displayFlagPiece(int x, int y)
{
	// マス目の色をYellowにする
	displayPiece(x, y, colors[Yellow]);

	// フラグ描画
	char flag = 'F';
	glColor3dv(colors[Red2]);
	glRasterPos2d(sqrSize*(x + 1) + sqrSize*1.5 / 5.0, sqrSize*(y + 1) + sqrSize*4.0 / 5.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, flag);
}

// ボードの基礎の描画
void displayBoard()
{
	// タイトル描画
	glColor3d(1, 1, 1);
	glRasterPos2d(sqrSize, sqrSize*4.0 / 5.0);
	for (char* str = title; *str; str++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
	}

	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			displayPiece(i, j, colors[Blue]);
		}
	}
}

void resize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(0, sqrSize*(sqrNum + 2), sqrSize*(sqrNum + 2), 0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		exit(0); // 改善の余地あり
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	int sqrX = x*(sqrNum + 2) / width - 1;
	int sqrY = y*(sqrNum + 2) / height - 1;

	// 盤面に収まっているか
	if (sqrX >= 0 && sqrY >= 0 && sqrX < sqrNum && sqrY < sqrNum) {

		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				left(sqrX,sqrY);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				right(sqrX,sqrY);
			}
			break;
		default:
			break;
		}
	}
}