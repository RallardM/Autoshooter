#pragma once

/*
Toutes les classes de votre jeu ayant une repr�sentation physique
devraient h�riter de la classe Agent.

En ayant cette classe comme parent, vous vous assurez d'appeller
Update() sur tous vos objets pr�sents dans la sc�ne,
Agent::OnStart() doit ABSOLUMENT �tre appel� �galement.

C'est de cette fa�on qu'on enregistre nos �l�ments de jeu.
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

