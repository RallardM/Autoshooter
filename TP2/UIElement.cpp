#include <iostream>
#include <string>

#include "UIElement.h"
#include "GameObjectPool.h"
#include "Mathutils.h"

unsigned short int UIElement::s_id = 0;

UIElement::UIElement(SUIElementData& uiData) : m_uiData(uiData)
{
	m_id = s_id++;
}

UIElement::~UIElement()
{
	std::cout << "UIElement destructor called. ID = " << m_id << std::endl;
}



void UIElement::OnStart()
{
	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void UIElement::FollowPosition(const Vector2& newPosition)
{
	m_position = { newPosition.x + m_uiData.OFFSET.x, newPosition.y + m_uiData.OFFSET.y };
}

void UIElement::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void UIElement::Update(const float& _deltatime)
{
	switch (static_cast<EUIElementType>(m_uiData.UIELEMENT_TYPE))
	{
	case EUIElementType::PROGRESS_BAR:
		UpdateProgressBar();
		break;

	case EUIElementType::REGRESS_BAR:
		UpdateRegressBar();
		break;

	case EUIElementType::TEXT:
		m_uiData.INT_VALUE = GameObjectPool::GetInstance()->GetPlayerTotalExperience();
		break;

	case EUIElementType::COUNT:
	default:
		std::cout << "UIElement::Render() : wrong UIElement type" << std::endl;
		break;
	}
}

void UIElement::Render()
{
	switch (static_cast<EUIElementType>(m_uiData.UIELEMENT_TYPE))
	{
	case EUIElementType::PROGRESS_BAR:
		RenderProgressBar();
		break;
	
	case EUIElementType::REGRESS_BAR:
		RenderRegressBar();
		break;

	case EUIElementType::TEXT:
		DrawText(std::to_string(m_uiData.INT_VALUE).c_str(), (int)m_position.x, (int)m_position.y, m_uiData.FONT_SIZE, m_uiData.COLOR);
		break;

	case EUIElementType::COUNT:
	default:
		std::cout << "UIElement::Render() : wrong UIElement type" << std::endl;
		break;
	}
}

void UIElement::RenderProgressBar()
{
	if (m_uiData.FLOAT_VALUE == 0.0f)
	{
		return;
	}

	DrawRectangleV(m_position, m_uiData.BAR_SIZE, m_uiData.COLOR);
}

void UIElement::RenderRegressBar()
{
	if (m_uiData.FLOAT_VALUE == 0.0f)
	{
		return;
	}

	DrawRectangleV(m_position, m_uiData.BAR_SIZE, m_uiData.COLOR);
}

void UIElement::UpdateProgressBar()
{
	m_uiData.FLOAT_VALUE = GameObjectPool::GetInstance()->GetPlayerExperience();
	
	// 32.0f  = 100% of the bar
	m_uiData.BAR_SIZE.x = (m_uiData.FLOAT_VALUE * PLAYER_HEALTH_BAR_SIZE.x) * HUNDREDTH; // TODO Remi: change the player size and xp/health bar to 40 
																	  // Warning, this section is for both the Enemy and Player health bar
																	  // PLAYER_HEALTH_BAR_SIZE.x would have to be changed wor a member variable
																	  // to fit both the Enemy health bar width at 32.f and player's at 40.f																
}

void UIElement::UpdateRegressBar()
{
	// Keep its size full it there is a second bar to regress
	if (m_uiData.HAS_SECONDARY_BAR)
	{
		m_uiData.BAR_SIZE.x = PLAYER_HEALTH_BAR_SIZE.x; // TODO Remi : change the player size and xp / health bar to 40
						  // Warning, this section is for both the Enemy and Player health bar
						  // PLAYER_HEALTH_BAR_SIZE.x would have to be changed wor a member variable
						  // to fit both the Enemy health bar width at 32.f and player's at 40.f
		return;
	}

	if (m_uiData.TARGET->GetHealth() > m_uiData.TARGET->GetMaxHealth())
	{
		m_uiData.FLOAT_VALUE = (float)(m_uiData.TARGET->GetHealth() - m_uiData.TARGET->GetMaxHealth());
	}
	else
	{
		m_uiData.FLOAT_VALUE = m_uiData.TARGET->GetHealth();
	}

	// 32.0f  = 100% of the bar
	m_uiData.BAR_SIZE.x = (m_uiData.FLOAT_VALUE * PLAYER_HEALTH_BAR_SIZE.x) * HUNDREDTH; // TODO Remi: change the player size and xp/health bar to 40 
																	  // Warning, this section is for both the Enemy and Player health bar
																	  // PLAYER_HEALTH_BAR_SIZE.x would have to be changed wor a member variable
																	  // to fit both the Enemy health bar width at 32.f and player's at 40.f
}