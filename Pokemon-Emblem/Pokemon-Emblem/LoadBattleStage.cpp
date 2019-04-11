#include "pch.h"
#include "BattleStageManager.h"

void BattleStageManager::loadBattleStage()
{
	// Delete the previously allocated memory
	for (int i = 0; i < m_tileMap.getSize().y; ++i)
	{
		for (int j = 0; j < m_tileMap.getSize().x; j++)
			delete[] m_tileMap.getTile(GridLocation(j, i));
	}
	
	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_tileMap.generateTileMap();

	m_selector.spawn(GridLocation(20,20), m_tileMap.getSize());

	loadTeams("data/playerTeam.json");
	
	for (Pokemon* poke : m_playerTeam)
	{
		poke->spawn(poke->getLocation());
		m_tileMap.getTile(poke->getLocation())->putPokemonHere(poke);
	}
}