#pragma once
#include <list>
#include "GameObject.h"



class Player : public GameObject
{
	
public:
	Player();
	Player(float& x, float& y, int& width, int& height);

public:
	float m_oldLeft;
	float m_oldTop;
	float m_oldRight;
	float m_oldBottom;

	Color m_color = { 0, 255, 0, 255 };
public:
	//std::list<Weapon*> m_weapons;

	// Inherited via Agent
	void OnStart() override;
	void Update(float deltatime) override;
	void Render() override;
	bool Collide(GameObject& gameObject);

};