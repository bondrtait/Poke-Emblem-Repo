#include "pch.h"
#include "Engine.h"

Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = 800;
	resolution.y = 600;
	m_Window.create(VideoMode(resolution.x, resolution.y), "Pokemon Emblem");

	// Initialize the fullscreen view
	m_MainView.setSize(resolution);

	// Inititialize the split screen Views
	//m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
	
	// Associate the sprite with the texture
	//m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the vertex array
	m_TextureTiles = TextureHolder::GetTexture("graphics/tileset.png");
}

void Engine::run()
{
	// Timing
	Clock clock;

	m_BSM.loadBattleStage();
	m_MainView.setCenter(m_BSM.getGridSelector().getCenter());

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();
		
		// Call each part of the game loop in turn
		input();
		update(dtAsSeconds);
		draw();
	}
}


void Engine::viewFollowSelector()
{
	Vector2f viewSize(m_MainView.getSize());
	Vector2f viewCenter(m_MainView.getCenter());
	
	//Construct a FloatRect that represents the mainView
	FloatRect viewRect(viewCenter.x - (viewSize.x / 2), viewCenter.y - (viewSize.y / 2), viewSize.x, viewSize.y);

	FloatRect selectorRect = m_BSM.getGridSelector().getSprite().getGlobalBounds();

	//The variables that mark if selector vertex is out of the mainView boundaries
	bool topLeftOut{ !viewRect.contains(selectorRect.left, selectorRect.top) };
	bool topRightOut{ !viewRect.contains(selectorRect.left + selectorRect.width, selectorRect.top) };
	bool bottomLeftOut{ !viewRect.contains(selectorRect.left, selectorRect.top + selectorRect.height) };
	bool bottomRightOut{ !viewRect.contains(selectorRect.left + selectorRect.width, selectorRect.top + selectorRect.height) };

	//Selector moving up
	if (topLeftOut && topRightOut)
		m_MainView.move(0, -TILE_SIZE);

	//Selector moving down
	if (bottomLeftOut && bottomRightOut)
		m_MainView.move(0, TILE_SIZE);

	//Selector moving left
	if (topLeftOut && bottomLeftOut)
		m_MainView.move(-TILE_SIZE, 0);

	//Selector moving right
	if (topRightOut && bottomRightOut)
		m_MainView.move(TILE_SIZE, 0);
}