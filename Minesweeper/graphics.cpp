#include <cstdlib>
#include <ctime>
#include <GL/glut.h>
#include "common.h"
using namespace std;

char* title = "Minesweeper";
int sqrNum = 15;
int width = 600;
int height = 600;

namespace {

	// マス目の一辺大きさ
	const int sqrSize = 50;
	// 盤面外にマス目何マス分余白を作るか
	const int frame = 2;

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
	glVertex2d(sqrSize*(x + frame), sqrSize*(y + frame));
	glVertex2d(sqrSize*(x + frame + 0.95), sqrSize*(y + frame));
	glVertex2d(sqrSize*(x + frame + 0.95), sqrSize*(y + frame + 0.95));
	glVertex2d(sqrSize*(x + frame), sqrSize*(y + frame + 0.95));
	glEnd();
}

// 押されたマス目の描画
void displayPushedPiece(int x, int y, int num)
{
	// マス目の色をGrayにする
	displayPiece(x, y, colors[Gray]);

	// 数字描画
	glColor3dv(colors[num]);
	glRasterPos2d(sqrSize*(x + frame)+sqrSize*1.5 / 5.0, sqrSize*(y + frame)+sqrSize*4.0 / 5.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[num]);
}

// フラグマス描画
void displayFlagPiece(int x, int y)
{
	// 旗の描画
	glColor3dv(colors[Red]);
	glBegin(GL_TRIANGLES);
	glVertex2d(sqrSize*(x + frame) + sqrSize*1.5 / 5.0, sqrSize*(y + frame) + sqrSize*1.0 / 5.0);
	glVertex2d(sqrSize*(x + frame) + sqrSize*1.5 / 5.0, sqrSize*(y + frame) + sqrSize*2.6 / 5.0);
	glVertex2d(sqrSize*(x + frame) + sqrSize*4.0 / 5.0, sqrSize*(y + frame) + sqrSize*1.8 / 5.0);
	glEnd();
	
	// 棒の描画
	glColor3dv(colors[Gray]);
	glBegin(GL_QUADS);
	glVertex2d(sqrSize*(x + frame) + sqrSize*1.5 / 5.0, sqrSize*(y + frame) + sqrSize*1.0 / 5.0);
	glVertex2d(sqrSize*(x + frame) + sqrSize*1.5 / 5.0, sqrSize*(y + frame) + sqrSize*4.0 / 5.0);
	glVertex2d(sqrSize*(x + frame) + sqrSize*1.0 / 5.0, sqrSize*(y + frame) + sqrSize*4.0 / 5.0);
	glVertex2d(sqrSize*(x + frame) + sqrSize*1.0 / 5.0, sqrSize*(y + frame) + sqrSize*1.0 / 5.0);
	glEnd();
}

// ボードの基礎の描画
void displayBoard()
{
	// タイトル描画
	glColor3d(1, 1, 1);
	glRasterPos2d(sqrSize*frame, sqrSize+sqrSize*4.0 / 5.0);
	for (char* str = title; *str; str++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
	}

	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			displayPiece(i, j, colors[Blue]);
		}
	}
}

void displayTime(time_t elapsed)
{

}

void displayGrayBand()
{
	glColor3dv(colors[Gray]);
	glBegin(GL_QUADS);
	glVertex2d(0, height / 3);
	glVertex2d(0, height * 2 / 3);
	glVertex2d(width, height * 2 / 3);
	glVertex2d(width, height / 3);
	glEnd();
}

void displaySentenceOnBand(char* str)
{

}

void resize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(0, sqrSize*(sqrNum + frame*2), sqrSize*(sqrNum + frame*2), 0, -1.0, 1.0);
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
	int sqrX = x*(sqrNum + frame*2) / width - frame;
	int sqrY = y*(sqrNum + frame*2) / height - frame;

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