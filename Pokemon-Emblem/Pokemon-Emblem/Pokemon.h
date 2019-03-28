#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TextureHolder.h"

using namespace sf;

class Pokemon
{
private:
	Sprite m_sprite;
	GridLocation m_location;
public:
	Pokemon();

	void spawn (GridLocation loc);
	
	Sprite& getSprite();
	GridLocation& getLocation();
};
