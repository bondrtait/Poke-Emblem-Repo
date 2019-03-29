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

public:
	Pokemon();
	const int WALK_DISTANCE{ 6 };
	void spawn (GridLocation loc);
	
	Sprite& getSprite();
	GridLocation& getLocation();
};
#endif