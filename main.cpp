#include <ctime>
#include <cstdlib>
#include "MGApplicationMain.h"

int main(int argc, char** argv)
{
	srand(time(NULL));
	MGApplicationMain application(argc, argv);
	application.appMain();

	return 0;
}