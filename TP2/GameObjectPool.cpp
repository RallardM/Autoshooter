#include <iostream>

#include "GameObjectPool.h"
#include "MathUtils.h"
#include "CameraManager.h"
#include "Globals.h"
#include "Entity.h"

GameObjectPool* GameObjectPool::_Instance = nullptr;

GameObjectPool::~GameObjectPool()
{
}

GameObjectPool* GameObjectPool::GetInstance()
{
	if (_Instance == nullptr)
	{
		_Instance = new GameObjectPool();
	}
	return _Instance;
}

GameObjectPool::GameObjectPool()
{
	std::cout << "GameObjectPool created" << std::endl;
}

void GameObjectPool::InitializeGameObjects()
{
	// Initialize random seed
	srand(static_cast<unsigned int>(time(NULL))); // cast for the warning :  C4244: 'argument': conversion from 'time_t' to 'unsigned int', possible loss of data

	// Initialize camera manager
	CameraManager* m_cameraManager = CameraManager::GetInstance();
	m_cameraManager->InitializeCamera();
	m_camera = m_cameraManager->GetCamera();

	// Initialize UIELEMENT elements pool
	for (int i = 0; i < UI_ELEMENTS_POOL_SIZE; i++)
	{
		auto emptyUiData = std::make_shared<SUIElementData>();
		UIElement* ui = new UIElement(emptyUiData.get());
		m_uiElementsPool.push_back(ui);
		m_allGameObjectsPool.push_back(ui);
	}

	// Initialize enemies pool
	for (int i = 0; i < ENEMIES_POOL_SIZE; i++)
	{
		Enemy* enemy = new Enemy();
		m_enemiesPool.push_back(enemy);
		m_allGameObjectsPool.push_back(enemy);
		m_allEntitiesPool.push_back(enemy);
	}

	// Initialize hand gun pool
	for (int i = 0; i < HANDGUNS_POOL_SIZE; i++)
	{
		HandGun* handGun = new HandGun();
		m_handGunsPool.push_back(handGun);
		m_allWeaponsPool.push_back(handGun);
		m_allGameObjectsPool.push_back(handGun);
	}

	// Initialize explosive gun pool
	for (int i = 0; i < EXPLOSIVEGUNS_POOL_SIZE; i++)
	{
		ExplosiveGun* explosiveGun = new ExplosiveGun();
		m_explosiveGunsPool.push_back(explosiveGun);
		m_allWeaponsPool.push_back(explosiveGun);
		m_allGameObjectsPool.push_back(explosiveGun);
	}

	// Initialize laser gun pool
	for (int i = 0; i < LASERGUNS_POOL_SIZE; i++)
	{
		LaserGun* laserGun = new LaserGun();
		m_laserGunsPool.push_back(laserGun);
		m_allWeaponsPool.push_back(laserGun);
		m_allGameObjectsPool.push_back(laserGun);
	}

	// Initialize projectiles pool
	for (int i = 0; i < PROJECTILES_POOL_SIZE; i++)
	{
		SProjectileData data;
		SetEmptyProjectileInfos(data);
		Projectile* projectile = new Projectile(m_emptyWeaponInfos.m_projectileInfos);
		m_projectilesPool.push_back(projectile);
		m_allGameObjectsPool.push_back(projectile);
	}

	// Initialize experience orbs pool
	for (int i = 0; i < EXPERIENCE_ORBS_POOL_SIZE; i++)
	{
		ExperienceOrb* experienceOrb = new ExperienceOrb();
		m_experienceOrbsPool.push_back(experienceOrb);
		m_allGameObjectsPool.push_back(experienceOrb);
	}

	// Initialize player
	m_player = new Player();
	m_player->OnStart();
	m_allGameObjectsPool.push_back(m_player);
	m_allEntitiesPool.push_back(m_player);

	_Instance = this;
	InitWindow((int)m_cameraManager->GetCameraWidth(), (int)m_cameraManager->GetCameraHeight(), "raylib [core] example - basic window");
	SetTargetFPS(TARGET_FPS);
}


void GameObjectPool::CleanUpGame()
{
	RemoveAllGameObjects();
}

const EGameObjectType GameObjectPool::GetGameObjectType(GameObject* gameObject) const
{
	return gameObject->GetGameObjectType();
}

const Enemy* GameObjectPool::GetClosestEnemy(const Vector2& position) const
{
	Enemy* closest = nullptr;
	float closestDistance = 0.0f;

	for (Enemy* enemy : _Instance->m_enemiesPool)
	{
		if (enemy->IsActive() == false)
		{
			continue;
		}

		float distance = GetFloatDistanceBetweenTwoVects(position, enemy->GetPosition());
		if (closest == nullptr || distance < closestDistance)
		{
			closest = enemy;
			closestDistance = distance;
		}
	}

	return closest;
}

const void GameObjectPool::UpdateGameObjects(const float& deltatime) const
{

	for (auto const& i : m_allGameObjectsPool)
	{
		if (i == NULL) { continue; }

		if (i->IsActive() == false) { continue; }

		i->Update(deltatime);
	}
}

