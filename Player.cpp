#include "Player.h"

static int i = 1;

Player::Player(glm::i16vec2 position, SDL_Renderer* renderer)
{
	m_Alive = true;
	m_EatenApples = 0;
	m_Renderer = renderer;
	// Initially going to the right
	m_Velocity = glm::i16vec2(1, 0);
	m_Nodes = std::vector<SquareObject*>();
	m_Nodes.push_back(new SquareObject(position, 10, renderer));
}

void Player::Update()
{
	if (i == m_Nodes.size()) i = 1;
	m_Nodes.at(0)->SetPosition(m_Nodes.at(0)->GetPosition() + m_Velocity);

	if (m_Nodes.size() == 1) return;

	SquareObject* node = m_Nodes.at(i);
	glm::i16vec2 position = node->GetPosition();

	glm::i16vec2 forwardNodePosition = m_Nodes.at(i - 1)->GetPosition();

	if (m_Velocity == glm::i16vec2(1, 0))
	{
		position.x = forwardNodePosition.x - 15;
		position.y = forwardNodePosition.y;
	}
	else if (m_Velocity == glm::i16vec2(-1, 0))
	{
		position.x = forwardNodePosition.x + 15;
		position.y = forwardNodePosition.y;
	}
	else if (m_Velocity == glm::i16vec2(0, 1))
	{
		position.x = forwardNodePosition.x;
		position.y = forwardNodePosition.y - 15;
	}
	else if (m_Velocity == glm::i16vec2(0, -1))
	{
		position.x = forwardNodePosition.x;
		position.y = forwardNodePosition.y + 15;
	}
	node->SetPosition(position);
	i++;

	/*for (size_t i = 0; i < m_Nodes.size(); i++)
	{
		SquareObject* node = m_Nodes.at(i);
		glm::i16vec2 position = node->GetPosition();

		if (i == 0)
		{
			node->SetPosition(position + m_Velocity);
			continue;
		}
		// if not first node, check forward node to know next position
		glm::i16vec2 forwardNodePosition = m_Nodes.at(i - 1)->GetPosition();

		if (m_Velocity == glm::i16vec2(1, 0))
		{
			position.x = forwardNodePosition.x - 15;
			position.y = forwardNodePosition.y;
		}
		else if (m_Velocity == glm::i16vec2(-1, 0))
		{
			position.x = forwardNodePosition.x + 15;
			position.y = forwardNodePosition.y;
		}
		else if (m_Velocity == glm::i16vec2(0, 1))
		{
			position.x = forwardNodePosition.x;
			position.y = forwardNodePosition.y - 15;
		}
		else if (m_Velocity == glm::i16vec2(0, -1))
		{
			position.x = forwardNodePosition.x;
			position.y = forwardNodePosition.y + 15;
		}
		node->SetPosition(position);

	}*/
}

void Player::Render()
{
	for (SquareObject* node : m_Nodes)
	{
		node->Render();
	}
}
