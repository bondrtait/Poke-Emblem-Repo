#include "pch.h"
#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	// Switch to background view
	//m_Window.setView(m_BGMainView);

	// Draw the background
	//m_Window.draw(m_BackgroundSprite);
		
	// Switch to m_MainView
	m_Window.setView(m_MainView);

	// Draw the Level
	m_Window.draw(m_BSM.getVA(), &m_TextureTiles);

	//Draw selector
	m_Window.draw(m_BSM.getSelectorShape());

	// Draw the HUD
	// Switch to m_HudView
	//m_Window.setView(m_HudView);

	// Show everything we have just drawn
	m_Window.display();
}