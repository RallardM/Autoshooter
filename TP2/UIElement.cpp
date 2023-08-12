#include "UIElement.h"
#include <iostream>
#include "Game.h"

UIElement::UIElement(GameObject* targetEntity, EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value)
{
	m_targetEntity = targetEntity;
	m_UIType = uitype;
	m_color = color;
	m_size = size;
	m_offset = offset;
	m_value = value;
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

	// Reset everything before m_isActive = false; in GameObject::Reset();
	GameObject::Reset();
}

void UIElement::Update(float _deltatime)
{
	switch (m_UIType)
	{
	case EUIElementType::PROGRESS_BAR:
		UpdateProgressBar();
		break;

	case EUIElementType::REGRESS_BAR:
		m_value = Game::GetInstance()->GetPlayerExperience();
		break;

	case EUIElementType::COUNT:
	default:
		std::cout << "UIElement::Render() : wrong UIElement type" << std::endl;
		m_value = Game::GetInstance()->GetPlayerExperience();
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
		DrawRectangleV(m_position, m_size, m_color);
		break;

	case EUIElementType::COUNT:
	default:
		std::cout << "UIElement::Render() : wrong UIElement type" << std::endl;
		DrawRectangleV(m_position, m_size, m_color);
		break;
	}
}



void UIElement::RenderProgressBar()
{
	if (m_value == 0.0f)
	{
		return;
	}

	DrawRectangleV(m_position, m_size, m_color);
}

void UIElement::UpdateProgressBar()
{
	m_value = Game::GetInstance()->GetPlayerExperience();
	
	// 32.0f  = 100% of the bar
	m_size.x = (m_value * 32.0f) / 100;
}

void UIElement::UpdateRegressBar()
{
	m_value = Game::GetInstance()->GetEntityHealth(m_targetEntity);

	// 32.0f  = 100% of the bar
	m_size.x = (m_value * 32.0f) / 100;
}