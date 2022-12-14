#include "interpreter.h"
using namespace std;

int main(int argc, char** argv)
{
	try
	{
		bool debug = 0;
		if (argv[2]) debug = 1;
		else debug = 0;
		machine input_code("2.txt", debug);
		input_code.interpret();
		cout << input_code.get_result() << endl;
	}
	catch (exception& error)
	{
		cout << error.what() << endl;
	}

	return 0;
}