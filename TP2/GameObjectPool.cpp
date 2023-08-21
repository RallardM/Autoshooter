#include <iostream>

#include "GameObjectPool.h"
#include "MathUtils.h"
#include "CameraManager.h"
#include "Globals.h"
#include "HandGun.h"
#include "ExplosiveGun.h"
#include "LaserGun.h"


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
		SUIElementData emptyUiData;
		UIElement* ui = new UIElement(emptyUiData);
		m_gameObjects.push_back(ui);
	}

	// Initialize enemies pool
	for (int i = 0; i < ENEMIES_POOL_SIZE; i++)
	{
		Enemy* enemy = new Enemy();
		m_gameObjects.push_back(enemy);
	}

	// Initialize hand gun pool
	for (int i = 0; i < HANDGUNS_POOL_SIZE; i++)
	{
		HandGun* handGun = new HandGun();
		m_gameObjects.push_back(handGun);
	}

	// Initialize explosive gun pool
	for (int i = 0; i < EXPLOSIVEGUNS_POOL_SIZE; i++)
	{
		ExplosiveGun* explosiveGun = new ExplosiveGun();
		m_gameObjects.push_back(explosiveGun);
	}

	// Initialize laser gun pool
	for (int i = 0; i < LASERGUNS_POOL_SIZE; i++)
	{
		LaserGun* laserGun = new LaserGun();
		m_gameObjects.push_back(laserGun);
	}

	// Initialize projectiles pool
	for (int i = 0; i < PROJECTILES_POOL_SIZE; i++)
	{
		SProjectileData data;
		SetEmptyProjectileInfos(data);
		Projectile* projectile = new Projectile(m_emptyWeaponInfos.m_projectileInfos);
		m_gameObjects.push_back(projectile);
	}

	// Initialize player
	m_player = new Player();
	m_player->OnStart();
	m_gameObjects.push_back(m_player);

	_Instance = this;
	InitWindow((int)m_cameraManager->GetCameraWidth(), (int)m_cameraManager->GetCameraHeight(), "raylib [core] example - basic window");
	SetTargetFPS(TARGET_FPS);
}

EGameObjectType GameObjectPool::GetGameObjectType(GameObject* gameObject)
{
	return gameObject->GetGameObjectType();
}

GameObject* GameObjectPool::GetClosestGameObject(const Vector2& position, const EGameObjectType& type)
{
	GameObject* closest = nullptr;
	float closestDistance = 0.f;

	for (GameObject* gameObject : _Instance->m_gameObjects)
	{
		if (gameObject->GetGameObjectType() == type)
		{
			float distance = GetFloatDistanceBetweenTwoVects(position, gameObject->GetPosition());
			if (closest == nullptr || distance < closestDistance)
			{
				closest = gameObject;
				closestDistance = distance;
			}
		}
	}

	return closest;
}

void GameObjectPool::UpdateGameObjects(const float& deltatime)
{

	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		if (i->IsActive() == false)
		{
			continue;
		}

		i->Update(deltatime);
	}
}

unsigned short int GameObjectPool::GetActiveObjectCountFromList(const EGameObjectType& type)
{
	unsigned short int count = 0;
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		if (i->GetGameObjectType() == type && i->IsActive())
		{
			count++;
		}
	}

	return count;
}

void GameObjectPool::RenderGameObjects()
{
	// Layer 0 : Background
	// 
	// Render Layer 1 : UIELEMENT
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }
		if (i->GetGameObjectType() != EGameObjectType::UIELEMENT) { continue; }

		i->Render();
	}

	// Layer 2 : Player
	m_player->Render();

	// Layer 3 : Weapons
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }
		if (i->GetGameObjectType() != EGameObjectType::WEAPON) { continue; }

		i->Render();
	}

	// Layer 4 : Enemies
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }
		if (i->GetGameObjectType() != EGameObjectType::ENEMY) { continue; }

		i->Render();
	}

	// Layer 5 : Projectiles
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }
		if (i->IsActive() == false) { continue; }
		if (i->GetGameObjectType() != EGameObjectType::PROJECTILE) { continue; }

		i->Render();
	}
}

void GameObjectPool::ResetAllObjects()
{
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		i->Reset();
	}
}