const unsigned short int GameObjectPool::GetActiveObjectCountFromList(const EGameObjectType& type) const
{
	unsigned short int count = 0;
	for (auto const& i : m_allGameObjectsPool)
	{
		if (i == NULL) { continue; }

		if (i->GetGameObjectType() == type && i->IsActive())
		{
			count++;
		}
	}

	return count;
}

const void GameObjectPool::RenderGameObjects() const
{
	// Layer 0 : Background

	// Render Layer 1 : UIELEMENT
	for (auto const& i : m_uiElementsPool)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }

		i->Render();
	}

	// Layer 2 : Player
	m_player->Render();

	// Layer 3 : Weapons
	for (auto const& i : m_allWeaponsPool)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }
		if (i->GetGameObjectType() != EGameObjectType::WEAPON) { continue; }

		i->Render();
	}

	// Layer 4 : Enemies
	for (auto const& i : m_enemiesPool)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }
		if (i->GetGameObjectType() != EGameObjectType::ENEMY) { continue; }

		i->Render();
	}

	// Layer 5 : Projectiles
	for (auto const& i : m_projectilesPool)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }
		if (i->GetGameObjectType() != EGameObjectType::PROJECTILE) { continue; }

		i->Render();
	}
}

const void GameObjectPool::UpdateEnemySpawner() const
{
	EGameObjectType enemyType = EGameObjectType::ENEMY;
	unsigned short int enemiesCount = GameObjectPool::GetInstance()->GetActiveObjectCountFromList(enemyType);

	if (enemiesCount == ENEMIES_POOL_SIZE) { return; }

	// Returns if there are more enemies than the max amount allowed per level
	if (enemiesCount >= MAX_ENEMY_AMOUNT_PER_LEVELS * m_player->GetLevel()) { return; }

	for (Enemy* enemy : m_enemiesPool)
	{
		if (enemy == nullptr) { continue; }
		if (enemy->IsActive() == true) { continue; }

		enemy->OnStart();

		// Update enemies count
		enemiesCount = GameObjectPool::GetInstance()->GetActiveObjectCountFromList(enemyType);
		if (enemiesCount >= MAX_ENEMY_AMOUNT_PER_LEVELS * m_player->GetLevel()) { break; }
	}
}

const void GameObjectPool::TakeProjectileFromPool(const SProjectileData& projectileData) const
{
	for (Projectile* projectile : m_projectilesPool)
	{
		if (projectile == nullptr) { continue; }
		if (projectile->IsActive() == true) { continue; }

		projectile->SetProjectileData(projectileData);
		projectile->OnStart();
		break;
	}
}

const void GameObjectPool::TakeHandGunFromPool() const
{
	for (HandGun* handGun : m_handGunsPool)
	{
		if (handGun == nullptr) { continue; }
		if (handGun->IsActive() == true) { continue; }

		handGun->OnStart();
		break;
	}
}

const void GameObjectPool::TakeExplosiveGunFromPool() const
{
	for (ExplosiveGun* explosiveGun : m_explosiveGunsPool)
	{
		if (explosiveGun == nullptr) { continue; }
		if (explosiveGun->IsActive() == true) { continue; }

		explosiveGun->OnStart();
		break;
	}
}

const void GameObjectPool::TakeLaserGunFromPool() const
{
	for (LaserGun* laserGun : m_laserGunsPool)
	{
		if (laserGun == nullptr) { continue; }
		if (laserGun->IsActive() == true) { continue; }

		laserGun->OnStart();
		break;
	}
}

const void GameObjectPool::TakeUIElementFromPool(SUIElementData* uiData) const
{
	for (UIElement* uiElement : m_uiElementsPool)
	{
		if (uiElement == nullptr) { continue; }

		if (uiElement->IsActive() == true) { continue; }

		uiElement->SetUIElementData(uiData);
		uiElement->OnStart();
		break;
	}
}

const void GameObjectPool::TakeExperienceOrbFromPool(const Vector2 position) const
{
	for (ExperienceOrb* experienceOrb : m_experienceOrbsPool)
	{
		if (experienceOrb == nullptr) { continue; }
		if (experienceOrb->IsActive() == true) { continue; }

		experienceOrb->SetPosition(position);
		experienceOrb->OnStart();
		break;
	}
}

const std::vector<Weapon*> GameObjectPool::GetActiveWeapons() const
{
	std::vector<Weapon*> activeWeapons;

	for (Weapon* weapon : m_allWeaponsPool)
	{
		if (weapon == nullptr) { continue; }
		if (weapon->IsActive() == false) { continue; }

		activeWeapons.push_back(const_cast<Weapon*>(weapon));
	}

	return activeWeapons;
}

const std::vector<Projectile*> GameObjectPool::GetActiveProjectiles() const
{
	std::vector<Projectile*> activeProjectiles;

	for (Projectile* projectile : m_projectilesPool)
	{
		if (projectile == nullptr) { continue; }
		if (projectile->IsActive() == false) { continue; }

		activeProjectiles.push_back(const_cast<Projectile*>(projectile));
	}

	return activeProjectiles;
}

