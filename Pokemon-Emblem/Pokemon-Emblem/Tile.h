#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const int TILE_SIZE = 32;

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
	Vector2i m_indexPos;

public:	
	//Constructors
	Tile();

	//Set walkability
	void setType(TileType type);
	   
	void setPos(int column, int row);

	// Set m_occupied = true
	void occupy();

	// Getters
	bool isOccupied();
	bool isWalkable();
	TileType getType();
	Vector2i& getPos();
};
