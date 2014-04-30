#include "MGBoard.h"


MGBoard::MGBoard()
{
	srand(time(NULL));

	board = new MGPiece*[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		board[i] = new MGPiece[sqrNum];
	}

	latest = 1;

	// ���e�ܗL��15%
	bomb = sqrNum*sqrNum * 15 / 100;

	// ���e��z�u����
	for (int count = 0; count < bomb; count++) {
		int x = rand() % sqrNum;
		int y = rand() % sqrNum;

		if (board[x][y].Num() != SENTINEL) {
			// ���e���ݒu����Ă���Ƃ���łȂ��Ȃ甚�e��ݒu
			board[x][y].setBomb();
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
			if (board[i][j].Num() == SENTINEL) continue;

			// ���ォ�瑖��
			for (int x = i - 1; x <= i + 1; x++) {
				for (int y = j - 1; y <= j + 1; y++) {
					// �ՖʊO�͏��O
					if (x < 0 || y < 0 || x >= sqrNum || y >= sqrNum) continue;

					// ���e�������num���C���N�������g
					if (board[x][y].Num() == SENTINEL) {
						++board[i][j];
					}
				}
			}
		}
	}
}


MGBoard::~MGBoard()
{
	for (int i = 0; i < sqrNum; i++) {
		delete[] board[i];
	}
	delete[] board;
}


void MGBoard::grooping()
{
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			if (board[i][j].Num() != SENTINEL) {
				// ���e�̓O���[�v�Ȃ��Ƃ���
				// �ȉ��ł͔��e�ȊO�ɂ��čl����
				// �㉺���E�̂P�}�X�𒲂ׂ�

				// �O���[�v�����̃��[��:
				// ���͂̔��e��0�̂Ƃ���͎��͂̔��e��0�̃}�X�̃O���[�v�Ƃ�������
				// ���͂̔��e��1�ȏ�̂Ƃ���͎��͂̃}�X�̃O���[�v���ׂĂƓ���

				int x = i, y = j - 1; 
				if (y >= 0 && y < sqrNum) {
					// �P�}�X��̃}�X�ƃO���[�v�𓯊�
					sync(i, j, x, y);
				}
				y = j + 1;
				if (y >= 0 && y < sqrNum) {
					// �P�}�X���̃}�X�ƃO���[�v�𓯊�
					sync(i, j, x, y);
				}
				x = i - 1, y = j;
				if (x >= 0 && x < sqrNum) {
					// �P�}�X���̃}�X�ƃO���[�v�𓯊�
					sync(i, j, x, y);
				}
				x = i + 1;
				if (x >= 0 && x < sqrNum) {
					// �P�}�X�E�̃}�X�ƃO���[�v�𓯊�
					sync(i, j, x, y);
				}

				// �����܂łŎ��͂Ƃ̃O���[�v�����͊���
				// �����ł܂��O���[�v������(0)�Ȃ�ΐV�K�O���[�v�����
				if (board[i][j].Group() == 0) {
					try {
						newGroup(i, j);
					}
					catch (MGGroupError& err) {
						cout << err;
					}
				}
			}
		}
	}
}

void MGBoard::newGroup(int x, int y)
{
	// �O���[�v�o�^��������r�b�g�V�t�g�����0�ɂȂ�̂ŃG���[���o��
	if (latest == 0) {
		throw MGGroupError();
	}

	// �V�K�O���[�v�ɓo�^
	board[x][y] |= latest;

	// ���̃O���[�v���X�V
	latest <<= 1;
}