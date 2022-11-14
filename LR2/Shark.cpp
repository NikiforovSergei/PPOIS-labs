#include "Shark.h"
#define new_world new_ocean[row][column][cell_position]
#define old_world old_ocean[new_row][new_column]

// make the main logic or how shark do his life
void Shark::next(Ocean old_ocean, Ocean new_ocean)
{
    // for random move
    srand(time(NULL));

    age += 1;
    int sum[STATES];

    // default characters for transport in the new ocean
    int next_row = row;
    int next_column = column;
    bool complete_move = false;
    bool reproduction = false;

    // count a number of surrounding objects
    sums(old_ocean, sum);

    if (age > DSHARK)
        // shark die from max age
        new_world = new Empty(row, column, cell_position);
    else
    {
        if (sum[PLANKTON] > 0)
        {
            for (int k = 0; k < LIFE_IN_CELL; k++)
            {
                // shark find a plankton
                if (old_ocean[row][column][k]->who() == 1)
                    // shark eat the plankton
                    old_ocean[row][column][k] = new Empty(row, column, k);
            }

            // "heal" hp because eat a plankton
            hp += 20 * size;

            // transport shark in the new ocean
            new_ocean[row][column][cell_position] = new Shark(row, column, cell_position, sex, size, hp, age);
        }
        else
        {
            // reproduction situation
            if (sum[SHARK] == 2)
            {
                for (int k = 0; k < LIFE_IN_CELL; k++)
                {
                    // find shark with another sex (female == 0, male == 1)
                    if (old_ocean[row][column][k]->who() == 2 && old_ocean[row][column][k]->get_sex() != sex)
                        for (int kk = 0; kk < LIFE_IN_CELL; kk++)
                        {
                            // find Empty cell position
                            if (old_ocean[row][column][kk]->who() == 0)
                            {
                                // rand baby sex choose 
                                int sex = rand() % 2;
                                // create baby
                                new_ocean[row][column][kk] = new Shark(row, column, kk, sex);

                                // mark cell as changed
                                std::vector<int> update_params{ row, column, k };
                                changed_cells.push_back(update_params);
                                update_params[2] = kk;
                                changed_cells.push_back(update_params);

                                reproduction = true;

                                // update characteristics for shark-parthner
                                int other_age = old_ocean[row][column][k]->get_age()+1;
                                old_ocean[row][column][k]->set_age(other_age);
                                int other_hp = old_ocean[row][column][k]->get_hp() - 20;
                                old_ocean[row][column][k]->set_hp(other_hp);

                                // if we make reproduction we also make the "next" method for shark-parthner because it literally do its step (reproduct)
                                if (old_ocean[row][column][k]->get_age() > DSHARK || old_ocean[row][column][k]->get_hp() <= 0)
                                    // die
                                    new_ocean[row][column][k] = new Empty(row, column, k);
                                else
                                    // transpotr in the new ocean (life)
                                    new_ocean[row][column][k] = new Shark(row, column, k, old_ocean[row][column][k]->get_sex(), 0, other_hp, other_age);

                                break;
                            }
                        }
                    if (reproduction)
                        break;
                }
            }
            // move situation
            if (!(reproduction))
            {
                // we update move paramether because we just find an empty cell for move 
                complete_move = false;
                while (!(complete_move))
                {
                    // random move side choose
                    int rand_move = rand() % 5;
                    next_row = row;
                    next_column = column;

                    switch (rand_move)
                    {
                        // check if we don`t move behind ocean borders
                    case 0:
                        if (row + move < OCEAN_LENGHT)
                        {
                            // check if cell is empty for move
                            int empty_pos = empty_cell_for_move(old_ocean, new_ocean, row + move, column);
                            if (empty_pos != -1)
                            {
                                next_row += move;
                                complete_move = true;
                            }
                        }
                        break;
                    case 1:
                        if (column + move < OCEAN_WIDTH)
                        {
                            int empty_pos = empty_cell_for_move(old_ocean, new_ocean, row, column + move);
                            if (empty_pos != -1)
                            {
                                next_column += move;
                                complete_move = true;
                            }
                        }
                        break;
                    case 2:
                        if (row - move > 0)
                        {
                            int empty_pos = empty_cell_for_move(old_ocean, new_ocean, row - move, column);
                            if (empty_pos != -1)
                            {
                                next_row -= move;
                                complete_move = true;
                            }
                        }
                        break;
                    case 3:
                        if (column - move > 0)
                        {
                            int empty_pos = empty_cell_for_move(old_ocean, new_ocean, row, column - move);
                            if (empty_pos != -1)
                            {
                                next_column -= move;
                                complete_move = true;
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
            }

            // formula that depends of animal size (MEDIUM, BIG ...)
            hp -= 20 * size;
            if (hp <= 0)
                // die
                new_ocean[row][column][cell_position] = new Empty(row, column, cell_position);
            else if (complete_move)
            {
                // shark move
                new_ocean[row][column][cell_position] = new Empty(row, column, cell_position);
                new_ocean[next_row][next_column][cell_position] = new Shark(next_row, next_column, cell_position, sex, size, hp, age);
                std::vector<int> update_params{ next_row, next_column, cell_position };
                changed_cells.push_back(update_params);
            }
            else
                // just life
                new_ocean[row][column][cell_position] = new Shark(row, column, cell_position, sex, size, hp, age);
        }
    }
}
