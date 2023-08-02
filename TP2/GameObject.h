#pragma once
#include "Globals.h"

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
	float m_speed;

	// Dimension
	int m_width;
	int m_height;


	// BoxCollider
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;
	float m_isCollide;
	
public:
	virtual void OnStart() = 0; 
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
};

