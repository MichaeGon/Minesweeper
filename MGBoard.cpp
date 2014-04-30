#include "MGBoard.h"

MGBoard::MGBoard()
{
	board = new MGPiece*[sqrNum];
	for (int i = 0; i < sqrNum; i++) {
		board[i] = new MGPiece[sqrNum];
		// ‰Šú‰»
	}
}


MGBoard::~MGBoard()
{
	for (int i = 0; i < sqrNum; i++) {
		delete[] board[i];
	}
	delete[] board;
}
