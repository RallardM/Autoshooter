#include <iostream>
#include <string>

#include "UIElement.h"
#include "GameObjectPool.h"
#include "Mathutils.h"

unsigned short int UIElement::s_id = 0;

UIElement::UIElement(Entity* targetEntity, EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value)
{
	m_id = s_id++;
	std::cout << "First UIElement constructor called. ID = " << m_id << std::endl;

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
	m_id = s_id++;
	std::cout << "Second UIElement constructor called. ID = " << m_id << std::endl;

	m_targetEntity = targetEntity;
	m_UIType = uitype;
	m_color = color;
	m_fontSize = size;
	m_size = { 0.0f, 0.0f };
	m_offset = offset;
	m_intValue = value;
	m_floatValue = 0.0f;
}

UIElement::~UIElement()
{
	std::cout << "UIElement destructor called. ID = " << m_id << std::endl;
}

void UIElement::OnStart()
{
	GameObject::OnStart();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void UIElement::FollowPosition(const Vector2& newPosition)
{
	m_position = { newPosition.x + m_offset.x, newPosition.y + m_offset.y };
}

void UIElement::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void UIElement::Update(const float& _deltatime)
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
		m_intValue = GameObjectPool::GetInstance()->GetPlayerTotalExperience();
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
	m_floatValue = GameObjectPool::GetInstance()->GetPlayerExperience();
	
	// 32.0f  = 100% of the bar
	m_size.x = (m_floatValue * PLAYER_HEALTH_BAR_SIZE.x) * HUNDREDTH; // TODO Remi: change the player size and xp/health bar to 40 
																	  // Warning, this section is for both the Enemy and Player health bar
																	  // PLAYER_HEALTH_BAR_SIZE.x would have to be changed wor a member variable
																	  // to fit both the Enemy health bar width at 32.f and player's at 40.f																
}

void UIElement::UpdateRegressBar()
{
	// Keep its size full it there is a second bar to regress
	if (m_hasASecondBarToRegressBefore)
	{
		m_size.x = PLAYER_HEALTH_BAR_SIZE.x; // TODO Remi : change the player size and xp / health bar to 40
						  // Warning, this section is for both the Enemy and Player health bar
						  // PLAYER_HEALTH_BAR_SIZE.x would have to be changed wor a member variable
						  // to fit both the Enemy health bar width at 32.f and player's at 40.f
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

	// 32.0f  = 100% of the bar
	m_size.x = (m_floatValue * PLAYER_HEALTH_BAR_SIZE.x) * HUNDREDTH; // TODO Remi: change the player size and xp/health bar to 40 
																	  // Warning, this section is for both the Enemy and Player health bar
																	  // PLAYER_HEALTH_BAR_SIZE.x would have to be changed wor a member variable
																	  // to fit both the Enemy health bar width at 32.f and player's at 40.f
}