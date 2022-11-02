#include "interpreter.h"
using namespace std;

int main(int argc, char** argv)
{
	try
	{
		bool debug = 0;
		
		
		if (argv[2]) debug = 1;
		else debug = 0;
		
		machine factorial(argv[1], debug);

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