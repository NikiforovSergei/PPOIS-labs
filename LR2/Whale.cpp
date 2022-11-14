#include "Whale.h"
#define new_world new_ocean[row][column][cell_position]
#define old_world old_ocean[new_row][new_column]

// make the main logic or whale do his life
void Whale::next(Ocean old_ocean, Ocean new_ocean)
{
    // Whale "next" methon logic is the same as shark "next" method logic
    srand(time(NULL));

    age += 1;
    int sum[STATES];

    int next_row = row;
    int next_column = column;
    bool complete_move = false;

    bool reproduction = false;
    sums(old_ocean, sum);

    if (age > DWHALE)
        new_world = new Empty(row, column, cell_position);
    else
    {
        if (sum[PLANKTON] > 0)
        {
            for (int k = 0; k < LIFE_IN_CELL; k++)
            {
                if (old_ocean[row][column][k]->who() == 1)
                    old_ocean[row][column][k] = new Empty(row, column, k);
            }

            hp += 20 * size;

            new_ocean[row][column][cell_position] = new Whale(row, column, cell_position, sex, size, hp, age);
        }
        else
        {
            if (sum[WHALE] == 2)
            {
                for (int k = 0; k < LIFE_IN_CELL; k++)
                {
                    if (old_ocean[row][column][k]->who() == 3 && old_ocean[row][column][k]->get_sex() != sex)
                        for (int kk = 0; kk < LIFE_IN_CELL; kk++)
                        {
                            if (old_ocean[row][column][kk]->who() == 0)
                            {
                                int sex = rand() % 2;
                                new_ocean[row][column][kk] = new Whale(row, column, kk, sex);

                                std::vector<int> update_params{ row, column, k };
                                changed_cells.push_back(update_params);
                                update_params[2] = kk;
                                changed_cells.push_back(update_params);

                                reproduction = true;

                                int other_age = old_ocean[row][column][k]->get_age() + 1;
                                old_ocean[row][column][k]->set_age(other_age);
                                int other_hp = old_ocean[row][column][k]->get_hp() - 20 * size;
                                old_ocean[row][column][k]->set_hp(other_hp);

                                if (old_ocean[row][column][k]->get_age() > DSHARK || old_ocean[row][column][k]->get_hp() <= 0)
                                    new_ocean[row][column][k] = new Empty(row, column, k);
                                else
                                    new_ocean[row][column][k] = new Whale(row, column, k, old_ocean[row][column][k]->get_sex(), 0, other_hp, other_age);

                                break;
                            }
                        }
                    if (reproduction)
                        break;
                }
            }
            if (!(reproduction))
            {
                complete_move = false;
                while (!(complete_move))
                {
                    int rand_move = rand() % 4;
                    next_row = row;
                    next_column = column;

                    switch (rand_move)
                    {
                    case 0:
                        if (row + move < OCEAN_LENGHT)
                        {
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

            hp -= 20 * size;
            if (hp <= 0)
                new_ocean[row][column][cell_position] = new Empty(row, column, cell_position);
            else if (complete_move)
            {
                new_ocean[row][column][cell_position] = new Empty(row, column, cell_position);
                new_ocean[next_row][next_column][cell_position] = new Whale(next_row, next_column, cell_position, sex, size, hp, age);
                std::vector<int> update_params{ next_row, next_column, cell_position };
                changed_cells.push_back(update_params);
            }
            else
                new_ocean[row][column][cell_position] = new Whale(row, column, cell_position, sex, size, hp, age);
        }
    }
}
