#pragma once
#include "Includes.h"

class SquareObject
{
	glm::u16vec2 m_Position;
	SDL_Renderer* m_Renderer;
	Uint8 m_Size;

public:
	SquareObject(glm::u16vec2 position, Uint8 size, SDL_Renderer* renderer);
	void Render();

	glm::u16vec2 GetPosition() { return m_Position; }
	void SetPosition(glm::u16vec2 position) { m_Position = position; }

	bool Collides(SquareObject squareObject);
};

