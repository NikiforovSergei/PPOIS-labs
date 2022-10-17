#include "HeaderHead.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// constructor
/// </summary>

Head::Head()
{

}

/// <summary>
/// \brief destructor
/// </summary>

Head::~Head()
{

}

/// <summary>
/// \brief constructor with parametrs
/// </summary>
/// <param name="curState"></param>
/// <param name="position"></param>

Head::Head(char curState, int position)
{
	this->curState = curState;
	this->position = position;
}

/// <summary>
/// \brief function for changing state of head
/// </summary>
/// <param name="state"></param>

void Head::ChangeState(char state)
{
	this->curState = state;
	return ;
}

/// <summary>
/// function function that determines the direction of the head 
/// </summary>
/// <param name="destination"></param>

void Head::Step(char destination)
{
	if (destination == 'L')
		position--;
	if (destination == 'R')
		position++;
}

/// <summary>
/// \brief function that returns the position of the symbol on which the head is currently located
/// </summary>
/// <returns></returns>

int Head::GetCurPosition()
{
	return this->position;
}

/// <summary>
/// \brief function that returns the symbol on which the head is currently located
/// </summary>
/// <returns></returns>

char Head::GetCurState()
{
	return this->curState;
}

