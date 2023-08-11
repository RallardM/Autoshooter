#pragma once

#include "Projectile.h"

// TODO Remi : Code initial, vérifier à retirer après transfère:
//struct SWeaponData
//{
//public:
//	float m_attackRate = 1.0f;
//	SHandGunProjectileData m_projectileInfos;
//};
//
//class Weapon: public GameObject
//{
//private:
//	float m_currentAttackTimer = 0.0f;
//	SWeaponData m_weaponInfos;
//	Vector2 m_size = { 5.0f, 5.0f };
//
//private:
//	void Fire();
//public:
//	// Inherited via GameObject
//	virtual void OnStart() override;
//	virtual void Update() override;
//	virtual void Render() override;
//};
//

class Weapon : public GameObject
{
	friend class Player;

public:

	//FireMode m_fireMode = FireMode::Auto;


public:

private:
	// TODO Remi : Vérifier code ajouté par Maurice:
	//Weapon();
	//Weapon(const float& x, const float& y);
	//Weapon(const float&, const float&, const FireMode&, const bool&);
	//virtual ~Weapon();

	//virtual void Load() = 0;
	//virtual void Reload() = 0;
	virtual void Fire() = 0;
	//virtual void ReloadProjectile(Projectile*) = 0;
	//virtual void FireProjectile(Projectile*) = 0;
	virtual void OnStart() = 0;
	virtual void Update() = 0;
	void FollowPosition(Vector2 newPosition);
	virtual void Render() = 0;
};

enum class EWeaponType : unsigned short int
{
	HAND_GUN,
	EXPLOSIVE_GUN,
	LAZER_GUN,
};