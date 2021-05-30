#include "SquareObject.h"

SquareObject::SquareObject(glm::i16vec2 position, Uint8 size, SDL_Renderer* renderer)
{
	m_Position = position;
	m_Renderer = renderer;
	m_Size = size;
}

void SquareObject::Render()
{
	SDL_Rect fillRect = { m_Position.x, m_Position.y, 10, 10 };
	SDL_RenderFillRect(m_Renderer, &fillRect);
}

bool SquareObject::Collides(SquareObject squareObject)
{
	glm::i16vec2 squareObjectPosition = squareObject.m_Position;
	Uint8 squareObjectSize = squareObject.m_Size;

	if (m_Position.x < squareObjectPosition.x + squareObjectSize &&
		m_Position.x + m_Size > squareObjectPosition.x &&
		m_Position.y < squareObjectPosition.y + squareObjectSize &&
		m_Position.y + m_Size > squareObjectPosition.y) {
		return true;
	}
	return false;
}
