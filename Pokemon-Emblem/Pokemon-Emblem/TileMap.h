#pragma once

#include <vector>
#include "Tile.h"
#include <array>

using namespace std;

class TileMap
{
private:
	//The size of the stage in Tiles
	Vector2i m_mapSize;

	// The 2d vector with the Tiles for the BattleStage
	vector<vector<Tile*> > m_vTiles;

	// The vertex array for the BattleStage tiles
	VertexArray m_VAMap;

public:
	//The array of posible directions (Up, Down, Left, Right)
	array<GridLocation, 4> DIRS = { GridLocation(1, 0), GridLocation(0, -1), GridLocation(-1, 0), GridLocation(0, 1) };

	Vector2i getSize();
	VertexArray getVA();

	//Create a 2d array of pointers to the Tile objects from the txt file
	void generateTileMap();

	// Check if the passed location is valid on the current tileMap
	bool in_bounds(GridLocation id) const;

	// Returns the adjacency list for the passed location
	vector<GridLocation> neighbors(GridLocation id);

	//Return a Tile of the specified location
	Tile* getTile(GridLocation loc);
};