#include "MGApplicationMain.h"

bool mvSwitch = true;

void mouse(int button, int state, int x, int y)
{
	int tmpx = x*(sqrNum + 2) / width;
	int tmpy = y*(sqrNum + 2) / height;

	// 盤面に収まっているか
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
				// フラグ処理
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
		exit(0); // 改善の余地あり
	default:
		break;
	}
}

MGApplicationMain::~MGApplicationMain()
{
}

void MGApplicationMain::appMain()
{
	// 描画と内部処理を別スレッドで行う
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
				// ここに内部処理を書く

				// modelのボードデータをviewへ引き渡す
			}
		}
	}
}