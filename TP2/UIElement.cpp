#include "UIElement.h"
#include <iostream>
#include <string>
#include "Game.h"

UIElement::UIElement(Entity* targetEntity, EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value)
{
	m_targetEntity = targetEntity;
	m_UIType = uitype;
	m_color = color;
	m_fontSize = 0;
	m_size = size;
	m_offset = offset;
	m_floatValue = value;
}

UIElement::UIElement(Entity* targetEntity, EUIElementType uitype, Color color, int size, Vector2 offset, unsigned short int value)
{
	m_targetEntity = targetEntity;
	m_UIType = uitype;
	m_color = color;
	m_fontSize = size;
	m_size = { 0.0f, 0.0f };
	m_offset = offset;
	m_intValue = value;
	m_floatValue = 0.0f;
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
	
	// 32.0f  = 100% of the bar
	m_size.x = (m_floatValue * 32.0f) / 100;
}

void UIElement::UpdateRegressBar()
{
	//m_floatValue = Game::GetInstance()->GetEntityHealth(m_targetEntity);
	m_floatValue = m_targetEntity->GetHealth();

	// 32.0f  = 100% of the bar
	m_size.x = (m_floatValue * 32.0f) / 100;
}