#pragma once
#include <list>
#include <vector>

#include "GameObject.h"
#include "Player.h"
#include "Weapon.h"

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

private:
	static GameObjectPool* _Instance;
	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;
	Camera2D* m_camera = nullptr;
	Player* m_player = nullptr;
	SWeaponData m_emptyWeaponInfos;
	const unsigned short int UI_ELEMENTS_POOL_SIZE = 503; // Max 65535 // Enemies + Player's 3 UIELEMENT elements
	const unsigned short int ENEMIES_POOL_SIZE = 500; // Max 65535
	const unsigned short int HANDGUNS_POOL_SIZE = 10; // Max 65535
	const unsigned short int EXPLOSIVEGUNS_POOL_SIZE = 10; // Max 65535
	const unsigned short int LASERGUNS_POOL_SIZE = 10; // Max 65535
	const unsigned short int PROJECTILES_POOL_SIZE = 1500; // Max 65535
	
private:
	GameObjectPool(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }
	EGameObjectType GetGameObjectType(GameObject* gameObject);
	GameObject* GetClosestGameObject(const Vector2& position, const EGameObjectType& type);
	void UpdateGameObjects(const float& deltatime);
	unsigned short int GetActiveObjectCountFromList(const EGameObjectType& type);
	void SetEmptyProjectileInfos(const SProjectileData& projectileInfos) { m_emptyWeaponInfos.m_projectileInfos = projectileInfos; }
	
	void RenderGameObjects();
	void ResetAllObjects();
	void RemoveAllGameObjects();
	void UpdateEnemySpawner();
	void TakeProjectileFromPool(SProjectileData& projectileData);
	void TakeHandGunFromPool(); // TODO Remi : Make into one weapon method
	void TakeExplosiveGunFromPool();// TODO Remi : Make into one weapon method
	void TakeLaserGunFromPool();// TODO Remi : Make into one weapon method
	void TakeUIElementFromPool(SUIElementData& uiData);	void CleanUpGame();

	// Weapon field
	const std::list<Weapon*> GetActiveWeapons() const;

	// Player getters // TODO Extract experience to its own class
	Player* GetPlayer() { return m_player; }
	Vector2 GetPlayerPosition() { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() { return m_player->m_totalExperience; }
	void AddPlayerExperience(unsigned short int experience) { m_player->m_experience += experience; m_player->m_totalExperience += experience; }
	const bool GetPlayerHasSecondaryHealthBar() const;
	UIElement* GetEnemyHealthBar() const;
	UIElement* GetPlayerPrimaryHealthBar() const;
	UIElement* GetPlayerSecondaryHealthBar() const;
	UIElement* GetPlayerExperienceBar() const;
};

