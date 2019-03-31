#include "pch.h"
#include "Tile.h"

Tile::Tile(TileType type, GridLocation loc) : m_type(type), m_indexPos(loc)
{
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
};

void Tile::putPokemonHere(Pokemon* pokemon) { m_occupier = pokemon; }

void Tile::freeTheTile() { m_occupier = nullptr; }

Pokemon* Tile::isOccupied() { return m_occupier; }

bool Tile::isWalkable() { return m_walkable; }

TileType Tile::getType() { return m_type; }

GridLocation& Tile::getPos() { return m_indexPos; }

GridLocation::GridLocation() {}

GridLocation::GridLocation(int x_coord, int y_coord) : x(x_coord), y(y_coord)
{
}

bool operator==(const GridLocation & left, const GridLocation & right)
{
	return left.x == right.x && left.y == right.y;
}

bool operator!=(const GridLocation & left, const GridLocation & right)
{
	return !(left == right);
}

bool operator<(const GridLocation & left, const GridLocation & right)
{
	return left.y < right.y || (!(right.y < left.y) && left.x < right.x);
}


