#include "pch.h"
#include "BattleStageManager.h"

void BattleStageManager::loadBattleStage()
{
	// Delete the previously allocated memory
	for (int i = 0; i < m_BattleStageSize.y; ++i)
	{
		delete[] TileMap[i];
	}

	delete[] TileMap;
	
	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	TileMap = generateTileMap(m_VAStage);

	m_selector.initialSet(&TileMap[20][20]);
}