void GameObjectPool::RemoveAllGameObjects()
{
	for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
	{
		if (m_gameObjectsToRemove[i] == nullptr) { continue; }

		auto iter = std::remove(m_gameObjects.begin(), m_gameObjects.end(), m_gameObjectsToRemove[i]);
		m_gameObjects.erase(iter);

		delete m_gameObjectsToRemove[i];
		m_gameObjectsToRemove[i] = nullptr;
	}

	m_gameObjectsToRemove.clear();
	m_gameObjectsToRemove.resize(0);

	for (GameObject* obj : m_gameObjects)
	{
		if (obj == nullptr) { continue; }

		delete obj;
		obj = nullptr;
	}

	m_gameObjects.clear();
	m_gameObjects.resize(0);
}

void GameObjectPool::UpdateEnemySpawner()
{
	EGameObjectType enemyType = EGameObjectType::ENEMY;
	unsigned short int enemiesCount = GameObjectPool::GetInstance()->GetActiveObjectCountFromList(enemyType);

	if (enemiesCount == ENEMIES_POOL_SIZE) { return; }

	// Returns if there are more enemies than the max amount allowed per level
	if (enemiesCount >= MAX_ENEMY_AMOUNT_PER_LEVELS * m_player->GetLevel()) { return; }

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == true || gameObject->GetGameObjectType() != EGameObjectType::ENEMY)
		{
			continue;
		}

		gameObject->OnStart();

		// Update enemies count
		enemiesCount = GameObjectPool::GetInstance()->GetActiveObjectCountFromList(enemyType);
		if (enemiesCount >= MAX_ENEMY_AMOUNT_PER_LEVELS * m_player->GetLevel()) { break; }
	}
}

void GameObjectPool::TakeProjectileFromPool(SProjectileData& projectileData)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == true || gameObject->GetGameObjectType() != EGameObjectType::PROJECTILE)
		{
			continue;
		}

		Projectile* projectile = static_cast<Projectile*>(gameObject);

		if (projectile == nullptr) { continue; }

		projectile->SetProjectileData(projectileData);
		projectile->OnStart();
		break;
	}
}

void GameObjectPool::TakeHandGunFromPool()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == true || gameObject->GetGameObjectType() != EGameObjectType::WEAPON)
		{
			continue;
		}

		Weapon* weapon = static_cast<Weapon*>(gameObject);

		if (weapon == nullptr) { continue; }
		if (weapon->GetWeaponType() != EWeaponType::HANDGUN) { continue; }

		HandGun* handGun = static_cast<HandGun*>(weapon);
		handGun->OnStart();
		break;
	}
}

void GameObjectPool::TakeExplosiveGunFromPool()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == true || gameObject->GetGameObjectType() != EGameObjectType::WEAPON)
		{
			continue;
		}

		Weapon* weapon = static_cast<Weapon*>(gameObject);

		if (weapon == nullptr) { continue; }
		if (weapon->GetWeaponType() != EWeaponType::EXPLOSIVEGUN) { continue; }

		ExplosiveGun* explosiveGun = static_cast<ExplosiveGun*>(weapon);
		explosiveGun->OnStart();
		break;
	}
}

void GameObjectPool::TakeLaserGunFromPool()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == true || gameObject->GetGameObjectType() != EGameObjectType::WEAPON)
		{
			continue;
		}

		Weapon* weapon = static_cast<Weapon*>(gameObject);

		if (weapon == nullptr) { continue; }
		if (weapon->GetWeaponType() != EWeaponType::LAZERGUN) { continue; }

		LaserGun* laserGun = static_cast<LaserGun*>(weapon);
		laserGun->OnStart();
		break;
	}
}

void GameObjectPool::TakeUIElementFromPool(SUIElementData& uiData)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == true || gameObject->GetGameObjectType() != EGameObjectType::UIELEMENT)
		{
			continue;
		}

		UIElement* uiElement = static_cast<UIElement*>(gameObject);

		if (uiElement == nullptr) { continue; }

		uiElement->SetUIElementData(uiData);
		uiElement->OnStart();
		break;

	}
}

void GameObjectPool::CleanUpGame()
{
	ResetAllObjects();
	RemoveAllGameObjects();
}

