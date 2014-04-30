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
	// 盤面データ
	MGPiece** board;
	// 最新グループ(次に作るグループ)
	unsigned long latest;
	// 爆弾の数
	int bomb;

public:

	// グループ操作に関するエラー
	class MGGroupError {
	private:
		string err;

	public:
		MGGroupError() :err("\aエラー：グループ数の上限をオーバーしました\n盤面を小さくしてからもう一度新規にゲームをやり直してください\n"){}
		~MGGroupError(){}

		friend ostream& operator<<(ostream& s, const MGGroupError& err)
		{
			return s << err.err;
		}
	};

	MGBoard();
	~MGBoard();

	// ボードデータ取得
	// 取得側で確実に開放すること
	MGPiece** Board()
	{
		MGPiece** tmp = new MGPiece*[sqrNum];
		for (int i = 0; i < sqrNum; i++) {
			tmp[i] = new MGPiece[sqrNum];
			for (int j = 0; j < sqrNum; j++) {
				tmp[i][j] = board[i][j];
			}
		}

		return tmp;
	}
	
private:
	// グループ化のための関数
	void sync(int i, int j, int x, int y)
	{
		if ((board[i][j].Num() == 0 && board[x][y].Num() == SENTINEL) || board[i][j].Num() != 0) {
			board[i][j] |= board[x][y];
		}
	}

public:

	// グループ化
	void grooping();

	// 新規グループ作成
	// 受け取った引数の要素のところに新規グループを作る
	void newGroup(int x, int y);

	
};

#endif