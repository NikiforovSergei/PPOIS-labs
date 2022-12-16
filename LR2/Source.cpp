#include "interpreter.h"
#include <typeinfo>

using namespace std;

int main(int argc, char** argv)
{
	try
	{
		bool debug = 0;

		if (strcmp(argv[2], "1") == 0)
			debug = 1;

		Interpreter factorial(argv[1], debug);

		factorial.interpret();

		cout << factorial.get_result() << endl;

	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}

	system("pause");

	return 0;
}