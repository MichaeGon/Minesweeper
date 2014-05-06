// 並列処理されることを前提とした実装です

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

public:
	// オブジェクトが作成された時点から計測開始とする
	MGTimer() :start(time(NULL)) {}

	// 経過時間を取得(秒)
	time_t getElapsedTime() const
	{
		return time(NULL) - start;
	}
};

#endif