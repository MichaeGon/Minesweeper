#include "MGBoard.h"

MGBoard::MGBoard()
{
	srand(static_cast<unsigned>(time(NULL)));

	board = new MGPiece**[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		board[i] = new MGPiece*[sqrNum];
	}

	// ���e�ܗL��15%
	bomb = sqrNum*sqrNum * 15 / 100;
}


MGBoard::~MGBoard()
{
	// �����ŔՖʃf�[�^���������鏈�����s���B
	// �h���N���X�̃f�X�g���N�^�ōs���K�v�͂Ȃ��B
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
}

void MGBoard::initBomb(int x0, int y0)
{
	// ���e��z�u����
	for (int count = 0; count < bomb; count++) {
		int x = rand() % sqrNum;
		int y = rand() % sqrNum;

		if (board[x][y]->Num() != SENTINEL && (x != x0 || y != y0)) {
			// ���e���ݒu����Ă���Ƃ���łȂ��Ȃ甚�e��ݒu
			board[x][y]->setBomb();
		}
		else {
			// �ݒu����Ă�����count����
			count--;
		}
	}

	// �ݒu����͂̔��e�����J�E���g����
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			// ���e�̂���Ƃ���͏��O
			if (board[i][j]->Num() == SENTINEL) continue;

			// ���ォ�瑖��
			for (int x = i - 1; x <= i + 1; x++) {
				for (int y = j - 1; y <= j + 1; y++) {
					// �ՖʊO�͏��O
					if (x < 0 || y < 0 || x >= sqrNum || y >= sqrNum) continue;

					// ���e�������num���C���N�������g
					if (board[x][y]->Num() == SENTINEL) {
						++(*board[i][j]);
					}
				}
			}
		}
	}
}

void MGBoard::open(int x, int y)
{
	// �w�肳�ꂽ�}�X�ڂ��I�[�v��
	board[x][y]->setPushed();

	if (board[x][y]->Num() == SENTINEL) {
		// ���e��������
		exit(0);
	}
	
}



bool MGBoard::isClear()
{
	int count = 0;
	// �󂢂Ă��Ȃ��}�X���J�E���g
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			if (!board[i][j]->Pushed()) {
				count++;
			}
		}
	}

	return count - bomb == 0;
}