#pragma once

/*
Toutes les classes de votre jeu ayant une représentation physique
devraient hériter de la classe Agent.

En ayant cette classe comme parent, vous vous assurez d'appeller
Update() sur tous vos objets présents dans la scène,
Agent::OnStart() doit ABSOLUMENT être appelé également.

C'est de cette façon qu'on enregistre nos éléments de jeu.
*/

class Agent
{
	friend class Game;

protected:
	float m_posX = 0.0f;
	float m_posY = 0.0f;
	
public:
	virtual void OnStart();
	virtual void Update() = 0;
};

