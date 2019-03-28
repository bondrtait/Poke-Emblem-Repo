#include "pch.h"
#include "Pokemon.h"

Pokemon::Pokemon()
{
	m_sprite = Sprite(TextureHolder::GetTexture("graphics/025.png"));
	m_sprite.setOrigin(Vector2f(10.0f, 10.0f));
}

void Pokemon::spawn(GridLocation loc)
{
	m_location = loc;

	m_sprite.setPosition((m_location.x * TILE_SIZE) + (TILE_SIZE / 2), (m_location.y * TILE_SIZE) + (TILE_SIZE / 2));
}

Sprite& Pokemon::getSprite() { return m_sprite; }

GridLocation& Pokemon::getLocation() { return m_location; }