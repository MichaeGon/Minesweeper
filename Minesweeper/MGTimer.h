// ���񏈗�����邱�Ƃ�O��Ƃ��������ł�

#ifndef ___MGTIMER___
#define ___MGTIMER___
#include <ctime>
#include "common.h"
using namespace std;

class MGTimer
{
private:
	// �^�C�}�[�v���J�n����
	time_t start;

public:
	// �I�u�W�F�N�g���쐬���ꂽ���_����v���J�n�Ƃ���
	MGTimer() :start(time(NULL)) {}

	// �o�ߎ��Ԃ��擾(�b)
	time_t getElapsedTime() const
	{
		return time(NULL) - start;
	}
};

#endif