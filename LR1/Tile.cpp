#include "Tile.h"

Tile::Tile(int value, int x, int y)
{
    this->value = (char) value;
    correctX = x;
    correctY = y;
}

char Tile::GetValue() const
{
    return value;
}

bool Tile::CheckPlacement(int x, int y) const
{
    return (x == correctX && y == correctY);
}
