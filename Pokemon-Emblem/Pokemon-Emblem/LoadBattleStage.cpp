#include "pch.h"
#include "BattleStageManager.h"

void BattleStageManager::loadBattleStage()
{
	// Delete the previously allocated memory
	for (int i = 0; i < m_BattleStageSize.y; ++i)
	{
		delete[] m_tileMap[i];
	}

	delete[] m_tileMap;
	
	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_tileMap = generateTileMap(m_VAStage);

	m_selector.spawn(GridLocation(20,20), m_BattleStageSize);

	pikachu.spawn(GridLocation(15, 15));
}