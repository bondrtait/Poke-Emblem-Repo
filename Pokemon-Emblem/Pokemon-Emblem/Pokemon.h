#pragma once
#ifndef POKEMON_H
#define POKEMON_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "TextureHolder.h"
#include "TileMap.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

class Pokemon
{
private:
	Sprite m_sprite;

	//Location on the tilemap
	GridLocation m_location;

	//Position in pixels on screen
	Vector2f m_position;

	string m_name;

	// Vector to hold Tiles which the Pokemon can reach from its current location
	vector<GridLocation> m_possibleRange;

	//The array of vertices of the Tiles in the possible movement range
	VertexArray m_VARange;

	//Auxillary maps for dijkstra and A* algorithms
	std::unordered_map<GridLocation, GridLocation> m_came_from;
	std::unordered_map<GridLocation, int> m_cost_so_far;

	//A pointer to a tileMap
	TileMap* m_tileMapPtr{nullptr};

	//Holds the best path to the current goal
	vector<GridLocation> m_path;

	int m_pathLength;

	//Manhattan distance function
	int heuristic(GridLocation a, GridLocation b);

	// Move pokemon to an adjacent tile, return true if the pokemon has reached the goal tile center
	bool moveTo(GridLocation &start, GridLocation &end, float elapsedTime, float speed);

	bool m_fainted{ false };
	RectangleShape m_healthBar;
	void updateHealthBar();

	int m_health;
	int m_attack;

public:
	Pokemon();

	Pokemon(TileMap* map, const json::object_t &obj);

	const int MOVEMENT_LIMIT{ 6 };

	//Spawns Pokemon on a specified Tile
	void spawn (GridLocation loc);

	//Performs Dijkstra Search to get all the possible tiles within Pokemon movement range
	void dijkstra_possible_range();

	//Highights the possible movement range using vertex array m_VARange
	void drawPossibleRange(RenderWindow &target);

	//Performs A* search for the best path from pokemon location to the goal
	void a_star_search(GridLocation goal);

	//Move pokemon along the path calculated in the a_star_search
	// return true if the pokemon has reached the destination
	bool followPath(GridLocation &goal, float elapsedTime);

	//Return true if passed location is in Pokemon's movement range
	bool isReachable(const GridLocation &loc);

	Sprite& getSprite();
	GridLocation& getLocation();
	RectangleShape& getHealthBar();
};
#endif