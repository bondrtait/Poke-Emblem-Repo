#pragma once
#ifndef POKEMON_H
#define POKEMON_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "TileMap.h"

using namespace sf;



class Pokemon
{
private:
	Sprite m_sprite;
	GridLocation m_location;
	
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

	int heuristic(GridLocation a, GridLocation b);

public:
	Pokemon();

	Pokemon(TileMap* map);

	const int MOVEMENT_LIMIT{ 6 };

	//Spawns Pokemon on a specified Tile
	void spawn (GridLocation loc);

	//Performs Dijkstra Search to get all the possible tiles within Pokemon movement range
	void dijkstra_possible_range();

	//Highights the possible movement range using vertex array m_VARange
	void drawPossibleRange(RenderWindow &target);

	//Performs A* search for the best path from pokemon location to the goal
	void a_star_search(GridLocation goal);

	//Return true if passed location is in Pokemon's movement range
	bool isReachable(const GridLocation &loc);
	
	Sprite& getSprite();
	GridLocation& getLocation();
};
#endif