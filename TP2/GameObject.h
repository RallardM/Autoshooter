#pragma once
#include "Globals.h"
#include <iostream>

/*
Toutes les classes de votre jeu ayant une repr�sentation physique
devraient h�riter de la classe Agent.

En ayant cette classe comme parent, vous vous assurez d'appeller
Update() sur tous vos objets pr�sents dans la sc�ne,
Agent::OnStart() doit ABSOLUMENT �tre appel� �galement.

C'est de cette fa�on qu'on enregistre nos �l�ments de jeu.
*/

class GameObject
{
	friend class Game;

public:

	// Position
	Vector2 m_position;
	Vector2 m_direction;
	float m_speed = PLAYER_SPEED;

	// Dimension
	int m_width = PLAYER_WIDTH;
	int m_height = PLAYER_HEIGHT;


	// BoxCollider
	float m_left = m_position.x - (m_width * 0.5f);
	float m_top = m_position.y - (m_height * 0.5f);
	float m_right = m_left + m_width;
	float m_bottom = m_top + m_height;
	float m_isCollide = false;
	
public:
	virtual void OnStart() = 0; 
	virtual void HandleInput() = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
};

