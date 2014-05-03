#include "MGBoard.h"


MGBoard::MGBoard()
{
	srand(static_cast<unsigned>(time(NULL)));

	board = new MGPiece*[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		board[i] = new MGPiece[sqrNum];
	}

	latest = 1;

	// ���e�ܗL��15%
	bomb = sqrNum*sqrNum * 15 / 100;
}


MGBoard::~MGBoard()
{
	for (int i = 0; i < sqrNum; i++) {
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

		if (board[x][y].Num() != SENTINEL && (x != x0 || y != y0)) {
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

	// �O���[�v��
	grooping();
}

void MGBoard::open(int x, int y)
{
	// �w�肳�ꂽ�}�X�ڂ��I�[�v��
	board[x][y].setPushed();

	if (board[x][y].Num() == SENTINEL) {
		// ���e��������
		exit(0);
	}
	else if (board[x][y].Num() == 0) {
		// �������Ƃ���̎��͂ɔ��e���Ȃ����
		// �����O���[�v�̃}�X�ڂ����ׂăI�[�v���ɂ���
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				if (board[x][y] & board[i][j]) {
					board[i][j].setPushed();
				}
			}
		}
	}
}

void MGBoard::sync(int i, int j, int x, int y)
{
	if (board[x][y].Num() == 0) {
		board[i][j] |= board[x][y];
	}
}

void MGBoard::syncall(int i, int j)
{
	if (board[i][j].Num() != SENTINEL) {
		// ���e�̓O���[�v�Ȃ��Ƃ���
		// �ȉ��ł͔��e�ȊO�ɂ��čl����
		// �㉺���E�̂P�}�X�𒲂ׂ�

		// ���͂̔��e��0�̂Ƃ���ƃO���[�v����

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
		// ���������͂̔��e��0�̂Ƃ���Ɍ���
		if (board[i][j].Group() == 0 && board[i][j].Num() == 0) {
			try {
				newGroup(i, j);
			}
			catch (MGGroupError& err) {
				cout << err;
			}
		}
	}
}

void MGBoard::grooping()
{
	for (int i = 0; i <sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			syncall(i, j);
		}
	}
	// �t����ēx�s��
	for (int i = sqrNum-1; i >= 0; i--) {
		for (int j = sqrNum-1; j >= 0; j--) {
			syncall(i, j);
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