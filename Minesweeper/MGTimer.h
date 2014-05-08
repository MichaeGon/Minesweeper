#ifndef ___MGTIMER___
#define ___MGTIMER___
#include <ctime>
#include "common.h"
using namespace std;

class MGTimer
{
private:
	// タイマー計測開始時間
	time_t start;
	// タイマーを止めるかどうか
	bool stopFlag;
	// タイマーを止めた時間(または現在の時間)
	time_t stop;

public:
	MGTimer() :start(0), stopFlag(false) {}

	// タイマー起動
	void fire()
	{
		start = time(NULL);
	}

	// タイマー停止
	void Stop()
	{
		if (!stopFlag) {
			stop = time(NULL);
			stopFlag = !stopFlag;
		}
	}

	// 経過時間を取得(秒) ただしタイマー起動前は0を返す
	time_t getElapsedTime()
	{
		if (!stopFlag) {
			stop = time(NULL);
		}
		return start>0 ? stop - start : start;
	}
};

#endif