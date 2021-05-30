#include "Player.h"

Player::Player(glm::u16vec2 position, SDL_Renderer* renderer)
{
	m_Alive = true;
	m_EatenApples = 0;
	m_Renderer = renderer;
	// Initially going to the right
	m_Velocity = glm::u16vec2(1, 0);
	m_Nodes = std::vector<SquareObject*>();
	m_Nodes.push_back(new SquareObject(position, 10, renderer));
}

void Player::Update()
{
	for (SquareObject* node : m_Nodes)
	{
		node->SetPosition(node->GetPosition() + m_Velocity);
	}
	for (size_t i = 0; i < m_Nodes.size(); i++)
	{
		SquareObject* node = m_Nodes.at(i);
		glm::u16vec2 position = node->GetPosition();

		if (i == 0)
		{
			node->SetPosition(position + m_Velocity);
			continue;
		}
		// if not first node, check forward node to know next position
		glm::u16vec2 forwardNodePosition = m_Nodes.at(i - 1)->GetPosition();

		if (m_Velocity == glm::u16vec2(1, 0))
		{
			position.x = forwardNodePosition.x - 15;
			position.y = forwardNodePosition.y;
		}
		else if (m_Velocity == glm::u16vec2(-1, 0))
		{
			position.x = forwardNodePosition.x + 15;
			position.y = forwardNodePosition.y;
		}
		else if (m_Velocity == glm::u16vec2(0, 1))
		{
			position.x = forwardNodePosition.x;
			position.y = forwardNodePosition.y - 15;
		}
		else if (m_Velocity == glm::u16vec2(0, -1))
		{
			position.x = forwardNodePosition.x;
			position.y = forwardNodePosition.y + 15;
		}
		node->SetPosition(position);

	}
}

void Player::Render()
{
	for (SquareObject* node : m_Nodes)
	{
		node->Render();
	}
}
