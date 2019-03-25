#include "pch.h"
#include "GridSelector.h"

GridSelector::GridSelector() 
{
	m_selector.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
	m_selector.setFillColor(Color::Transparent);
	m_selector.setOutlineThickness(3);
	m_selector.setOutlineColor(Color::Red);
	m_selector.setOrigin(Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
}

void GridSelector::initialSet(Tile* initialTile)
{
	m_tileSelected = initialTile;

	m_position.x = (initialTile->getPos().x * TILE_SIZE) + TILE_SIZE / 2;
	m_position.y = (initialTile->getPos().y * TILE_SIZE) + TILE_SIZE / 2;

	m_selector.setPosition(m_position);
}

RectangleShape& GridSelector::getShape() { return m_selector; }

void GridSelector::handleInput(float timeElapsed)
{

	if (Keyboard::isKeyPressed(Keyboard::Left) && m_timeSinceLastSwitch > m_switchRate)
	{
////
	}
	else


	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
////
	}
}