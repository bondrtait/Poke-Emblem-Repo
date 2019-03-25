#include "pch.h"
#include "Tile.h"

Tile::Tile() {};

void Tile::setType(TileType type)
{
	m_type = type;

	switch (type)
	{
	case TileType::PLAIN_GROUND:
		m_walkable = true;
		break;
	case TileType::ROCK:
		m_walkable = false;
		break;
	case TileType::GRASS:
		m_walkable = true;
		break;
	}
}

void Tile::setPos(int column, int row)
{
	m_indexPos.x = column;
	m_indexPos.y = row;
}

void Tile::occupy() { m_occupied = true; }

bool Tile::isOccupied() { return m_occupied; }

bool Tile::isWalkable() { return m_walkable; }

TileType Tile::getType() { return m_type; }

Vector2i& Tile::getPos() { return m_indexPos; }