const std::vector<Enemy*> GameObjectPool::GetActiveEnemies() const
{
	std::vector<Enemy*> activeEnemies;

	for (Enemy* enemy : m_enemiesPool)
	{
		if (enemy == nullptr) { continue; }
		if (enemy->IsActive() == false) { continue; }

		activeEnemies.push_back(const_cast<Enemy*>(enemy));
	}

	return activeEnemies;
}

UIElement* GameObjectPool::GetEnemyHealthBar(const unsigned short int& id) const
{
	for (UIElement* uiElement : m_uiElementsPool)
	{
		if (uiElement == nullptr) { continue; }
		if (uiElement->IsActive() == false) { continue; }
		if (uiElement->m_uiData->TARGET_ID != id) { continue; }

		return uiElement;
		break;
	}

	return nullptr;
}

UIElement* GameObjectPool::GetPlayerPrimaryHealthBar(const unsigned short int& id) const
{
	UIElement* playerPrimaryHealthBar = nullptr;

	for (UIElement* uiElement : m_uiElementsPool)
	{
		if (uiElement == nullptr) { continue; }
		if (uiElement->IsActive() == false) { continue; }
		if (uiElement->m_uiData->TARGET_ID != id) { continue; }
		if (uiElement->m_uiData->UIELEMENT_TYPE != static_cast<unsigned short int>(EUIElementType::REGRESS_BAR)) { continue; }

		if (uiElement->m_uiData->HAS_SECONDARY_BAR == true)
		{
			playerPrimaryHealthBar = uiElement;
			break;
		}
		else if (uiElement->m_uiData->HAS_SECONDARY_BAR == false)
		{
			playerPrimaryHealthBar = uiElement;
			continue;
		}
	}

	return playerPrimaryHealthBar;
}

UIElement* GameObjectPool::GetPlayerSecondaryHealthBar(const unsigned short int& id) const
{
	for (UIElement* uiElement : m_uiElementsPool)
	{
		if (uiElement == nullptr) { continue; }
		if (uiElement->IsActive() == false) { continue; }
		if (uiElement->m_uiData->TARGET_ID != id) { continue; }
		if (uiElement->m_uiData->UIELEMENT_TYPE != static_cast<unsigned short int>(EUIElementType::REGRESS_BAR)) { continue; }

		if (uiElement->m_uiData->HAS_SECONDARY_BAR == true)
		{
			continue;
		}
		else if (uiElement->m_uiData->HAS_SECONDARY_BAR == false)
		{
			return uiElement;
		}
	}

	return nullptr;
}

UIElement* GameObjectPool::GetPlayerExperienceBar(const unsigned short int& id) const
{
	for (UIElement* uiElement : m_uiElementsPool)
	{
		if (uiElement == nullptr) { continue; }
		if (uiElement->IsActive() == false) { continue; }
		if (uiElement->m_uiData->TARGET_ID != id) { continue; }
		if (uiElement->m_uiData->UIELEMENT_TYPE != static_cast<unsigned short int>(EUIElementType::PROGRESS_BAR)) { continue; }

		return uiElement;
		break;
	}

	return nullptr;
}

Entity* GameObjectPool::GetEntityFromID(const unsigned short int& id) const
{
	for (Entity* entity : m_allEntitiesPool)
	{
		if (entity == nullptr) { continue; }
		if (entity->IsActive() == false) { continue; }
		if (entity->GetEntityID() != id) { continue; }

		return entity;
	}

	return nullptr;
}

const void GameObjectPool::RemoveAllGameObjects()
{
	for (auto* i : m_allGameObjectsPool)
	{
		delete i;
		i = nullptr;
	}
	m_allGameObjectsPool.clear();

	for (auto* i : m_allWeaponsPool)
	{
		delete i;
		i = nullptr;
	}
	m_allWeaponsPool.clear();

	for (auto* i : m_uiElementsPool)
	{
		delete i;
		i = nullptr;
	}
	m_uiElementsPool.clear();

	for (auto* i : m_allEntitiesPool)
	{
		delete i;
		i = nullptr;
	}
	m_allEntitiesPool.clear();

	for (auto* i : m_enemiesPool)
	{
		delete i;
		i = nullptr;
	}
	m_enemiesPool.clear();

	for (auto* i : m_handGunsPool)
	{
		delete i;
		i = nullptr;
	}
	m_handGunsPool.clear();

	for (auto* i : m_explosiveGunsPool)
	{
		delete i;
		i = nullptr;
	}
	m_explosiveGunsPool.clear();

	for (auto* i : m_laserGunsPool)
	{
		delete i;
		i = nullptr;
	}
	m_laserGunsPool.clear();

	for (auto* i : m_projectilesPool)
	{
		delete i;
		i = nullptr;
	}
	m_projectilesPool.clear();

	for (auto* i : m_experienceOrbsPool)
	{
		delete i;
		i = nullptr;
	}
	m_experienceOrbsPool.clear();
}