#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;
using namespace std;

class BattleStageManager
{
private:
	Vector2i m_BattleStageSize;

public:
	const int TILE_SIZE = 32;
	const int VERTS_IN_QUAD = 4;

	Tile** generateBattleStage(VertexArray& rVaLevel);
	
	Vector2i getBattleStageSize();
};