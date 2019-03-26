#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "GridSelector.h"

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

	// The vertex array for the BattleStage tiles
	VertexArray m_VAStage;

	GridSelector m_selector;

	// The 2d array with the map for the BattleStage
	// A pointer to a pointer
	Tile** m_tileMap = nullptr;

	//Create a 2d array of pointers to the Tile objects from the txt file
	Tile** generateTileMap(VertexArray& rVaLevel);

public:
	const int VERTS_IN_QUAD = 4;
	   	
	Vector2i getBattleStageSize();

	//Loads a new BattleStage, deleting any previous
	void loadBattleStage();

	VertexArray& getVA();

	//Return a Tile with the specified indices
	Tile* getTile(int x, int y);

	GridSelector& getGridSelector();

	void handleInput();

	void update();
};