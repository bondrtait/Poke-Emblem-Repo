#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "BattleStageManager.h"

using namespace sf;

class Engine
{
private:
	// The texture holder
	TextureHolder th;

	// A class to manage all the levels
	BattleStageManager m_LM;

	const int TILE_SIZE = 32;
	const int VERTS_IN_QUAD = 4;

	// A regular RenderWindow
	RenderWindow m_Window;
	
	// The main View
	View m_MainView;
	
	//View m_HudView;

	// The vertex array for the BattleStage tiles
	VertexArray m_VALevel;

	// The 2d array with the map for the BattleStage
	// A pointer to a pointer
	Tile** m_ArrayLevel = nullptr;

	// Texture for the BattleStage tiles
	Texture m_TextureTiles;
	
	// Private functions for internal use only
	//void input();
	void update();
	void draw();

	// Load a new level
	void loadBattleStage();

public:
	// The Engine constructor
	Engine();
	
	// Run will call all the private functions
	void run();
};