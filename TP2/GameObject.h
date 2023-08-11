#pragma once
#include "raylib.h"
#include "Enumerations.h"

/*
Toutes les classes de votre jeu ayant une représentation physique
devraient hériter de la classe GameObject.

En ayant cette classe comme parent, vous vous assurez d'appeller
Update() sur tous vos objets présents dans la scène,
GameObject::OnStart() doit ABSOLUMENT être appelé également.

C'est de cette façon qu'on enregistre nos éléments de jeu.
*/

class GameObject
{
	friend class Game;

protected:
	// TODO Remi : Vérifier avec Maurice vector au lieu de 2 float:
	//float m_posX = 0.0f;
	//float m_posY = 0.0f;
	
	Vector2 m_position = { 0.0f, 0.0f };
	//EGameObjectType m_gameObjectType = EGameObjectType::COUNT;
	
public:
	virtual void OnStart() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};

