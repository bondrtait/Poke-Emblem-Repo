#pragma once

class Tile
{
private:
	
	//Marks if the tile is occupied by another unit
	bool m_occupied;
	//Marks if the tile is not walkable (tree, rock, fence)
	bool m_walkable;

	//The tile type 0 - plain ground, 1 - rocks, 2 grass
	int m_type; 

public:
	//Constructor
	Tile();

	//Set walkability
	void setType(const int &type);

	// Set m_occupied = true
	void occupy();

	// Getters
	bool isOccupied();
	bool isWalkable();
	int getType();
};
