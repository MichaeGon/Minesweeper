#ifndef ___MGFIXEDTIMER___
#define ___MGFIXEDTIMER___
#include <ctime>
#include "MGTimer.h"

class MGFixedTimer :
	public MGTimer
{
protected:
	// �v���J�n����
	time_t start;
	// �^�C�}�[���~�߂邩�ǂ���
	bool stopFlag;
	// ���݂̎��ԁA�܂��͎~�߂�����
	time_t present;

public:
	MGFixedTimer() :start(0), stopFlag(false) {}
	~MGFixedTimer() {}

	// �^�C�}�[�N��
	void fire()
	{
		start = time(NULL);
	}

	// �^�C�}�[��~
	void stop()
	{
		if (!stopFlag) {
			present = time(NULL);
			stopFlag = !stopFlag;
		}
	}

	// �o�ߎ��Ԃ��擾�B�������^�C�}�[�N���O��0��Ԃ�
	time_t getElapsedTime()
	{
		if (!stopFlag) {
			present = time(NULL);
		}

		return start > 0 ? present - start : start;
	}

	// �V�K�Q�[���̂��߂̏�����
	void newGame()
	{
		stopFlag = false;
		start = 0;
	}
};


#endif