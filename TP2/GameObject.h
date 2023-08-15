#pragma once
#include "raylib.h"
#include "Enumerations.h"

/**
 * @brief Abstract class use to represent object handle by the engine
*/
class GameObject
{
	friend class Game;// To all Game class to access GameObject class encapsulated member or method

protected:
	Vector2 m_position = { 0.0f, 0.0f };
	bool m_isActive = false;
	/**
	 * @brief Abstract method that return game object position
	 * @return Vector2 game object position 
	*/
	virtual const Vector2& GetPosition() const = 0;
	/**
	 * @brief Abstract Method that return the game object type
	 * @return EnumGameObjectType type of game object
	*/
	virtual const EGameObjectType GetGameObjectType() const = 0;
	
public:
	/**
	 * @brief Abstract Method call when the game object its created 
	*/
	virtual void OnStart() = 0;
	/**
	 * @brief Abstract method call every frame of gameloop
	 * @param deltatime Represent the time elapsed between two frame
	*/
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
	/**
	 * @brief Abstract method call to update current state of the game object
	 * @return Active state of the game object
	*/
	virtual const bool IsActive() const = 0;
	/**
	 * @brief Abstract method call to reinitialize the game object attributes
	*/
	virtual void Reset() = 0;

};