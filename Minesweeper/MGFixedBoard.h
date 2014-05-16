#ifndef ___MGFIXEDBOARD___
#define ___MGFIXEDBOARD___
#include <iostream>
#include <string>
#include "MGFixedPiece.h"
#include "MGBoard.h"
using namespace std;

class MGFixedBoard :
	public MGBoard
{
protected:
	// �ŐV�O���[�v
	unsigned long latest;

public:
	MGFixedBoard();
	~MGFixedBoard();

	// �O���[�v����Ɋւ���G���[
	class MGGroupError {
	private:
		string err;

	public:
		MGGroupError() :err("\a�G���[�F�O���[�v���̏�����I�[�o�[���܂���\n�Ֆʂ����������Ă��������x�V�K�ɃQ�[������蒼���Ă�������\n"){}

		friend ostream& operator<<(ostream& s, const MGGroupError& err)
		{
			return s << err.err;
		}
	};

	// �V�K�Q�[���p������
	void newGame();

	// �Q�[���J�n���̔��e�z�u
	// �����ɂ͂͂��߂č��N���b�N���ꂽ�}�X�ڂ̈ʒu
	void initBomb(int x0, int y0);

	// �I�[�v������
	void open(int x, int y);

protected:
	// �O���[�v���̂��߂̊֐�
	void sync(int i, int j, int x, int y);
	void syncall(int i, int j);

	// �O���[�v��
	void grooping();

	// �V�K�O���[�v�쐬
	// �󂯎���������̗v�f�̂Ƃ���ɐV�K�O���[�v�����
	void newGroup(int x, int y);
};

#endif