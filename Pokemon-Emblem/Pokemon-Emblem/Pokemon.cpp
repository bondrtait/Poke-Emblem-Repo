#include "pch.h"
#include "Pokemon.h"
#include "Util.h"

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

void Pokemon::givePossibleRange(const vector<GridLocation>& range, Vector2i &stageSize)
{
	if (!m_possibleRange.empty())
		m_possibleRange.clear();

	m_possibleRange = range;

	m_VARange.clear();
	m_VARange.setPrimitiveType(Quads);
	m_VARange.resize(m_possibleRange.size() * VERTS_IN_QUAD);

	int currentVertex = 0;

	for (int i = 0; i < m_possibleRange.size(); ++i)
	{
		//int topLeftVertex = (m_possibleRange[i].x * stageSize.y) + m_possibleRange[i].y;
		m_VARange[currentVertex + 0].position = Vector2f(m_possibleRange[i].x * TILE_SIZE, m_possibleRange[i].y * TILE_SIZE);
		m_VARange[currentVertex + 1].position = Vector2f((m_possibleRange[i].x * TILE_SIZE) + TILE_SIZE, m_possibleRange[i].y * TILE_SIZE);
		m_VARange[currentVertex + 2].position = Vector2f((m_possibleRange[i].x * TILE_SIZE) + TILE_SIZE, (m_possibleRange[i].y * TILE_SIZE) + TILE_SIZE);
		m_VARange[currentVertex + 3].position = Vector2f(m_possibleRange[i].x * TILE_SIZE, (m_possibleRange[i].y * TILE_SIZE) + TILE_SIZE);

		Color hlColor(0, 0, 255, 124);

		m_VARange[currentVertex + 0].color = hlColor;
		m_VARange[currentVertex + 1].color = hlColor;
		m_VARange[currentVertex + 2].color = hlColor;
		m_VARange[currentVertex + 3].color = hlColor;

		currentVertex += VERTS_IN_QUAD;
	}
}

void Pokemon::drawPossibleRange(RenderWindow & target)
{
	target.draw(m_VARange);
}

Sprite& Pokemon::getSprite() { return m_sprite; }

GridLocation& Pokemon::getLocation() { return m_location; }

