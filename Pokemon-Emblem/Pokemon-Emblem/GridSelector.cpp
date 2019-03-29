#include "pch.h"
#include "GridSelector.h"

GridSelector::GridSelector() 
{
	m_shape.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
	m_shape.setFillColor(Color::Transparent);
	m_shape.setOutlineThickness(3);
	m_shape.setOutlineColor(Color::Red);
	m_shape.setOrigin(Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
}

void GridSelector::spawn(GridLocation pos, Vector2i stageSize)
{
	m_indexPos = pos;
	m_stageSize = stageSize;
	
	m_position.x = (m_indexPos.x * TILE_SIZE) + TILE_SIZE / 2;
	m_position.y = (m_indexPos.y * TILE_SIZE) + TILE_SIZE / 2;

	m_shape.setPosition(m_position);
}

RectangleShape& GridSelector::getSprite() { return m_shape; }

Vector2f GridSelector::getCenter() { return m_position; }

GridLocation& GridSelector::getLocation() { return m_indexPos; }

SelectorState GridSelector::getState() { return m_currentState; }

void GridSelector::changeState(SelectorState state) 
{ 
	m_currentState = state;

	if (m_currentState == SelectorState::EXPLORING)
		m_shape.setOutlineColor(Color::Red);
	if (m_currentState == SelectorState::SELECTING_TARGET)
		m_shape.setOutlineColor(Color::Blue);
}

void GridSelector::handleInput()
{
	//Check if time since last switch is greater then the switch rate && if the direction key is pressed
	if (Keyboard::isKeyPressed(Keyboard::Left) && m_switchClock.getElapsedTime().asMilliseconds() > m_switchRate)
	{
		m_leftPressed = true;
		m_switchClock.restart();
	}
	else
		m_leftPressed = false;

	if (Keyboard::isKeyPressed(Keyboard::Right) && m_switchClock.getElapsedTime().asMilliseconds() > m_switchRate)
	{
		m_rightPressed = true;
		m_switchClock.restart();
	}
	else
		m_rightPressed = false;

	if (Keyboard::isKeyPressed(Keyboard::Up) && m_switchClock.getElapsedTime().asMilliseconds() > m_switchRate)
	{
		m_upPressed = true;
		m_switchClock.restart();
	}
	else
		m_upPressed = false;

	if (Keyboard::isKeyPressed(Keyboard::Down) && m_switchClock.getElapsedTime().asMilliseconds() > m_switchRate)
	{
		m_downPressed = true;
		m_switchClock.restart();
	}
	else
		m_downPressed = false;
}

void GridSelector::update()
{
	if (m_leftPressed && m_indexPos.x > 0)
		m_indexPos.x -= 1;

	if (m_rightPressed && m_indexPos.x < m_stageSize.x - 1)
		m_indexPos.x += 1;

	if (m_upPressed && m_indexPos.y > 0)
		m_indexPos.y -= 1;

	if (m_downPressed && m_indexPos.y < m_stageSize.y - 1)
		m_indexPos.y += 1;

	m_position.x = (m_indexPos.x * TILE_SIZE) + TILE_SIZE / 2;
	m_position.y = (m_indexPos.y * TILE_SIZE) + TILE_SIZE / 2;

	m_shape.setPosition(m_position);
}
