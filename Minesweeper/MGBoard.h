#ifndef ___MGBOARD___
#define ___MGBOARD___
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include "common.h"
#include "MGPiece.h"
using namespace std;

class MGBoard
{
private:
	// �Ֆʃf�[�^
	MGPiece** board;
	// �ŐV�O���[�v(���ɍ��O���[�v)
	unsigned long latest;
	// ���e�̐�
	int bomb;

public:

	// �O���[�v����Ɋւ���G���[
	class MGGroupError {
	private:
		string err;

	public:
		MGGroupError() :err("\a�G���[�F�O���[�v���̏�����I�[�o�[���܂���\n�Ֆʂ����������Ă��������x�V�K�ɃQ�[������蒼���Ă�������\n"){}
		~MGGroupError(){}

		friend ostream& operator<<(ostream& s, const MGGroupError& err)
		{
			return s << err.err;
		}
	};

	MGBoard();
	~MGBoard();

	// �{�[�h�f�[�^�擾
	// �擾���Ŋm���ɊJ�����邱��
	MGPiece** Board()
	{
		MGPiece** tmp = new MGPiece*[sqrNum];
		for (int i = 0; i < sqrNum; i++) {
			tmp[i] = new MGPiece[sqrNum];
			for (int j = 0; j < sqrNum; j++) {
				tmp[i][j] = board[i][j];
			}
		}

		return tmp;
	}
	
private:
	// �O���[�v���̂��߂̊֐�
	void sync(int i, int j, int x, int y)
	{
		if ((board[i][j].Num() == 0 && board[x][y].Num() == SENTINEL) || board[i][j].Num() != 0) {
			board[i][j] |= board[x][y];
		}
	}

public:

	// �O���[�v��
	void grooping();

	// �V�K�O���[�v�쐬
	// �󂯎���������̗v�f�̂Ƃ���ɐV�K�O���[�v�����
	void newGroup(int x, int y);

	
};

#endif