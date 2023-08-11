#pragma once

class BoxCollider
{

public:
	BoxCollider();
	BoxCollider(const float& x, const float& y, const float& width, const float& height);
	// TODO Remi : Vérifier code ajouté par Maurice:
	//BoxCollider(const BoxCollider& otherBoxCollider);
	//~BoxCollider();

public:
	float m_left = 0.0f;
	float m_top = 0.0f;

private:
	// Dimension
	float m_width = 0;
	float m_height = 0;


	// BoxCollider
	//float m_left = 0.0f;
	//float m_top = 0.0f;
	float m_right = 0.0f;
	float m_bottom = 0.0f;

public:
	// TODO Remi : Vérifier code ajouté par Maurice:
	void Update(float& x, float& y);
	//bool Collide(BoxCollider& boxCollider);
};