#include "pch.h"
#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::Black);

	// Switch to background view
	//m_Window.setView(m_BGMainView);

	// Draw the background
	//m_Window.draw(m_BackgroundSprite);
		
	// Switch to m_MainView
	m_Window.setView(m_MainView);

	//Draw everything in BSM
	m_BSM.draw(m_Window, m_TextureTiles);

	// Draw the HUD
	// Switch to m_HudView
	//m_Window.setView(m_HudView);

	// Show everything we have just drawn
	m_Window.display();
}