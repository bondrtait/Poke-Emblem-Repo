#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;
using namespace std;

class LevelManager
{
private:
	Vector2i m_LevelSize;

public:
	const int TILE_SIZE = 32;
	const int VERTS_IN_QUAD = 4;

	Tile** nextLevel(VertexArray& rVaLevel);
	
	Vector2i getLevelSize();
};