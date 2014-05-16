#include "MGBoard.h"

MGBoard::MGBoard()
{
	srand(static_cast<unsigned>(time(NULL)));

	board = new MGPiece**[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		board[i] = new MGPiece*[sqrNum];
	}

	// 爆弾含有率15%
	bomb = sqrNum*sqrNum * 15 / 100;
}


MGBoard::~MGBoard()
{
	// ここで盤面データを消去する処理を行う。
	// 派生クラスのデストラクタで行う必要はない。
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
}

void MGBoard::initBomb(int x0, int y0)
{
	// 爆弾を配置する
	for (int count = 0; count < bomb; count++) {
		int x = rand() % sqrNum;
		int y = rand() % sqrNum;

		if (board[x][y]->Num() != SENTINEL && (x != x0 || y != y0)) {
			// 爆弾が設置されているところでないなら爆弾を設置
			board[x][y]->setBomb();
		}
		else {
			// 設置されていたらcount調整
			count--;
		}
	}

	// 設置後周囲の爆弾数をカウントする
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			// 爆弾のあるところは除外
			if (board[i][j]->Num() == SENTINEL) continue;

			// 左上から走査
			for (int x = i - 1; x <= i + 1; x++) {
				for (int y = j - 1; y <= j + 1; y++) {
					// 盤面外は除外
					if (x < 0 || y < 0 || x >= sqrNum || y >= sqrNum) continue;

					// 爆弾があればnumをインクリメント
					if (board[x][y]->Num() == SENTINEL) {
						++(*board[i][j]);
					}
				}
			}
		}
	}
}

void MGBoard::open(int x, int y)
{
	// 指定されたマス目をオープン
	board[x][y]->setPushed();

	if (board[x][y]->Num() == SENTINEL) {
		// 爆弾だったら
		exit(0);
	}
	
}



bool MGBoard::isClear()
{
	int count = 0;
	// 空いていないマスをカウント
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			if (!board[i][j]->Pushed()) {
				count++;
			}
		}
	}

	return count - bomb == 0;
}