#include "pch.h"

#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"

using namespace sf;
using namespace std;

Tile** LevelManager::nextLevel(VertexArray& rVaLevel)
{
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Load the appropriate level from a text file
	string levelToLoad("levels/stage1.txt");

	ifstream inputFile(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	Tile** arrayLevel = new Tile*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new Tile[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++) {
			const char val = row[x];
			arrayLevel[y][x].setType(atoi(&val));
		}
		y++;
	}
	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);
	
	// Start at the beginning of the vertex array
	int currentVertex = 0;
	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
			rVaLevel[currentVertex + 1].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);
			rVaLevel[currentVertex + 2].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);
			rVaLevel[currentVertex + 3].position = Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);
			
			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x].getType() * TILE_SIZE;
			rVaLevel[currentVertex + 0].texCoords =	Vector2f(0, 0 + verticalOffset);
			rVaLevel[currentVertex + 1].texCoords =	Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVaLevel[currentVertex + 2].texCoords =	Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVaLevel[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			
			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	return arrayLevel;
} // End of nextLevel function

Vector2i LevelManager::getLevelSize() { return m_LevelSize; }