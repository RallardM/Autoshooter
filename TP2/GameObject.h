#pragma once
#include "Globals.h"
#include "Game.h"
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
	//friend class Game;
public:
	GameObject();
	GameObject(const float&, const float&);
	GameObject(const float&, const float&, const bool&);
	virtual ~GameObject();
public:

	// Position
	Vector2 m_position = { 0.0f, 0.0f};
	bool m_isDie = false;
	
public:
	virtual void OnStart() = 0; 
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
};

