#include "Empty.h"
#define new_world new_ocean[row][column][cell_position]

void Empty::next(Ocean old_ocean, Ocean new_ocean)
{
    //fill the next ocean model cell with emptiness
    new_world = new Empty(row, column, cell_position);
}
