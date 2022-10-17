#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
/// <summary>
/// \brief class that implements the machine tape
/// </summary>
class Tape 
{
private:
	/// <summary>
	/// \brief vector containing tape's symbols
	/// </summary>
	vector<char>simbols;
	
public:
	Tape();
	~Tape();
	Tape(vector<char>);
	void ChangeSimbol(int, char);
	void WriteSimbol(char, int);
	void Print();
	int TapeLength();
	char GetCurSymbol(int);
};
