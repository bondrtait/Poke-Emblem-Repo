#pragma once

#include <SFML\Graphics.hpp>
#include "Tile.h"

using namespace sf;

class GridSelector
{
private:
	//Sprite m_sprite;

	RectangleShape m_selector;

	// The particular Tile currently highlighted by the Selector
	Tile* m_tileSelected { nullptr };

	// Pixel position of the Selector
	Vector2f m_position;

	//How many switches per second can be performed
	const float m_switchRate { 0.7 };

	// Time in seconds passed since last time the Selector moved to another tile
	float m_timeSinceLastSwitch{ 0 };

	// Which directions is the Selector currently moving in
	bool m_leftPressed { false };
	bool m_rightPressed { false };
	bool m_upPressed { false };
	bool m_downPressed { false };

public:
	GridSelector();

	void initialSet(Tile* initialTile);

	RectangleShape& getShape();

	void handleInput(float timeElapsed);

	//void update(float elapsedTime);

};