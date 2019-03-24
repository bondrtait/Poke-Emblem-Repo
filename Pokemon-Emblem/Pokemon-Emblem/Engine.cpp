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
	//m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

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
	//Clock clock;
	
	while (m_Window.isOpen())
	{
		//Time dt = clock.restart();
		
		// Make a decimal fraction from the delta time
		//float dtAsSeconds = dt.asSeconds();
		
		// Call each part of the game loop in turn
		//input();
		update();
		draw();
	}
}