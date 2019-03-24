#include "pch.h"
#include "Tile.h"

Tile::Tile() {};

void Tile:: setType(const int &type)
{
	m_type = type;

	if (type == 1)
	{
		m_walkable = false;
	}
	else
		m_walkable = true;
}

void Tile::occupy() { m_occupied = true; }

bool Tile::isOccupied() { return m_occupied; }

bool Tile::isWalkable() { return m_walkable; }

int Tile::getType() { return m_type; }