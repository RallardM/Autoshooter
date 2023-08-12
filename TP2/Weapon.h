#pragma once

#include "GameObject.h"
#include "Projectile.h"

class Weapon : public GameObject
{
	friend class Player;
public:

private:
	virtual void Fire() = 0;
	virtual void OnStart() = 0;
	virtual void Update() = 0;
	void FollowPosition(Vector2 newPosition); // TODO make pure virtual
	
	virtual void Render() = 0;

protected:
	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;
};