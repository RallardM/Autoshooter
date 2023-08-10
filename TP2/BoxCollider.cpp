#include <iostream>
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	std::cout << "BoxCollider default constructor" << std::endl;
	// Dimension
	int m_width = 0;
	int m_height = 0;

	// BoxCollider
	float m_left = 0.0f;
	float m_top = 0.0f;
	float m_right = 0.0f;
	float m_bottom = 0.0f;
}

BoxCollider::BoxCollider(const float& x, const float& y, const float& width, const float& height)
{
	std::cout << "BoxCollider constructor" << std::endl;
	// Dimension
	m_width = width;
	m_height = height;

	// Body
	m_left = x - (m_width * 0.5f);
	m_top = y - (m_height * 0.5f);
	m_right = m_left + m_width;
	m_bottom = m_top + m_height;
}

// TODO Remi : Vérifier code ajouté par Maurice:
//BoxCollider::BoxCollider(const BoxCollider& otherBoxCollider)
//	: m_width(otherBoxCollider.m_width), m_height(otherBoxCollider.m_height),
//	m_left(otherBoxCollider.m_left), m_top(otherBoxCollider.m_top), m_right(otherBoxCollider.m_right),
//	m_bottom(otherBoxCollider.m_bottom)
//{
//
//}
//
//BoxCollider::~BoxCollider()
//{}
//
//void BoxCollider::Update(float& x, float& y)
//{
//	m_left = std::floorf(x - (m_width * 0.5f));
//	m_top = std::floorf(y - (m_height * 0.5f));
//	m_right = m_left + m_width;
//	m_bottom = m_top + m_height;
//}
//
//bool BoxCollider::Collide(BoxCollider& boxCollider)
//{
//	if (
//		m_left <= boxCollider.m_right &&
//		m_right >= boxCollider.m_left &&
//		m_top <= boxCollider.m_bottom &&
//		m_bottom >= boxCollider.m_top
//		)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}