#include "pch.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float elapsedTime)
{
	m_BSM.update(elapsedTime);

	viewFollowSelector();
}