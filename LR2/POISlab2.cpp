#include "interpreter.h"
using namespace std;

int main()
{
	try
	{
		string file = "check.txt";
		interpreter I(file, false);
		I.interpret();
		cout << I.get_result() << endl;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
}