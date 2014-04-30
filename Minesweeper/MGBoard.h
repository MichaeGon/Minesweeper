#ifndef ___MGBOARD___
#define ___MGBOARD___
#include <iostream>
#include "common.h"
#include "MGPiece.h"
using namespace std;

class MGBoard
{
private:
	// î’ñ ÉfÅ[É^
	MGPiece** board;

public:
	MGBoard();
	~MGBoard();
};

#endif