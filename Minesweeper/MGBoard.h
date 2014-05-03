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

	// �O���[�v���̂��߂̊֐�
	void sync(int i, int j, int x, int y);
	void syncall(int i, int j);

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

	// �Q�[���J�n���̔��e�z�u
	// �����ɂ͂͂��߂č��N���b�N���ꂽ�}�X�ڂ̈ʒu
	void initBomb(int x0, int y0);

	// �I�[�v������
	void open(int x, int y);

	// �O���[�v��
	void grooping();

	// �V�K�O���[�v�쐬
	// �󂯎���������̗v�f�̂Ƃ���ɐV�K�O���[�v�����
	void newGroup(int x, int y);



	// �ȉ��͉��Z�q���d��`

	// board��ʏ�̔z��̂悤�Ɏw��ł���悤�ɂ���
	MGPiece*& operator[](int x)
	{
		// �Z�[�t�e�B�K�[�h
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