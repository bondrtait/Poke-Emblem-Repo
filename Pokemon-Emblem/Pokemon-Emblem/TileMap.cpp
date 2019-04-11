#include "pch.h"
#include "TileMap.h"
#include <fstream>

void TileMap::generateTileMap()
{
	m_mapSize.x = 0;
	m_mapSize.y = 0;

	// Load the appropriate Stage from a text file
	string stageToLoad("data/stage1.txt");

	ifstream inputFile(stageToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_mapSize.y;
	}

	// Store the length of the rows
	m_mapSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	if (!m_vTiles.empty())
		m_vTiles.clear();

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		m_vTiles.push_back(vector<Tile*>());
		for (int x = 0; x < row.length(); x++) {
			const char val = row[x];
			m_vTiles[y].push_back(new Tile(static_cast<TileType>(atoi(&val)), GridLocation(x, y)));
		}
		y++;
	}
	// close the file
	inputFile.close();

	// What type of primitive are we using?
	m_VAMap.setPrimitiveType(Quads);

	// Set the size of the vertex array
	m_VAMap.resize(m_mapSize.x * m_mapSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;
	for (int x = 0; x < m_mapSize.x; x++)
	{
		for (int y = 0; y < m_mapSize.y; y++)
		{
			// Position each vertex in the current quad
			m_VAMap[currentVertex + 0].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
			m_VAMap[currentVertex + 1].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);
			m_VAMap[currentVertex + 2].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);
			m_VAMap[currentVertex + 3].position = Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = static_cast<int>(m_vTiles[y][x]->getType()) * TILE_SIZE;
			m_VAMap[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			m_VAMap[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			m_VAMap[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			m_VAMap[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex += VERTS_IN_QUAD;
		}
	}
}

bool TileMap::in_bounds(GridLocation id) const
{
	return (0 <= id.x && id.x < m_mapSize.x && 0 <= id.y && id.y < m_mapSize.y);
}

vector<GridLocation> TileMap::neighbors(GridLocation id)
{
	vector<GridLocation> results;

	for (GridLocation dir : DIRS) {
		GridLocation next(id.x + dir.x, id.y + dir.y);
		if (in_bounds(next) && getTile(next)->isWalkable())
			results.push_back(next);
	}

	if ((id.x + id.y) % 2 == 0)
		// aesthetic improvement on square grids
		reverse(results.begin(), results.end());

	return results;
}

Tile * TileMap::getTile(const GridLocation &loc) { return m_vTiles[loc.y][loc.x]; }

Vector2i TileMap::getSize() { return m_mapSize; }

VertexArray TileMap::getVA() { return m_VAMap; }