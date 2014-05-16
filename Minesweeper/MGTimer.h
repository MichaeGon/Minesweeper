#ifndef ___MGTIMER___
#define ___MGTIMER___
#include <ctime>
#include "common.h"

class MGTimer
{
public:
	virtual ~MGTimer() {}

	// �^�C�}�[�N��
	virtual void fire() = 0;

	// �^�C�}�[��~
	virtual void stop() = 0;

	// �o�ߎ��Ԃ��擾(�b) �������^�C�}�[�N���O��0��Ԃ�
	virtual time_t getElapsedTime() = 0;

	// �V�K�΋Ǐ����p
	virtual void newGame() = 0;
};

#endif