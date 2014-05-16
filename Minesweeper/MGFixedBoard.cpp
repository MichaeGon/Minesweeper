#include "MGFixedBoard.h"


MGFixedBoard::MGFixedBoard() :MGBoard(), latest(1UL)
{
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			board[i][j] = new MGFixedPiece();
		}
	}
}


MGFixedBoard::~MGFixedBoard()
{
}

void MGFixedBoard::newGame()
{
	// ���݂̃{�[�h�f�[�^�j���A�����ɍĎ擾
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			delete board[i][j];
			board[i][j] = new MGFixedPiece();
		}
	}

	latest = 1;
}

void MGFixedBoard::initBomb(int x0, int y0)
{
	MGBoard::initBomb(x0, y0);

	// �O���[�v��
	grooping();
}

void MGFixedBoard::open(int x, int y)
{
	MGBoard::open(x, y);

	if (board[x][y]->Num() == 0) {
		// �������Ƃ���̎��͂ɔ��e���Ȃ����
		// �����O���[�v�̃}�X�ڂ����ׂăI�[�v���ɂ���
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				// �������t���O�������Ă���Ƃ���̓I�[�v���ɂ��Ȃ�
				if (board[i][j]->Flag() && !board[i][j]->Pushed()) continue;

				if (*dynamic_cast<MGFixedPiece*>(board[x][y]) & *dynamic_cast<MGFixedPiece*>(board[i][j])) {
					board[i][j]->setPushed();
				}
			}
		}
	}
}

void MGFixedBoard::sync(int i, int j, int x, int y)
{
	if (board[x][y]->Num() == 0) {
		*dynamic_cast<MGFixedPiece*>(board[i][j]) |= *dynamic_cast<MGFixedPiece*>(board[x][y]);
	}
}

void MGFixedBoard::syncall(int i, int j)
{
	if (board[i][j]->Num() != SENTINEL) {
		MGFixedPiece* piece = dynamic_cast<MGFixedPiece*>(board[i][j]);
		// ���e�̓O���[�v�Ȃ��Ƃ���
		// �ȉ��ł͔��e�ȊO�ɂ��čl����
		// �㉺���E�̂P�}�X�𒲂ׂ�

		// ���͂̔��e��0�̂Ƃ���ƃO���[�v����

		int x, y;
		for (x = -1; x <= 1; x++){
			for (y = -1; y <= 1; y++){
				if (x + i >= 0 && x + i < sqrNum&&y + j >= 0 && y + j < sqrNum){
					sync(i, j, x + i, y + j);
				}
			}
		}

		/*int x = i, y = j - 1;
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
		}*/

		// �����܂łŎ��͂Ƃ̃O���[�v�����͊���
		// �����ł܂��O���[�v������(0)�Ȃ�ΐV�K�O���[�v�����
		// ���������͂̔��e��0�̂Ƃ���Ɍ���
		if (piece->Group() == 0 && piece->Num() == 0) {
			try {
				newGroup(i, j);
			}
			catch (MGGroupError& err) {
				cout << err;
			}
		}
	}
}

void MGFixedBoard::grooping()
{
	// �c
	for (int i = 0; i <sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			syncall(i, j);
		}
	}
	// ��
	for (int j = 0; j < sqrNum; j++) {
		for (int i = 0; i < sqrNum; i++) {
			syncall(i, j);
		}
	}
	// �t����ēx�s��
	for (int i = sqrNum - 1; i >= 0; i--) {
		for (int j = sqrNum - 1; j >= 0; j--) {
			syncall(i, j);
		}
	}
	for (int j = sqrNum - 1; j >= 0; j--) {
		for (int i = sqrNum - 1; i >= 0; i--) {
			syncall(i, j);
		}
	}
}

void MGFixedBoard::newGroup(int x, int y)
{
	// �O���[�v�o�^��������r�b�g�V�t�g�����0�ɂȂ�̂ŃG���[���o��
	if (latest == 0) {
		throw MGGroupError();
	}

	// �V�K�O���[�v�ɓo�^
	*dynamic_cast<MGFixedPiece*>(board[x][y]) |= latest;

	// ���̃O���[�v���X�V
	latest <<= 1;
}