#include "MGApplicationMain.h"

bool mvSwitch = true;



void mouse(int button, int state, int x, int y)
{
	int tmpx = x*(sqrNum + 2) / width;
	int tmpy = y*(sqrNum + 2) / height;

	// �ՖʂɎ��܂��Ă��邩
	if (tmpx > 0 && tmpy > 0 && tmpx <= sqrNum && tmpy <= sqrNum) {
		sqrX = tmpx;
		sqrY = tmpy;

		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				
				glutPostRedisplay();
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				// �t���O����
				glutPostRedisplay();
			}
			break;
		default:
			break;
		}
	}
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

namespace {
	// ���̖��O��ԓ��Ŏg�p�ł���|�C���^�Ɋe�C���X�^���X��n���Ă����Ă����Ńf�[�^�̂���������
	MGViewController* vptr;
	MGBoard* bptr;

}

MGApplicationMain::MGApplicationMain(int argc, char** argv) :view(argc, argv), model()
{
	vptr = &view;
	bptr = &model;
}

MGApplicationMain::~MGApplicationMain()
{
}

void MGApplicationMain::appMain()
{
	// �`��Ɠ���������ʃX���b�h�ōs��
#pragma omp parallel
#pragma omp sections
	{
#pragma omp section
		{
			view.viewMain();
		}
#pragma omp section
		{
			while (true) {
				// �����ɓ�������������

				// model�̃{�[�h�f�[�^��view�ֈ����n��
			}
		}
	}
}