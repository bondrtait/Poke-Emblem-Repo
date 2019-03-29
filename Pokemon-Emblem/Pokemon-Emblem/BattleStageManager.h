#pragma once

//#include <unordered_map>
//#include <queue>
#include <array>
#include <vector>
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
	//bool in_bounds(GridLocation id) const;

	// Returns the adjacency list for the passed location
	//vector<GridLocation> neighbors(GridLocation id) const;

	//Performs Dijkstra

public:
	const int VERTS_IN_QUAD = 4;

	//The array of posible directions (Up, Down, Left, Right)
	static array<GridLocation, 4> DIRS;

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