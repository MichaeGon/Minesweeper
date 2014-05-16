#ifndef ___MGBOARD___
#define ___MGBOARD___
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "common.h"
#include "MGPiece.h"
using namespace std;

class MGBoard
{
protected:
	// �Ֆʃf�[�^
	MGPiece*** board;
	// ���e�̐�
	int bomb;

public:

	MGBoard();
	~MGBoard();

	// �V�K�Q�[���p������
	virtual void newGame() = 0;

	// �Q�[���J�n���̔��e�z�u
	// �����ɂ͂͂��߂č��N���b�N���ꂽ�}�X�ڂ̈ʒu
	virtual void initBomb(int x0, int y0);

	// �I�[�v������
	virtual void open(int x, int y);

	// flag�������Ă��鐔���擾
	virtual int getFlagNum() const
	{
		int count = 0;
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				if (board[i][j]->Flag() && !board[i][j]->Pushed()) {
					count++;
				}
			}
		}

		return count;
	}

	// �z�u���ꂽ���e���擾
	int Bomb() const
	{
		return bomb;
	}

	// �N���A���ǂ����Btrue�ŃN���A
	bool isClear();


	// �ȉ��͉��Z�q���d��`

	// board��ʏ�̔z��̂悤�Ɏw��ł���悤�ɂ���
	// ���ӁF�|�C���^�ɓK�p����Ƃ��� (*p)[i][j]�̂悤�ɃJ�b�R�ł�����B
	MGPiece** operator[](int x)
	{
		if (x >= sqrNum || x < 0) {
			cout << "\a�G���[�F �s���Ȕz��̗v�f�̎w��ł��B\n �I�����܂��B�������͂��Ă�������:";
			int some;
			cin >> some;
			exit(1);
		}
		else {
			return board[x];
		}
	}
	
};

#endif