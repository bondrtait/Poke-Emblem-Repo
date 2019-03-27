#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const int TILE_SIZE = 32;

typedef Vector2i GridLocation;

enum class TileType {
	PLAIN_GROUND,
	ROCK,
	GRASS
};

class Tile
{
private:
	
	//Marks if the tile is occupied by another unit
	bool m_occupied;

	//Marks if the tile is not walkable (tree, rock, fence)
	bool m_walkable;

	// Defines the Tile type - GRASS, PLAIN_GROUND etc.
	TileType m_type; 

	//Stores the position of the tile in the TileMap (row, column)
	GridLocation m_indexPos;

public:	
	//Constructors
	Tile();

	//Set Type and Walkability
	void setType(TileType type);
	   
	//Set Tile's position in the TileMap
	void setPos(int column, int row);

	// Set m_occupied = true
	void occupy();

	// Getters
	bool isOccupied();
	bool isWalkable();
	TileType getType();
	GridLocation& getPos();
};
