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

	// A class to manage all the Stages
	BattleStageManager m_BSM;

	const int TILE_SIZE = 32;
	const int VERTS_IN_QUAD = 4;

	// A regular RenderWindow
	RenderWindow m_Window;
	
	// The main View
	View m_MainView;
	
	//View m_HudView;

	// Texture for the BattleStage tiles
	Texture m_TextureTiles;
	
	// Private functions for internal use only
	//void input();
	void update();
	void draw();



public:
	// The Engine constructor
	Engine();
	
	// Run will call all the private functions
	void run();
};