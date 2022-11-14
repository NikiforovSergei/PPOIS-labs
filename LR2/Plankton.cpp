#include "Plankton.h"
#include <vector>

#define new_world new_ocean[row][column][cell_position]
#define old_world old_ocean[new_row][new_column] // it is current ocean model that we wants to change

// make the main logic or how plankton do his life
void Plankton::next(Ocean old_ocean, Ocean new_ocean)
{
    hp -= 20;
    int sum[STATES];

    bool reproduction = false;
    bool self_reproduction = false;

    // count a number of surrounding objects
    sums(old_ocean, sum);
    if (hp <= 0)
        //plankton die
        new_world = new Empty(row, column, cell_position);
    else
    {
        // crete model for next life step
        Model model;
        for (int m = -1; m < 2; m++)
        {
            for (int n = -1; n < 2; n++)
            {
                int new_row = row - m;
                int new_column = column - n;

                // we want to find a suitable cell (we we look at neighboring cells) 
                if (model.border(new_row, new_column))
                {
                    // count a number of cell surrounding planktons
                    old_ocean[new_row][new_column][0]->sums(old_ocean, sum);

                    // we determine if plankton peroduce itself in the next cell or in its cell
                    if (sum[PLANKTON] > 0)
                    {
                        if (new_row == row && new_column == column)
                            // if new coordinates coincided with current coordinates we "heal" current plankton
                            self_reproduction = true;
                        else
                        {
                            for (int k = 0; k < LIFE_IN_CELL; k++)
                                //check cell positions and find a plankton (who() == 1). If we find a plankton we "heal" it hp to 100
                               if (old_world[k]->who() == 1)
                               {
                                   new_ocean[new_row][new_column][k] = new Plankton(new_row, new_column, k);

                                   std::vector<int> repr_params{ new_row, new_column, k };
                                   reproducted_plankton.push_back(repr_params);

                                   reproduction = true;
                                   break;
                               }
                        }
                    }
                    else
                    {
                        for (int k = 0; k < LIFE_IN_CELL; k++)
                            // find an empt cell for reproduction
                            if (old_world[k]->who() == 0)
                            {
                                // make reproduction in the neighbour cell
                                new_ocean[new_row][new_column][k] = new Plankton(new_row, new_column, k);

                                std::vector<int> update_params{ new_row, new_column, k };
                                changed_cells.push_back(update_params);

                                reproduction = true;
                                break;
                            }
                    }
                }
                if (reproduction)
                    break;
            }
            if (reproduction)
                break;
        }

        if (self_reproduction)
            // we heal current plankton
            hp = 100;
        // transport current plankton in the new ocean
        new_world = new Plankton(row, column, cell_position, hp);
    }
}
