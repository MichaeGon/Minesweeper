#include "MGBoard.h"


MGBoard::MGBoard()
{
	srand(static_cast<unsigned>(time(NULL)));

	board = new MGPiece*[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		board[i] = new MGPiece[sqrNum];
	}

	latest = 1;

	// 爆弾含有率15%
	bomb = sqrNum*sqrNum * 15 / 100;
}


MGBoard::~MGBoard()
{
	for (int i = 0; i < sqrNum; i++) {
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

		if (board[x][y].Num() != SENTINEL && (x != x0 || y != y0)) {
			// 爆弾が設置されているところでないなら爆弾を設置
			board[x][y].setBomb();
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
			if (board[i][j].Num() == SENTINEL) continue;

			// 左上から走査
			for (int x = i - 1; x <= i + 1; x++) {
				for (int y = j - 1; y <= j + 1; y++) {
					// 盤面外は除外
					if (x < 0 || y < 0 || x >= sqrNum || y >= sqrNum) continue;

					// 爆弾があればnumをインクリメント
					if (board[x][y].Num() == SENTINEL) {
						++board[i][j];
					}
				}
			}
		}
	}

	// グループ化
	grooping();
}

void MGBoard::open(int x, int y)
{
	// 指定されたマス目をオープン
	board[x][y].setPushed();

	if (board[x][y].Num() == SENTINEL) {
		// 爆弾だったら
		exit(0);
	}
	else if (board[x][y].Num() == 0) {
		// 押したところの周囲に爆弾がなければ
		// 同じグループのマス目をすべてオープンにする
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				if (board[x][y] & board[i][j]) {
					board[i][j].setPushed();
				}
			}
		}
	}
}

void MGBoard::sync(int i, int j, int x, int y)
{
	if (board[x][y].Num() == 0) {
		board[i][j] |= board[x][y];
	}
}

void MGBoard::syncall(int i, int j)
{
	if (board[i][j].Num() != SENTINEL) {
		// 爆弾はグループなしとする
		// 以下では爆弾以外について考える
		// 上下左右の１マスを調べる

		// 周囲の爆弾数0のところとグループ同期

		int x = i, y = j - 1;
		if (y >= 0 && y < sqrNum) {
			// １マス上のマスとグループを同期
			sync(i, j, x, y);
		}
		y = j + 1;
		if (y >= 0 && y < sqrNum) {
			// １マス下のマスとグループを同期
			sync(i, j, x, y);
		}
		x = i - 1, y = j;
		if (x >= 0 && x < sqrNum) {
			// １マス左のマスとグループを同期
			sync(i, j, x, y);
		}
		x = i + 1;
		if (x >= 0 && x < sqrNum) {
			// １マス右のマスとグループを同期
			sync(i, j, x, y);
		}

		// ここまでで周囲とのグループ同期は完了
		// ここでまだグループ未所属(0)ならば新規グループを作る
		// ただし周囲の爆弾数0のところに限る
		if (board[i][j].Group() == 0 && board[i][j].Num() == 0) {
			try {
				newGroup(i, j);
			}
			catch (MGGroupError& err) {
				cout << err;
			}
		}
	}
}

void MGBoard::grooping()
{
	for (int i = 0; i <sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			syncall(i, j);
		}
	}
	// 逆から再度行う
	for (int i = sqrNum-1; i >= 0; i--) {
		for (int j = sqrNum-1; j >= 0; j--) {
			syncall(i, j);
		}
	}
}

void MGBoard::newGroup(int x, int y)
{
	// グループ登録上限よりもビットシフトすると0になるのでエラーを出す
	if (latest == 0) {
		throw MGGroupError();
	}

	// 新規グループに登録
	board[x][y] |= latest;

	// 次のグループを更新
	latest <<= 1;
}