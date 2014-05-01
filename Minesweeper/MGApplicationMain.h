#ifndef ___MGAPPLICATIONMAIN___
#define ___MGAPPLICATIONMAIN___
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "MGViewController.h"
#include "MGBoard.h"
#include "MGPiece.h"
#include "common.h"
using namespace std;

class MGApplicationMain
{
private:
	MGViewController view;
	MGBoard model;

public:
	MGApplicationMain(int argc, char** argv);

	~MGApplicationMain();

	void appMain();
};

#endif