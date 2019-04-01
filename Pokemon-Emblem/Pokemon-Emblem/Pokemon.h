#pragma once
#ifndef POKEMON_H
#define POKEMON_H
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Tile.h"

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

public:
	Pokemon();

	const int MOVEMENT_LIMIT{ 6 };

	//Spawns Pokemon on a specified Tile
	void spawn (GridLocation loc);

	//Provides values for the vector of Tiles within MovementLimit and 
	//fills the VertexArray m_VARange for further drawing
	void givePossibleRange(const vector<GridLocation> &range, Vector2i &stageSize);
	
	//Highights the possible movement range using vertex array m_VARange
	void drawPossibleRange(RenderWindow &target);

	bool isReachable(const GridLocation &loc)
	{
		for (auto &tile : m_possibleRange)
			if (tile == loc)
				return true;

		return false;
	}
	
	Sprite& getSprite();
	GridLocation& getLocation();
};
#endif