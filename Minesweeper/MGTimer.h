#ifndef ___MGTIMER___
#define ___MGTIMER___
#include <ctime>
#include "common.h"

class MGTimer
{
public:
	virtual ~MGTimer() {}

	// タイマー起動
	virtual void fire() = 0;

	// タイマー停止
	virtual void stop() = 0;

	// 経過時間を取得(秒) ただしタイマー起動前は0を返す
	virtual time_t getElapsedTime() = 0;

	// 新規対局処理用
	virtual void newGame() = 0;
};

#endif