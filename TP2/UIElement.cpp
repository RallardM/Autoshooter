#include "UIElement.h"
#include <iostream>
#include <string>
#include "Game.h"

UIElement::~UIElement()
{

}

void UIElement::Cleanup()
{
	Reset();
	Game::GetInstance()->UnregisterGameObject(this);
}

// TODO: to avoid Entities from deleting themselves 
// while deleting their ui elements send an entity type
// instead of sending the pointer to the entity
//UIElement::UIElement(Entity* targetEntity, EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value)
UIElement::UIElement(unsigned short int gameObjectId, EUIElementType uitype)
{
	//m_targetEntity = targetEntity;
	m_uiType = uitype;
	//m_color = color;
	//m_fontSize = 0;
	//m_size = size;
	//m_offset = offset;
	//m_floatValue = value;
	m_targetObjectId = gameObjectId;
	GameObject* gameObject = Game::GetInstance()->GetObjectFromId(gameObjectId);
	if (gameObject == nullptr)
	{
		std::cout << "UIElement::UIElement() : gameObject is nullptr" << std::endl;
		return;
	}

	if (gameObject->GetGameObjectType() == EGameObjectType::PLAYER)
	{
		AssignPlayerUiValues();
	}
	else if (gameObject->GetGameObjectType() == EGameObjectType::ENEMY)
	{
		AssignEnemyUiValues();
	}
	else
	{
		std::cout << "UIElement::UIElement() : wrong gameobject type" << std::endl;
	}
}

// TODO: to avoid Entities from deleting themselves 
// while deleting their ui elements send an entity type
// instead of sending the pointer to the entity
//UIElement::UIElement(Entity* targetEntity, EUIElementType uitype, Color color, int size, Vector2 offset, unsigned short int value)
//{
//	m_targetEntity = targetEntity;
//	m_uiType = uitype;
//	m_color = color;
//	m_fontSize = size;
//	m_size = { 0.0f, 0.0f };
//	m_offset = offset;
//	m_intValue = value;
//	m_floatValue = 0.0f;
//}

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
	switch (m_uiType)
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
	switch (m_uiType)
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
	if (m_hasASecondBarToRegressBefore)
	{
		m_size.x = 32.0f;
		return;
	}

	GameObject* gameObject = Game::GetInstance()->GetObjectFromId(m_targetObjectId);
	if (gameObject == nullptr)
	{
		std::cout << "UIElement::UpdateRegressBar() : gameObject is nullptr" << std::endl;
		return;
	}
	
	if (gameObject->GetGameObjectType() != EGameObjectType::PLAYER && gameObject->GetGameObjectType() != EGameObjectType::ENEMY)
	{
		return;
	}

	// Dynamic cast
	Entity* entity = dynamic_cast<Player*>(gameObject);
	if (entity == nullptr)
	{
		return;
	}

	if (entity->GetHealth() > entity->GetMaxHealth())
	{
		m_floatValue = (float)(entity->GetHealth() - entity->GetMaxHealth());
	}
	else
	{
		m_floatValue = entity->GetHealth();
	}

	// 32.0f  = 100% of the bar
	m_size.x = (m_floatValue * 32.0f) / 100;
}

void UIElement::AssignPlayerUiValues()
{
	if (m_uiType == EUIElementType::PROGRESS_BAR)
	{
		// Experience bar
		m_size = { 32.0f, 3.0f }; // Size of the bar
		m_offset = { 0.0f, -3.0f }; // Offset from the enemy ui square
		m_color = GREEN;
		m_floatValue = 100.0f; // Health points
	}
	else if (m_uiType == EUIElementType::REGRESS_BAR)
	{
		if (m_hasASecondBarToRegressBefore == false)
		{
			m_offset = { 0.0f, 33.0f }; // Offset from the enemy ui square
			m_floatValue = 100.0f; // Health points
			m_size = { 32.0f, 3.0f }; // Size of the bar
		}
		else
		{
			m_offset = { 0.0f, 37.0f }; // Offset from the enemy ui square
			GameObject* gameObject = Game::GetInstance()->GetObjectFromId(m_gameObjectId);
			Player* player = dynamic_cast<Player*>(gameObject);
			float extraHealth = (float)player->GetHealth() - (float)player->GetMaxHealth();
			extraHealth = (extraHealth * 32.0f) / 100;
			m_floatValue = 100.0f; // Health points
			m_size = { extraHealth, 3.0f }; // Size of the bar
		}

		// Health bar
		m_size = { 32.0f, 3.0f }; // Size of the bar
		m_color = RED;
	}
	if (m_uiType == EUIElementType::TEXT)
	{
		// Experience text
		m_fontSize = 15;
		m_offset = { 3.0f, 4.0f };
		m_color = GREEN;
		m_intValue = 0; // Experience points starts at 0
	}
}

void UIElement::AssignEnemyUiValues()
{
	// Health bar
	m_size = { 32.0f, 3.0f }; // Size of the bar
	m_offset = { 0.0f, 33.0f }; // Offset from the enemy ui square
	m_color = RED;
	m_floatValue = 100.0f; // Health points
}
