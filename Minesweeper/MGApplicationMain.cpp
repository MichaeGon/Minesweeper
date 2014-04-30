#include "MGApplicationMain.h"
#include "dyumahead.h"
bool mvSwitch = true;

void hyouzi(){
	int i, j;
	for (i = 0; i < tate + 2; i++){
		for (j = 0; j < yoko + 2; j++){
			if (i == 0){
				if (j == 0){
					printf("┏");
				}
				else if (j == yoko + 1){
					printf("┓");
				}
				else{
					printf("━");
				}
			}
			else if (i == tate + 1){
				if (j == 0){
					printf("┗");
				}
				else if (j == yoko + 1){
					printf("┛");
				}
				else{
					printf("━");

				}
			}
			else{
				if (j == 0 || j == yoko + 1){
					printf("┃");
				}
				else if (BAN[2][i][j] == 1){
					printf("%d ", BAN[0][i][j]);
				}
				else{
					printf("  ");
				}
			}

		}
		puts("");
	}
}


void hantei(int a,int b){
	int i, j, n = 0;
	if (BAN[0][b][a] == bomb){
		endflag = 1;
	}
	else{
		for (i = 1; i <= tate; i++){
			for (j = 1; j <= yoko; j++){
				if (BAN[2][i][j] == 0){
					n++;
				}
			}
		}
		if (n == bombnumber){
			endflag = 2;
		}
	}
}

void haiti(){
	int i = 0, j;
	int x, y;
	int n;
	for (x = 1; x <= tate; x++){
		for (y = 1; y <= yoko; y++){
			BAN[0][x][y] = 0;
		}
	}
	while (i < bombnumber){
		x = rand() % tate + 1;
		y = rand() % yoko + 1;
		if (BAN[0][x][y] != 0 || BAN[2][x][y] != 0){
			i--;
		}
		else{
			BAN[0][x][y] = bomb;
		}
		i++;
	}
	for (x = 1; x <= tate; x++){
		for (y = 1; y <= yoko; y++){
			if (BAN[0][x][y] != bomb){
				n = 0;
				for (i = -1; i <= 1; i++){
					for (j = -1; j <= 1; j++){
						if (!(i == 0 && j == 0)){
							if (BAN[0][x + i][y + j] == bomb){
								n++;
							}
						}
					}
				}
				BAN[0][x][y] = n;
			}

		}
	}
}

void shokika(){
	int i, j, k;
	for (i = 0; i < 10; i++){
		for (j = 0; j < tate + 2; j++){
			for (k = 0; k < yoko + 2; k++){
				BAN[i][j][k] = 0;
			}
		}
	}
	endflag = 0;
	srand((unsigned)time(NULL));
}

void test(int a,int b){
	if (endflag == 3){
		shokika();
	}
	BAN[2][b][a] = 1;
	hyouzi();
	hantei(a,b);
	if (endflag == 0){
		haiti();
	}
	else if (endflag == 1){
		cout << "おしまい";
		exit(0);
	}

	           
}

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
				cout << sqrX << ',' << sqrY << '\n';
				test(sqrX  , sqrY);
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
	}
	}
}