#ifndef ___MGVIEWCONTROLLER___
#define ___MGVIEWCONTROLLER___
#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glut.h>
#include "common.h"
#include "MGPiece.h"
using namespace std;

class MGViewController
{
private:
	// ƒtƒ‰ƒO
	bool** flag;

public:
	MGViewController(int argc, char** argv);
	~MGViewController();

	void viewMain();
};

#endif