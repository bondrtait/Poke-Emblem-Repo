#include "pch.h"
#include "BattleStageManager.h"

void BattleStageManager::loadBattleStage()
{
	// Delete the previously allocated memory
	for (int i = 0; i < m_BattleStageSize.y; ++i)
	{
		for (int j = 0; j < m_BattleStageSize.x; j++)
			delete[] m_tileMap[i][j];
	}
	
	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_tileMap = generateTileMap(m_VAStage);

	m_selector.spawn(GridLocation(20,20), m_BattleStageSize);

	//For testing
	GridLocation loc(15, 15);
	
	pikachu.spawn(loc);
	m_tileMap[loc.y][loc.x]->putPokemonHere(&pikachu);
}