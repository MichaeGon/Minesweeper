#ifndef ___MGAPPLICATIONMAIN___
#define ___MGAPPLICATIONMAIN___
#include <omp.h>
#include "MGViewController.h"
#include "MGBoard.h"
#include "common.h"
using namespace std;

class MGApplicationMain
{
private:
	MGViewController view;
	MGBoard model;

public:
	MGApplicationMain(int argc, char** argv) :view(argc, argv), model() {};

	~MGApplicationMain();

	void appMain();
};

#endif