const std::list<Weapon*> GameObjectPool::GetActiveWeapons() const
{
	std::list<Weapon*> activeWeapons;

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == false || gameObject->GetGameObjectType() != EGameObjectType::WEAPON)
		{
			continue;
		}

		Weapon* weapon = static_cast<Weapon*>(gameObject);
		activeWeapons.push_back(const_cast<Weapon*>(weapon));
	}

	return activeWeapons;
}

const bool GameObjectPool::GetPlayerHasSecondaryHealthBar() const
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == false || gameObject->GetGameObjectType() != EGameObjectType::UIELEMENT)
		{
			continue;
		}

		UIElement* uiElement = static_cast<UIElement*>(gameObject);

		if (uiElement == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET->GetGameObjectType() != EGameObjectType::PLAYER) { continue; }

		if (uiElement->m_uiData.HAS_SECONDARY_BAR == true)
		{
			return true;
		}
		else
		{
			continue;
		}
	}

	return false;
}

UIElement* GameObjectPool::GetEnemyHealthBar() const
{
	UIElement* enemyHealthBar = nullptr;

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == false || gameObject->GetGameObjectType() != EGameObjectType::UIELEMENT)
		{
			continue;
		}

		UIElement* uiElement = static_cast<UIElement*>(gameObject);

		if (uiElement == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET->GetGameObjectType() != EGameObjectType::ENEMY) { continue; }
		if (uiElement->m_uiData.UIELEMENT_TYPE != static_cast<unsigned short int>(EUIElementType::REGRESS_BAR)) { continue; }
		
		enemyHealthBar = uiElement;
		break;

	}

	return enemyHealthBar;
}

UIElement* GameObjectPool::GetPlayerPrimaryHealthBar() const
{
	UIElement* playerPrimaryHealthBar = nullptr;

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == false || gameObject->GetGameObjectType() != EGameObjectType::UIELEMENT)
		{
			continue;
		}

		UIElement* uiElement = static_cast<UIElement*>(gameObject);

		if (uiElement == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET->GetGameObjectType() != EGameObjectType::PLAYER) { continue; }
		if (uiElement->m_uiData.UIELEMENT_TYPE != static_cast<unsigned short int>(EUIElementType::REGRESS_BAR)) { continue; }

		if (uiElement->m_uiData.HAS_SECONDARY_BAR == true)
		{
			playerPrimaryHealthBar = uiElement;
			break;
		}
		else if (uiElement->m_uiData.HAS_SECONDARY_BAR == false)
		{
			playerPrimaryHealthBar = uiElement;
			continue;
		}
	}

	return playerPrimaryHealthBar;
}

UIElement* GameObjectPool::GetPlayerSecondaryHealthBar() const
{
UIElement* playerSecondaryHealthBar = nullptr;

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == false || gameObject->GetGameObjectType() != EGameObjectType::UIELEMENT)
		{
			continue;
		}

		UIElement* uiElement = static_cast<UIElement*>(gameObject);

		if (uiElement == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET->GetGameObjectType() != EGameObjectType::PLAYER) { continue; }
		if (uiElement->m_uiData.UIELEMENT_TYPE != static_cast<unsigned short int>(EUIElementType::REGRESS_BAR)) { continue; }

		if (uiElement->m_uiData.HAS_SECONDARY_BAR == true)
		{
			continue;
		}
		else if (uiElement->m_uiData.HAS_SECONDARY_BAR == false)
		{
			playerSecondaryHealthBar = uiElement;
			break;
		}
	}

	return playerSecondaryHealthBar;
}

UIElement* GameObjectPool::GetPlayerExperienceBar() const
{
	UIElement* playerExperienceBar = nullptr;

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->IsActive() == false || gameObject->GetGameObjectType() != EGameObjectType::UIELEMENT)
		{
			continue;
		}

		UIElement* uiElement = static_cast<UIElement*>(gameObject);

		if (uiElement == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET == nullptr) { continue; }
		if (uiElement->m_uiData.TARGET->GetGameObjectType() != EGameObjectType::PLAYER) { continue; }
		if (uiElement->m_uiData.UIELEMENT_TYPE != static_cast<unsigned short int>(EUIElementType::PROGRESS_BAR)) { continue; }

		playerExperienceBar = uiElement;
		break;

	}

	return playerExperienceBar;
}
