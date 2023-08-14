#include "UIElement.h"
#include <iostream>
#include <string>
#include "Game.h"

UIElement::UIElement(Entity* targetEntity, EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value) // TODO : diminush the number of arguments like in projectile
{
	// Bar UI
	m_targetEntity = targetEntity;
	m_UIType = uitype;
	m_color = color;
	m_size = size;
	m_width = size.x;
	m_offset = offset;
	m_floatValue = value;
}

UIElement::UIElement(Entity* targetEntity, EUIElementType uitype, Color color, int size, Vector2 offset, unsigned short int value) // TODO : diminush the number of arguments like in projectile
{
	// Textual UI
	m_targetEntity = targetEntity;
	m_UIType = uitype;
	m_color = color;
	m_fontSize = size;
	m_offset = offset;
	m_intValue = value;
}

void UIElement::OnStart()
{
	GameObject::OnStart();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void UIElement::FollowPosition(Vector2 newPosition)
{
	m_position = { newPosition.x + m_offset.x, newPosition.y + m_offset.y };
}

void UIElement::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void UIElement::Update(float _deltatime)
{
	switch (m_UIType)
	{
	case EUIElementType::PROGRESS_BAR:
		UpdateProgressBar();
		break;

	case EUIElementType::REGRESS_BAR:
		UpdateRegressBar();
		break;

	case EUIElementType::TEXT:
		m_intValue = Game::GetInstance()->GetPlayerTotalExperience();
		break;

	case EUIElementType::COUNT:
	default:
		std::cout << "UIElement::Render() : wrong UIElement type" << std::endl;
		break;
	}
}

void UIElement::Render()
{
	switch (m_UIType)
	{
	case EUIElementType::PROGRESS_BAR:
		RenderProgressBar();
		break;
	
	case EUIElementType::REGRESS_BAR:
		RenderRegressBar();
		break;

	case EUIElementType::TEXT:
		DrawText(std::to_string(m_intValue).c_str(), (int)m_position.x, (int)m_position.y, m_fontSize, m_color);
		break;

	case EUIElementType::COUNT:
	default:
		std::cout << "UIElement::Render() : wrong UIElement type" << std::endl;
		break;
	}
}

void UIElement::RenderProgressBar()
{
	if (m_floatValue == 0.0f)
	{
		return;
	}

	DrawRectangleV(m_position, m_size, m_color);
}

void UIElement::RenderRegressBar()
{
	if (m_floatValue == 0.0f)
	{
		return;
	}

	DrawRectangleV(m_position, m_size, m_color);
}

void UIElement::UpdateProgressBar()
{
	m_floatValue = Game::GetInstance()->GetPlayerExperience();
	
	// 40.0f = 100% of the bar or 32.0f = 100% of the bar thus health*pixelsize/100
	m_size.x = (m_floatValue * m_width) / 100;
}

void UIElement::UpdateRegressBar()
{
	// Dynamic cast to player
	//Player* player = dynamic_cast<Player*>(m_targetEntity);
	if (m_targetEntity->GetGameObjectType() == EGameObjectType::PLAYER)
	{
		int a = 0;
	}

	if (m_hasASecondBarToRegressBefore)
	{
		m_size.x = 40.0f;
		return;
	}

	if (m_targetEntity->GetHealth() > m_targetEntity->GetMaxHealth())
	{
		m_floatValue = (float)(m_targetEntity->GetHealth() - m_targetEntity->GetMaxHealth());
	}
	else
	{
		m_floatValue = m_targetEntity->GetHealth();
	}

	// 40.0f = 100% of the bar or 32.0f = 100% of the bar thus health*pixelsize/100
	m_size.x = (m_floatValue * m_width) / 100;
}