#include "MGViewController.h"

int sqrNum = 9;
int sqrX = SENTINEL;
int sqrY = SENTINEL;
int width = 600;
int height = 600;


// �}�X�ڂ̕`��T�C�Y
const int sqrSize = 50;


namespace {
	// ���g�ւ̃|�C���^�����̖��O��ԂŎg����悤�ɂ��āA���̖��O��Ԓ��̊֐����[���I�Ƀ����o�֐��̂悤�Ɉ����i�Ƃ��������������j
	MGViewController* owner;

	// �^�C�g��
	char* title = "Minesweeper";
	// �����W
	char* numbers = "012345678";

	// �F�̗񋓑� �z��colors���w�肷��̂Ɏg�p����̂�z��(2�Ƃ��Ă�����̂̂ق����Â��F)
	enum color { Gray, Blue, Green, Red, Blue2, Brown, Green2, Red2, Purple, Yellow };
	// �F�z��
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

	// �����ꂽ�}�X�ڂ̕`��
	void displayPushedPiece(int x, int y)
	{
		// ���e���擾
		int num = owner->Data(x, y).Num();

		// �����`��
		if (num > 0) {
			glColor3dv(colors[num]);
			glRasterPos2d(sqrSize*4.0 / 5.0, sqrSize*4.0 / 5.0);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, numbers[num]);
		}

		// �}�X�ڂ̐F��Gray�ɂ���
		displayPiece(x, y, colors[Gray]);
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
				displayPiece(i, j, colors[Blue]);
			}
		}
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// �{�[�h�̊�b��`��
		displayBoard();

		// �f�[�^�ɉ����Ēǉ��`��


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
	data = new MGViewData*[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		data[i] = new MGViewData[sqrNum];
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
		delete[] data[i];
	}
	delete[] data;
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