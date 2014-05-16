#include "MGFixedBoard.h"


MGFixedBoard::MGFixedBoard() :MGBoard(), latest(1UL)
{
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			board[i][j] = new MGFixedPiece();
		}
	}
}


MGFixedBoard::~MGFixedBoard()
{
}

void MGFixedBoard::newGame()
{
	// 現在のボードデータ破棄、同時に再取得
	for (int i = 0; i < sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			delete board[i][j];
			board[i][j] = new MGFixedPiece();
		}
	}

	latest = 1;
}

void MGFixedBoard::initBomb(int x0, int y0)
{
	MGBoard::initBomb(x0, y0);

	// グループ化
	grooping();
}

void MGFixedBoard::open(int x, int y)
{
	MGBoard::open(x, y);

	if (board[x][y]->Num() == 0) {
		// 押したところの周囲に爆弾がなければ
		// 同じグループのマス目をすべてオープンにする
		for (int i = 0; i < sqrNum; i++) {
			for (int j = 0; j < sqrNum; j++) {
				// ただしフラグがたっているところはオープンにしない
				if (board[i][j]->Flag() && !board[i][j]->Pushed()) continue;

				if (*dynamic_cast<MGFixedPiece*>(board[x][y]) & *dynamic_cast<MGFixedPiece*>(board[i][j])) {
					board[i][j]->setPushed();
				}
			}
		}
	}
}

void MGFixedBoard::sync(int i, int j, int x, int y)
{
	if (board[x][y]->Num() == 0) {
		*dynamic_cast<MGFixedPiece*>(board[i][j]) |= *dynamic_cast<MGFixedPiece*>(board[x][y]);
	}
}

void MGFixedBoard::syncall(int i, int j)
{
	if (board[i][j]->Num() != SENTINEL) {
		MGFixedPiece* piece = dynamic_cast<MGFixedPiece*>(board[i][j]);
		// 爆弾はグループなしとする
		// 以下では爆弾以外について考える
		// 上下左右の１マスを調べる

		// 周囲の爆弾数0のところとグループ同期

		int x, y;
		for (x = -1; x <= 1; x++){
			for (y = -1; y <= 1; y++){
				if (x + i >= 0 && x + i < sqrNum&&y + j >= 0 && y + j < sqrNum){
					sync(i, j, x + i, y + j);
				}
			}
		}

		/*int x = i, y = j - 1;
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
		}*/

		// ここまでで周囲とのグループ同期は完了
		// ここでまだグループ未所属(0)ならば新規グループを作る
		// ただし周囲の爆弾数0のところに限る
		if (piece->Group() == 0 && piece->Num() == 0) {
			try {
				newGroup(i, j);
			}
			catch (MGGroupError& err) {
				cout << err;
			}
		}
	}
}

void MGFixedBoard::grooping()
{
	// 縦
	for (int i = 0; i <sqrNum; i++) {
		for (int j = 0; j < sqrNum; j++) {
			syncall(i, j);
		}
	}
	// 横
	for (int j = 0; j < sqrNum; j++) {
		for (int i = 0; i < sqrNum; i++) {
			syncall(i, j);
		}
	}
	// 逆から再度行う
	for (int i = sqrNum - 1; i >= 0; i--) {
		for (int j = sqrNum - 1; j >= 0; j--) {
			syncall(i, j);
		}
	}
	for (int j = sqrNum - 1; j >= 0; j--) {
		for (int i = sqrNum - 1; i >= 0; i--) {
			syncall(i, j);
		}
	}
}

void MGFixedBoard::newGroup(int x, int y)
{
	// グループ登録上限よりもビットシフトすると0になるのでエラーを出す
	if (latest == 0) {
		throw MGGroupError();
	}

	// 新規グループに登録
	*dynamic_cast<MGFixedPiece*>(board[x][y]) |= latest;

	// 次のグループを更新
	latest <<= 1;
}