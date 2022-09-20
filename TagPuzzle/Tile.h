///
/// Simulates a tag tile
/// 

#pragma once

class Tile
{
public:
	Tile(int value, int x, int y);
	char GetValue() const;
	bool CheckPlacement(int x, int y) const;
private:
	char value;
	int correctX;
	int correctY;
};

