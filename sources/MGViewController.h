#ifndef ___MGVIEWCONTROLLER___
#define ___MGVIEWCONTROLLER___
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "common.h"
#include "MGPiece.h"
using namespace std;

class MGViewController
{
private:
	MGPiece board;

public:
	MGViewController(int argc, char** argv);
	~MGViewController();

	void viewMain();
};

#endif