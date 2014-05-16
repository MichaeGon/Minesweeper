#ifndef ___MGFIXEDTIMER___
#define ___MGFIXEDTIMER___
#include <ctime>
#include "MGTimer.h"

class MGFixedTimer :
	public MGTimer
{
protected:
	// 計測開始時間
	time_t start;
	// タイマーを止めるかどうか
	bool stopFlag;
	// 現在の時間、または止めた時間
	time_t present;

public:
	MGFixedTimer() :start(0), stopFlag(false) {}
	~MGFixedTimer() {}

	// タイマー起動
	void fire()
	{
		start = time(NULL);
	}

	// タイマー停止
	void stop()
	{
		if (!stopFlag) {
			present = time(NULL);
			stopFlag = !stopFlag;
		}
	}

	// 経過時間を取得。ただしタイマー起動前は0を返す
	time_t getElapsedTime()
	{
		if (!stopFlag) {
			present = time(NULL);
		}

		return start > 0 ? present - start : start;
	}

	// 新規ゲームのための初期化
	void newGame()
	{
		stopFlag = false;
		start = 0;
	}
};


#endif