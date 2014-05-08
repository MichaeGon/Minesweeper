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
	// �^�C�}�[���~�߂邩�ǂ���
	bool stopFlag;
	// �^�C�}�[���~�߂�����(�܂��͌��݂̎���)
	time_t stop;

public:
	MGTimer() :start(0), stopFlag(false) {}

	// �^�C�}�[�N��
	void fire()
	{
		start = time(NULL);
	}

	// �^�C�}�[��~
	void Stop()
	{
		if (!stopFlag) {
			stop = time(NULL);
			stopFlag = !stopFlag;
		}
	}

	// �o�ߎ��Ԃ��擾(�b) �������^�C�}�[�N���O��0��Ԃ�
	time_t getElapsedTime()
	{
		if (!stopFlag) {
			stop = time(NULL);
		}
		return start>0 ? stop - start : start;
	}
};

#endif