#pragma once

class BoxCollider
{

public:
	BoxCollider();
	BoxCollider(const float& x, const float& y, const int& width, const int& height);
	BoxCollider(const BoxCollider& otherBoxCollider);
	~BoxCollider();

public:
	// Dimension
	int m_width = 0;
	int m_height = 0;


	// BoxCollider
	float m_left = 0.0f;
	float m_top = 0.0f;
	float m_right = 0.0f;
	float m_bottom = 0.0f;

public:
	void Update(float& x, float&y);
	bool Collide(BoxCollider& boxCollider);
};