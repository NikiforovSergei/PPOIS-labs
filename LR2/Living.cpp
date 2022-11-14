#include "Living.h"

// counts the number of every creatures in the cell
void Living::sums(Ocean ocean, int sm[])
{
	// initialized the sum of creatures of every type in the current cell as 0
	sm[EMPTY] = sm[PLANKTON] = sm[SHARK] = sm[WHALE] = 0;

	//get each item of 4 positions in the cell and call "who" method in depend what creature in this position
	for (int k = 0;  k < LIFE_IN_CELL; k++)
	{
		// k - position in cell; row,column - cell coordinates in the ocean
		sm[ocean[row][column][k]->who()]++;
	}
}


