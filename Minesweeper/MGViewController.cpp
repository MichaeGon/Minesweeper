#include "MGViewController.h"

int sqrNum = 6;
int sqrX = SENTINEL;
int sqrY = SENTINEL;
int width = 500;
int height = 500;


// マス目の描画サイズ
const int sqrSize = 50;


namespace {
	// タイトル
	char* title = "Minesweeper";

	// 青
	double blue[]={0.25, 0.25, 1.0};


	// マス目の描画
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
				displayPiece(i, j, blue);
			}
		}
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		displayBoard();

		glutSwapBuffers();
	}

	void resize(int w, int h)
	{
		width = w;
		height = h;

		glViewport(0, 0, w, h);
		glLoadIdentity();
		glOrtho(0, sqrSize*(sqrNum + 2), sqrSize*(sqrNum + 2), 0, -1.0, 1.0);
	}


	void init()
	{
		glClearColor(0.18, 0.18, 0.18, 1.0);

	}
}

MGViewController::MGViewController(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width,height);
	glutCreateWindow(title);
}


MGViewController::~MGViewController()
{
}

void MGViewController::viewMain()
{
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
}