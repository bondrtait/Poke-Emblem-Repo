#pragma once

#ifndef BATTLESTAGEMANAGER_H
#define BATTLESTAGEMANAGER_H

#include <unordered_map>
#include <array>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
//#include "Tile.h"
#include "GridSelector.h"
#include "Pokemon.h"
#include "TileMap.h"

using namespace sf;
using namespace std;

//Typedef for std::priority_queue element
//typedef std::pair<int, GridLocation> PQElement;

//The class for managing BattleStages
//It composes and stores a tilemap and vertex array for texture drawing
//Also it stores GridSelector and Pokemon data
//It manages pathfinding
class BattleStageManager
{
private:

	//A pointer to a tileMap
	TileMap m_tileMap;

	// The selector to interact with the Pokemon and BattleStage
	GridSelector m_selector;

	//Pokemon instance temp
	Pokemon pikachu = Pokemon(&m_tileMap);

	//Pointer to a Pokemon currently selected by the selector
	Pokemon* m_selectedPokemon = nullptr;

	//Track Return presses
	bool m_enterPressed = false;

	//The time in seconds since last change of selector state
	float m_lastSelectionTime = 0.0f;

	int heuristic(GridLocation a, GridLocation b);

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
	Pokemon& getPokemon();
};

#endif