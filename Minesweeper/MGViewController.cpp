#include "MGViewController.h"

int sqrNum = 6;
int sqrX = SENTINEL;
int sqrY = SENTINEL;
int width = 500;
int height = 500;


// �}�X�ڂ̕`��T�C�Y
const int sqrSize = 50;


namespace {
	// MGViewController�N���X�̃C���X�^���X�̓A�v����ɂP�����Ȃ����̂Ƃ���
	MGViewController* owner;

	// �^�C�g��
	char* title = "Minesweeper";

	// ��
	double blue[]={0.25, 0.25, 1.0};


	// �}�X�ڂ̕`��
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

	// �{�[�h�̊�b�̕`��
	void displayBoard()
	{
		// �^�C�g���`��
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
	flag = new bool*[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		flag[i] = new bool[sqrNum];
		for (int j = 0; j < sqrNum; j++) {
			flag[i][j] = false;
		}
	}

	owner = this;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width,height);
	glutCreateWindow(title);
}


MGViewController::~MGViewController()
{
	for (int i = 0; i < sqrNum; i++) {
		delete[] flag[i];
	}
	delete[] flag;
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