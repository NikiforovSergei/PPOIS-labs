#pragma once

/// <summary>
/// Simulates a tag tile.
/// </summary>
class Tile
{
public:
	/// <summary>
	/// Initializes a new instance of Tile class.
	/// </summary>
	Tile(int value, int x, int y);

	/// <summary>
	/// Gets tile's symbol.
	/// </summary>
	char GetValue() const;

	/// <summary>
	/// Checks if tile's placements is correct.
	/// </summary>
	bool CheckPlacement(int x, int y) const;
private:
	char value;
	int correctX;
	int correctY;
};

