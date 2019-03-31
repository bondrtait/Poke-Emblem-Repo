#include "pch.h"

#include <queue>
#include <functional>
#include <fstream>
#include "TextureHolder.h"
#include "BattleStageManager.h"


using namespace sf;
using namespace std;

vector<GridLocation> BattleStageManager::neighbors(GridLocation id)
{
	vector<GridLocation> results;

	for (GridLocation dir : DIRS) {
		GridLocation next( id.x + dir.x, id.y + dir.y );
		if (in_bounds(next) && getTile(next)->isWalkable()) 
			results.push_back(next);
	}

	if ((id.x + id.y) % 2 == 0) 
		// aesthetic improvement on square grids
		reverse(results.begin(), results.end());

	return results;
}

bool BattleStageManager::in_bounds(GridLocation id) const
{
	return (0 <= id.x && id.x < m_BattleStageSize.x && 0 <= id.y && id.y < m_BattleStageSize.y);
}

vector<GridLocation> BattleStageManager::BattleStageManager::dijkstra_possible_range(GridLocation start,
	unordered_map<GridLocation, GridLocation>& came_from, 
	unordered_map<GridLocation, int>& cost_so_far)
{
	//Construct a priority_queue that will store tiles and expand
	priority_queue<PQElement, vector<PQElement>, greater<PQElement> > frontier;
	//Put the starting location using std::pair constructor's arguments
	frontier.emplace(0, start);

	came_from[start] = start;
	//This map Key holds GridLocation and the Value is the number of steps to get from start to that location
	cost_so_far[start] = 0;

	vector<GridLocation> results;

	while (!frontier.empty())
	{
		//Get the easiest-to-get-to GridLocation and remove it from the frontier
		GridLocation current = frontier.top().second;
		frontier.pop();

		if (cost_so_far[current] <= 6)
		{
			results.push_back(current);
			
			auto currNeigh = neighbors(current);

			for (GridLocation& next : currNeigh)
			{	
				int new_cost = cost_so_far[current] + 1;
				
				if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
				{
					cost_so_far[next] = new_cost;
					came_from[next] = current;
					frontier.emplace(new_cost, next);
				}
			}
		}
	}

	return results;
}

vector<vector<Tile*> > BattleStageManager::generateTileMap(VertexArray& rVaLevel)
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

	vector<vector<Tile*> > battleStageGrid;

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		battleStageGrid.push_back(vector<Tile*>());
		for (int x = 0; x < row.length(); x++) {
			const char val = row[x];
			battleStageGrid[y].push_back(new Tile(static_cast<TileType>(atoi(&val)), GridLocation(x, y)));
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
			int verticalOffset = static_cast<int>(battleStageGrid[y][x]->getType()) * TILE_SIZE;
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

Tile* BattleStageManager::getTile(GridLocation loc) { return m_tileMap[loc.y][loc.x]; }

GridSelector& BattleStageManager::getGridSelector() { return m_selector; }

Pokemon& BattleStageManager::getPokemon() { return pikachu; };

void BattleStageManager::handleInput()
{
	m_selector.handleInput();

	//Pointer to the tile which is highlighted by the GridSelector
	auto pokePtr = m_tileMap[m_selector.getLocation().y][m_selector.getLocation().x];

	if (m_selector.getState() == SelectorState::EXPLORING)
	{
		if (Keyboard::isKeyPressed(Keyboard::Return) && pokePtr->isOccupied())
			m_enterPressed = true;
		else
			m_enterPressed = false;
	}
	else if (m_selector.getState() == SelectorState::SELECTING_TARGET)
	{
		if (Keyboard::isKeyPressed(Keyboard::Return) && pokePtr->isWalkable())
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
			m_selectedPokemon = m_tileMap[m_selector.getLocation().y][m_selector.getLocation().x]->isOccupied();
			
			m_selector.changeState(SelectorState::SELECTING_TARGET);
			m_lastSelectionTime = 0.0f;
		}
		else if (m_selector.getState() == SelectorState::SELECTING_TARGET)
		{
			//Respawn the previously selected Pokemon on the new location
			m_selectedPokemon->spawn(m_selector.getLocation());
			
			//Free the tile m_selectedPokemon previously occupied
			getTile(m_selectedPokemon->getLocation())->freeTheTile();
			//Put m_selected Pokemon to a new tile
			getTile(m_selector.getLocation())->putPokemonHere(m_selectedPokemon);
			
			//The Pokemon is not selected anymore
			m_selectedPokemon = nullptr;

			m_selector.changeState(SelectorState::EXPLORING);
			m_lastSelectionTime = 0.0f;
		}
	}
	else
		m_lastSelectionTime += elapsedTime;
}


void BattleStageManager::draw(RenderWindow &target, Texture &tex)
{
	// Draw the Level
	target.draw(m_VAStage, &tex);

	//draw highlighted tiles

	//Draw selector
	target.draw(m_selector.getSprite());

	//Draw pikachu
	target.draw(pikachu.getSprite());
}

