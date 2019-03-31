#pragma once

#include <unordered_map>
#include <array>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "GridSelector.h"
#include "Pokemon.h"

using namespace sf;
using namespace std;

//Typedef for std::priority_queue element
typedef std::pair<int, GridLocation> PQElement;

//The array of posible directions (Up, Down, Left, Right)
const array<GridLocation, 4> DIRS = { GridLocation(1, 0), GridLocation(0, -1), GridLocation(-1, 0), GridLocation(0, 1) };

//The class for managing BattleStages
//It composes and stores a tilemap and vertex array for texture drawing
//Also it stores GridSelector and Pokemon data
//It manages pathfinding
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
	vector<vector<Tile*> > m_tileMap;

	//Create a 2d array of pointers to the Tile objects from the txt file
	vector<vector<Tile*> > generateTileMap(VertexArray& rVaLevel);

	//Pokemon instance temp
	Pokemon pikachu;

	//Pointer to a Pokemon currently selected by the selector
	Pokemon* m_selectedPokemon = nullptr;

	//Track Return presses
	bool m_enterPressed = false;

	//The time in seconds since last change of selector state
	float m_lastSelectionTime = 0.0f;

	// Check if the passed location is valid on the current tileMap
	bool in_bounds(GridLocation id) const;

	// Returns the adjacency list for the passed location
	vector<GridLocation> neighbors(GridLocation id);

	// Vector to hold Tiles which the selected Pokemon can reach
	vector<GridLocation> m_possibleRange;

	//Performs Dijkstra Search to get all the possible tiles within Pokemon movement range
	vector<GridLocation> dijkstra_possible_range (GridLocation start, 
		unordered_map<GridLocation, GridLocation>& came_from, 
		unordered_map<GridLocation, int>& cost_so_far);

public:
	const int VERTS_IN_QUAD = 4;

	//Think about constructor here ....?
	//BattleStageManager();

	// Functions to handle BSM's internal objects updating and input, these are just to be able to call from the Engine
	void handleInput();
	void update(float elapsedTime);
	void draw(RenderWindow &target, Texture &tex);
	
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