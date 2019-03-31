#pragma once
#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int TILE_SIZE = 32;

// A class to hold a 2d cordinates of a single Tile
// I failed to use Vector2i T_T
class GridLocation
{
public:
	int x;
	int y;

	GridLocation();
	GridLocation(int x_coord, int y_coord);

	friend bool operator == (const GridLocation &left, const GridLocation &right);
	friend bool operator != (const GridLocation &left, const GridLocation &right);
	friend bool operator < (const GridLocation &left, const GridLocation &right);
};

namespace std {
	/* implement hash function so we can put GridLocation into an unordered_map */
	template <> struct hash<GridLocation> {
		typedef GridLocation argument_type;
		typedef size_t result_type;
		size_t operator()(const GridLocation& id) const noexcept {
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}

class Pokemon; //forward declaration

enum class TileType {
	PLAIN_GROUND,
	ROCK,
	GRASS
};

class Tile
{
private:
	
	//Pointer to a pokemon in the Tile
	Pokemon* m_occupier = nullptr;

	//Marks if the tile is not walkable (tree, rock, fence)
	bool m_walkable;

	// Defines the Tile type - GRASS, PLAIN_GROUND etc.
	TileType m_type; 

	//Stores the position of the tile in the TileMap (row, column)
	GridLocation m_indexPos;

public:	
	//Constructors
	Tile(TileType type, GridLocation loc);

	void putPokemonHere(Pokemon* pokemon);
	void freeTheTile();

	// Getters
	Pokemon* isOccupied();
	bool isWalkable();
	TileType getType();
	GridLocation& getPos();
};
#endif