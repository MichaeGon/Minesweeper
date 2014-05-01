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

namespace {
	// この名前空間内で使用できるポインタに各インスタンスを渡しておいてここでデータのやり取りをする
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