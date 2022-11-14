#include "Predator.h"

// check if animal can move in a certain cell 
int Predator::empty_cell_for_move(Ocean old_ocean, Ocean new_ocean, int m, int n)
{
	for (int k = 0; k < LIFE_IN_CELL; k++)
		// who == 0 means cell contains Empty object
		if (old_ocean[m][n][k]->who() == 0)
			return k;

	return -1;
}
