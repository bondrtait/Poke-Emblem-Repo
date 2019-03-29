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
