#pragma once

#include <SFML\Graphics.hpp>
#include "Tile.h"

using namespace sf;

enum class SelectorState
{
	EXPLORING,
	SELECTING_TARGET,
	WAITING
};

class GridSelector
{
private:
	//Sprite m_sprite;
	
	RectangleShape m_shape;

	// The size of the battle stage in tiles
	Vector2i m_stageSize;

	// The pair of indices of the m_tileSelected in the m_tileMap
	GridLocation m_indexPos;

	// Pixel position of the Selector
	Vector2f m_position;

	//One switch in 700ms can be performed
	const Int32 m_switchRate { 150 };

	//The clock to count time between switches
	Clock m_switchClock;

	// Which directions is the Selector currently moving in
	bool m_leftPressed { false };
	bool m_rightPressed { false };
	bool m_upPressed { false };
	bool m_downPressed { false };

	SelectorState m_currentState = SelectorState::EXPLORING;

public:
	//Constructor
	GridSelector();

	//Spawn selector when the stage starts
	void spawn(GridLocation pos, Vector2i stageSize);



	RectangleShape& getSprite();
	Vector2f getCenter();
	GridLocation& getLocation();
	SelectorState getState();

	void changeState(SelectorState state);

	void handleInput();
	//Update selector position according to the input
	void update();

};