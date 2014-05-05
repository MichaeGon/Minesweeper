#include <cstdlib>
#include <GL/glut.h>
#include "common.h"
using namespace std;

char* title = "Minesweeper";
int sqrNum = 20;
int width = 600;
int height = 600;

namespace {

	// �}�X�ڂ̈�ӑ傫��
	const int sqrSize = 50;

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
}


// �}�X�ڕ`��
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
void displayPushedPiece(int x, int y, int num)
{
	// �}�X�ڂ̐F��Gray�ɂ���
	displayPiece(x, y, colors[Gray]);

	// �����`��
	glColor3dv(colors[num]);
	glRasterPos2d(sqrSize*(x + 1)+sqrSize*1.5 / 5.0, sqrSize*(y + 1)+sqrSize*4.0 / 5.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[num]);
}

// �t���O�}�X�`��
void displayFlagPiece(int x, int y)
{
	// �}�X�ڂ̐F��Yellow�ɂ���
	displayPiece(x, y, colors[Yellow]);

	// �t���O�`��
	char flag = 'F';
	glColor3dv(colors[Red2]);
	glRasterPos2d(sqrSize*(x + 1) + sqrSize*1.5 / 5.0, sqrSize*(y + 1) + sqrSize*4.0 / 5.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, flag);
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
		exit(0); // ���P�̗]�n����
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	int sqrX = x*(sqrNum + 2) / width - 1;
	int sqrY = y*(sqrNum + 2) / height - 1;

	// �ՖʂɎ��܂��Ă��邩
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