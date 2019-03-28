#pragma once

//#include <unordered_map>
//#include <queue>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "GridSelector.h"
#include "Pokemon.h"

using namespace sf;
using namespace std;

//The class for managing BattleStages
//It composes and stores a tilemap and vertex array for texture drawing
//
class BattleStageManager
{
private:
	//The size of the battle stage represented in tiles
	Vector2i m_BattleStageSize;

	// The selector to interact with the Pokemon and BattleStage
	GridSelector m_selector;

	// The vertex array for the BattleStage tiles
	VertexArray m_VAStage;

	// The 2d array with the Tiles for the BattleStage
	// A pointer to a pointer
	Tile** m_tileMap = nullptr;

	//Create a 2d array of pointers to the Tile objects from the txt file
	Tile** generateTileMap(VertexArray& rVaLevel);

	//Pokemon instance temp
	Pokemon pikachu;

	//The array of posible directions (Up, Down, Left, Right)
	//static array<GridLocation, 4> DIRS;

	// Check if the passed location is valid on the current tileMap
	//bool in_bounds(GridLocation id) const;

	// Returns the adjacency list for the passed location
	//std::vector<GridLocation> neighbors(GridLocation id) const

	//Performs Dijkstra

public:
	const int VERTS_IN_QUAD = 4;

	//Think about constructor here ....?
	//BattleStageManager();

	// Functions to handle BSM's internal objects updating and input, these are just to be able to call from the Engine
	void handleInput();
	void update();
	//void draw(RenderWindow &target);
	
	//Loads a new BattleStage, deleting any previous
	void loadBattleStage();
	
	//Getters
	GridSelector& getGridSelector();
	Vector2i getBattleStageSize();
	VertexArray& getVA();
	Pokemon& getPokemon();

	//Return a Tile with the specified indices
	Tile* getTile(GridLocation loc);
};