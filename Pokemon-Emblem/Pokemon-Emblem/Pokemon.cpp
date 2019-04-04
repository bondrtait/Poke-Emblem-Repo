#include "pch.h"
#include <queue>
#include "Pokemon.h"
#include "Util.h"

int Pokemon::heuristic(GridLocation a, GridLocation b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool Pokemon::moveTo(GridLocation &start, GridLocation &end, float elapsedTime, float speed)
{
	//Calculate the direction of movement
	GridLocation direction = end - start; //problem here

	m_position.x += direction.x * speed * elapsedTime;
	m_position.y += direction.y * speed * elapsedTime;
	
	//m_sprite.setPosition(m_position);

	// check if the sprite went further then the goal center
	if (abs(start.getCenter().x - m_position.x) > TILE_SIZE || abs(start.getCenter().y - m_position.y) > TILE_SIZE) 
	{
		m_position = end.getCenter();
		m_sprite.setPosition(m_position);
		return true;
	}
	else
	{
		m_sprite.setPosition(m_position);
		return false;
	}
}

Pokemon::Pokemon()
{
	m_sprite = Sprite(TextureHolder::GetTexture("graphics/025.png"));
	m_sprite.setOrigin(Vector2f(16.0f, 16.0f));
}

Pokemon::Pokemon(TileMap * map)
{
	m_sprite = Sprite(TextureHolder::GetTexture("graphics/025.png"));
	m_sprite.setOrigin(Vector2f(16.0f, 16.0f));
	m_tileMapPtr = map;
}

void Pokemon::spawn(GridLocation loc)
{
	m_location = loc;
	m_position = loc.getCenter();

	m_sprite.setPosition(m_position);
}

void Pokemon::dijkstra_possible_range()
{
	//Construct a priority_queue that will store tiles and expand
	priority_queue<PQElement, vector<PQElement>, greater<PQElement> > frontier;
	//Put the starting location using std::pair constructor's arguments
	frontier.emplace(0, m_location);

	//Clear cost_so_far if it is not empty
	if (!m_cost_so_far.empty())
		m_cost_so_far.clear();

	//This map Key holds GridLocation and the Value is the number of steps to get from start to that location
	m_cost_so_far[m_location] = 0;

	//Clear possibleRange if it is not empty
	if (!m_possibleRange.empty())
		m_possibleRange.clear();

	while (!frontier.empty())
	{
		//Get the easiest-to-get-to GridLocation and remove it from the frontier
		GridLocation current = frontier.top().second;
		frontier.pop();

		if (m_cost_so_far[current] <= MOVEMENT_LIMIT)
		{
			m_possibleRange.push_back(current);

			auto currNeigh = m_tileMapPtr->neighbors(current);

			for (GridLocation& next : currNeigh)
			{
				int new_cost = m_cost_so_far[current] + 1;

				if (m_cost_so_far.find(next) == m_cost_so_far.end() || new_cost < m_cost_so_far[next])
				{
					m_cost_so_far[next] = new_cost;
					frontier.emplace(new_cost, next);
				}
			}
		}
	}

	m_VARange.clear();
	m_VARange.setPrimitiveType(Quads);
	m_VARange.resize(m_possibleRange.size() * VERTS_IN_QUAD);

	int currentVertex = 0;

	for (int i = 0; i < m_possibleRange.size(); ++i)
	{
		//int topLeftVertex = (m_possibleRange[i].x * stageSize.y) + m_possibleRange[i].y;
		m_VARange[currentVertex + 0].position = Vector2f(m_possibleRange[i].x * TILE_SIZE, m_possibleRange[i].y * TILE_SIZE);
		m_VARange[currentVertex + 1].position = Vector2f((m_possibleRange[i].x * TILE_SIZE) + TILE_SIZE, m_possibleRange[i].y * TILE_SIZE);
		m_VARange[currentVertex + 2].position = Vector2f((m_possibleRange[i].x * TILE_SIZE) + TILE_SIZE, (m_possibleRange[i].y * TILE_SIZE) + TILE_SIZE);
		m_VARange[currentVertex + 3].position = Vector2f(m_possibleRange[i].x * TILE_SIZE, (m_possibleRange[i].y * TILE_SIZE) + TILE_SIZE);

		Color hlColor(0, 0, 255, 124);

		m_VARange[currentVertex + 0].color = hlColor;
		m_VARange[currentVertex + 1].color = hlColor;
		m_VARange[currentVertex + 2].color = hlColor;
		m_VARange[currentVertex + 3].color = hlColor;

		currentVertex += VERTS_IN_QUAD;
	}
}

void Pokemon::drawPossibleRange(RenderWindow & target)
{
	target.draw(m_VARange);
}

void Pokemon::a_star_search(GridLocation goal)
{
	//Construct a priority_queue that will store tiles and expand
	priority_queue<PQElement, vector<PQElement>, greater<PQElement> > frontier;
	//Put the starting location using std::pair constructor's arguments
	frontier.emplace(0, m_location);
	
	//Clear came_from if it is not empty
	if (!m_came_from.empty())
		m_came_from.clear();

	m_came_from[m_location] = m_location;

	//Clear cost_so_far if it is not empty
	if (!m_cost_so_far.empty())
		m_cost_so_far.clear();

	m_cost_so_far[m_location] = 0;

	while (!frontier.empty()) 
	{
		//Get the easiest-to-get-to GridLocation and remove it from the frontier
		GridLocation current = frontier.top().second;
		frontier.pop();

		if (current == goal)
			break;

		for (GridLocation next : m_tileMapPtr->neighbors(current)) {
			int new_cost = m_cost_so_far[current] + 1;
			if (m_cost_so_far.find(next) == m_cost_so_far.end() || new_cost < m_cost_so_far[next]) 
			{
				m_cost_so_far[next] = new_cost;
				int priority = new_cost + heuristic(next, goal);
				frontier.emplace(priority, next);
				m_came_from[next] = current;
			}
		}
	}

	//Reconstruct the path

	if (!m_path.empty())
		m_path.clear();

	GridLocation current = goal;
	while (current != m_location) {
		m_path.push_back(current);
		current = m_came_from[current];
	}
	m_path.push_back(m_location); // optional
	//reverse(m_path.begin(), m_path.end());

	m_pathLength = m_path.size();
}

bool Pokemon::followPath(GridLocation &goal, float elapsedTime)
{
	float speed = TILE_SIZE * m_pathLength;

	if (m_path.size() == 1)
	{
		m_location = goal;
		return true;
	}
	else if (moveTo(m_path.back(), m_path[m_path.size() - 2], elapsedTime, speed))
	{
		m_path.pop_back();
	}
		
	return false;
}

bool Pokemon::isReachable(const GridLocation & loc)
{
		for (auto &tile : m_possibleRange)
			if (tile == loc)
				return true;

		return false;
}

Sprite& Pokemon::getSprite() { return m_sprite; }

GridLocation& Pokemon::getLocation() { return m_location; }

