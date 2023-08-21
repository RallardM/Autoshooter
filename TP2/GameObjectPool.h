#pragma once
#include <list>
#include <vector>
#include <memory>

#include "GameObject.h"
#include "Player.h"
#include "Weapon.h"
#include "ExperienceOrb.h"
#include "HandGun.h"
#include "ExplosiveGun.h"
#include "LaserGun.h"

class GameObjectPool
{
	friend class Projectile;
	friend class CollisionManager;
	friend class GameObject;
	friend class Player;
	friend class Enemy;
	friend class ExperienceOrb;
	friend class Game;
	friend class CameraManager;
	friend class UIElement;
	friend class HandGun;
	friend class ExplosiveGun;
	friend class LaserGun;


public:
	~GameObjectPool();
	static GameObjectPool* GetInstance();
	void InitializeGameObjects();
	void CleanUpGame();

private:
	static GameObjectPool* _Instance;

	std::vector<GameObject*> m_allGameObjectsPool;
	std::vector<Weapon*> m_allWeaponsPool;
	std::vector<Entity*> m_allEntitiesPool;

	std::vector<UIElement*> m_uiElementsPool;
	std::vector<Enemy*> m_enemiesPool;
	std::vector<HandGun*> m_handGunsPool;
	std::vector<ExplosiveGun*> m_explosiveGunsPool;
	std::vector<LaserGun*> m_laserGunsPool;
	std::vector<Projectile*> m_projectilesPool;
	std::vector<ExperienceOrb*> m_experienceOrbsPool;


	Camera2D* m_camera = nullptr;
	Player* m_player = nullptr;
	SWeaponData m_emptyWeaponInfos;
	const unsigned short int UI_ELEMENTS_POOL_SIZE = 13; // Max 65535 // Enemies + Player's 3 UIELEMENT elements
	const unsigned short int EXPERIENCE_ORBS_POOL_SIZE = 20; // Max 65535 // At lest the double of ennemies
	const unsigned short int ENEMIES_POOL_SIZE = 10; // Max 65535
	const unsigned short int HANDGUNS_POOL_SIZE = 10; // Max 65535
	const unsigned short int EXPLOSIVEGUNS_POOL_SIZE = 10; // Max 65535
	const unsigned short int LASERGUNS_POOL_SIZE = 10; // Max 65535
	const unsigned short int PROJECTILES_POOL_SIZE = 1500; // Max 65535

private:
	GameObjectPool(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	const EGameObjectType GetGameObjectType(GameObject* gameObject) const;
	const Enemy* GetClosestEnemy(const Vector2& position) const;
	const void UpdateGameObjects(const float& deltatime) const;
	const unsigned short int GetActiveObjectCountFromList(const EGameObjectType& type) const;
	const void SetEmptyProjectileInfos(const SProjectileData& projectileInfos) { m_emptyWeaponInfos.m_projectileInfos = projectileInfos; }

	const void RenderGameObjects() const;
	const void UpdateEnemySpawner() const;
	const void TakeProjectileFromPool(const SProjectileData& projectileData) const;
	const void TakeHandGunFromPool() const; // TODO Remi : Make into one weapon method
	const void TakeExplosiveGunFromPool() const;// TODO Remi : Make into one weapon method
	const void TakeLaserGunFromPool() const;// TODO Remi : Make into one weapon method
	const void TakeUIElementFromPool(std::shared_ptr<SUIElementData> uiData) const;
	const void TakeExperienceOrbFromPool(const Vector2 position) const;

	// vector fields
	const std::vector<Weapon*> GetActiveWeapons() const;
	const std::vector<Projectile*> GetActiveProjectiles() const;
	const std::vector<Enemy*> GetActiveEnemies() const;

	// Player getters // TODO Extract experience to its own class
	const Player* GetPlayer() const { return m_player; }
	const Vector2 GetPlayerPosition() const { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() const { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() const { return m_player->m_totalExperience; }
	const void AddPlayerExperience(unsigned short int experience) const { m_player->m_experience += experience; m_player->m_totalExperience += experience; }
	UIElement* GetEnemyHealthBar(const unsigned short int& id) const;
	UIElement* GetPlayerPrimaryHealthBar(const unsigned short int& id) const;
	UIElement* GetPlayerSecondaryHealthBar(const unsigned short int& id) const;
	UIElement* GetPlayerExperienceBar(const unsigned short int& id) const;
	Entity* GetEntityFromID(const unsigned short int& id) const;

	const void RemoveAllGameObjects();
};

