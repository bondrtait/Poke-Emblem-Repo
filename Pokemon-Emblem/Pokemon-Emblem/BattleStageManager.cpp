#include "pch.h"

#include "TextureHolder.h"
#include <fstream>
#include "BattleStageManager.h"

using namespace sf;
using namespace std;

Tile** BattleStageManager::generateTileMap(VertexArray& rVaLevel)
{
	m_BattleStageSize.x = 0;
	m_BattleStageSize.y = 0;

	// Load the appropriate Stage from a text file
	string stageToLoad("levels/stage1.txt");

	ifstream inputFile(stageToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_BattleStageSize.y;
	}

	// Store the length of the rows
	m_BattleStageSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2d array to hold the Tile values from the file
	Tile** battleStageGrid = new Tile*[m_BattleStageSize.y];
	for (int i = 0; i < m_BattleStageSize.y; ++i)
	{
		// Add a new array into each array element
		battleStageGrid[i] = new Tile[m_BattleStageSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++) {
			const char val = row[x];
			battleStageGrid[y][x].setType(static_cast<TileType>(atoi(&val)));
			battleStageGrid[y][x].setPos(x, y);
		}
		y++;
	}
	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVaLevel.resize(m_BattleStageSize.x * m_BattleStageSize.y * VERTS_IN_QUAD);
	
	// Start at the beginning of the vertex array
	int currentVertex = 0;
	for (int x = 0; x < m_BattleStageSize.x; x++)
	{
		for (int y = 0; y < m_BattleStageSize.y; y++)
		{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
			rVaLevel[currentVertex + 1].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);
			rVaLevel[currentVertex + 2].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);
			rVaLevel[currentVertex + 3].position = Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);
			
			// Which tile from the sprite sheet should we use
			int verticalOffset = static_cast<int>(battleStageGrid[y][x].getType()) * TILE_SIZE;
			rVaLevel[currentVertex + 0].texCoords =	Vector2f(0, 0 + verticalOffset);
			rVaLevel[currentVertex + 1].texCoords =	Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVaLevel[currentVertex + 2].texCoords =	Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVaLevel[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			
			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	return battleStageGrid;
} // End of nextLevel function

Vector2i BattleStageManager::getBattleStageSize() { return m_BattleStageSize; }

VertexArray& BattleStageManager::getVA() { return m_VAStage; }

Tile* BattleStageManager::getTile(GridLocation loc) { return &m_tileMap[loc.y][loc.x]; }

GridSelector& BattleStageManager::getGridSelector() { return m_selector; }

Pokemon& BattleStageManager::getPokemon() { return pikachu; };

void BattleStageManager::handleInput()
{
	m_selector.handleInput();
}

void BattleStageManager::update()
{
	m_selector.update();
}

