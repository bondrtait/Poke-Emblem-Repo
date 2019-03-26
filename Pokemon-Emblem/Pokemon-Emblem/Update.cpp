#include "pch.h"
#include "Engine.h"

using namespace sf;

void Engine::update()
{
	m_BSM.update();

	viewFollowSelector();
}