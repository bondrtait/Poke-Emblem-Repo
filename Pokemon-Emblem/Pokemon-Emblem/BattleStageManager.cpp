#include "pch.h"

#include <queue>
#include <functional>
#include <fstream>
#include "TextureHolder.h"
#include "BattleStageManager.h"


using namespace sf;
using namespace std;

int BattleStageManager::heuristic(GridLocation a, GridLocation b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

GridSelector& BattleStageManager::getGridSelector() { return m_selector; }

Pokemon& BattleStageManager::getPokemon() { return pikachu; };

void BattleStageManager::handleInput()
{
	m_selector.handleInput();

	//Pointer to the tile which is highlighted by the GridSelector
	auto tilePtr = m_tileMap.getTile(m_selector.getLocation());

	if (m_selector.getState() == SelectorState::EXPLORING)
	{
		if (Keyboard::isKeyPressed(Keyboard::Return) && tilePtr->isOccupied())
			m_enterPressed = true;
		else
			m_enterPressed = false;
	}
	else if (m_selector.getState() == SelectorState::SELECTING_TARGET)
	{
		if (Keyboard::isKeyPressed(Keyboard::Return) && tilePtr->isWalkable())
			m_enterPressed = true;
		else
			m_enterPressed = false;
	}
}

void BattleStageManager::update(float elapsedTime)
{
	m_selector.update();

	if (m_enterPressed && m_lastSelectionTime > 0.7f)
	{
		if (m_selector.getState() == SelectorState::EXPLORING)
		{
			//Get a pointer to the Pokemon that is on the same tile with the selector when Enter is pressed
			m_selectedPokemon = m_tileMap.getTile(m_selector.getLocation())->isOccupied();
			
			//Calculate the possible range
			m_selectedPokemon->dijkstra_possible_range();

			m_selector.changeState(SelectorState::SELECTING_TARGET);
			m_lastSelectionTime = 0.0f;
		}
		else if (m_selector.getState() == SelectorState::SELECTING_TARGET)
		{
			
			if (m_selectedPokemon->isReachable(m_selector.getLocation()))
			{
				m_selectedPokemon->a_star_search(m_selector.getLocation());
				
				//Respawn the previously selected Pokemon on the new location
				m_selectedPokemon->spawn(m_selector.getLocation());

				//Free the tile m_selectedPokemon previously occupied
				m_tileMap.getTile(m_selectedPokemon->getLocation())->freeTheTile();
				//Put m_selected Pokemon to a new tile
				m_tileMap.getTile(m_selector.getLocation())->putPokemonHere(m_selectedPokemon);

				//The Pokemon is not selected anymore
				m_selectedPokemon = nullptr;

				m_selector.changeState(SelectorState::EXPLORING);
				m_lastSelectionTime = 0.0f;
			}
		}
	}
	else
		m_lastSelectionTime += elapsedTime;
}


void BattleStageManager::draw(RenderWindow &target, Texture &tex)
{
	// Draw the Level
	target.draw(m_tileMap.getVA(), &tex);

	//Draw selected Pokemon possible movement range
	if (m_selector.getState() == SelectorState::SELECTING_TARGET)
		m_selectedPokemon->drawPossibleRange(target);

	//Draw selector
	target.draw(m_selector.getSprite());

	//Draw pikachu
	target.draw(pikachu.getSprite());
}

