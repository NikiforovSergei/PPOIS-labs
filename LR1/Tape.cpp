#include "HeaderTape.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
/// <summary>
/// \brief constructor without parameters
/// </summary>

Tape::Tape()
{

}

/// <summary>
/// \brief destructor
/// </summary>

Tape::~Tape()
{
	
}

/// <summary>
/// \brief constructor with parameters
/// </summary>
/// <param name="simbol"></param>

Tape::Tape(vector<char>simbol)
{
	simbols = simbol;
}

/// <summary>
/// \brirf the function that changes the meaning of a symbol on the tape
/// </summary>
/// <param name="position1"></param>
/// <param name="symbol2"></param>
void Tape::ChangeSimbol(int position1, char symbol2)
{
	int i = this->simbols.size();
	if (position1 < i && position1 >= 0)
		{
			this->simbols.at(position1) = symbol2;
		}
};


/// <summary>
/// \brief the function that write a new symbol on the tape
/// </summary>
/// <param name="symbol"></param>
/// <param name="position"></param>
void Tape::WriteSimbol(char symbol, int position)
{
	auto iter = this->simbols.cbegin();
	this->simbols.insert(iter + position, symbol);
};

/// <summary>
/// \brief function that returns the length of the tape
/// </summary>
/// <returns></returns>

int Tape::TapeLength()
{ 
	return this->simbols.size();
}

/// <summary>
/// \brief function for displaying tape on the screen
/// </summary>
void Tape::Print()
{

	int size = this->simbols.size();
	for (int i = 0; i < size; i++)
		cout << i << " " << this->simbols[i] << endl;
	
}

/// <summary>
/// \brief function that returns the symbol on which the head is currently located
/// </summary>
/// <param name="position"></param>
/// <returns></returns>

char Tape::GetCurSymbol(int position)
{
	char endTape = '.';
	int i = this->simbols.size();
	if (position < i && position >= 0)
		return this->simbols[position];
	else 
		return endTape;
}
