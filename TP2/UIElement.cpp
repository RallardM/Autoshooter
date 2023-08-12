#include "UIElement.h"

UIElement::UIElement(Color color, Vector2 size, Vector2 offset)
{
	m_color = color;
	m_size = size;
	m_offset = offset;
}

void UIElement::OnStart()
{
	GameObject::OnStart();
}

void UIElement::FollowPosition(Vector2 newPosition)
{
	m_position = { newPosition.x + m_offset.x, newPosition.y + m_offset.y };
}


void UIElement::Update()
{
}

void UIElement::Render()
{
	DrawRectangleV(m_position, m_size, m_color);
}

