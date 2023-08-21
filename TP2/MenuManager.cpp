#include <iostream>
#include <raylib.h>
#include <string>

#include "MenuManager.h"
#include "MathUtils.h"
#include "CameraManager.h"
#include "Globals.h"
#include "Enumerations.h"

using namespace std;

MenuManager* MenuManager::_Instance = nullptr;

MenuManager::MenuManager()
{
	std::cout << "MenuManager constructor called" << std::endl;
}

MenuManager::~MenuManager()
{
	std::cout << "MenuManager destructor called" << std::endl;
}

MenuManager* MenuManager::GetInstance()
{
	if (_Instance == nullptr || NULL)
	{
		_Instance = new MenuManager();
	}
	return _Instance;
}

void MenuManager::RenderPause()
{
	switch (m_currentMenu)
	{
	case EUIMenuType::MAIN_MENU:
		RenderMainMenu();
		break;

	case EUIMenuType::LEVELUP_MENU:
		RenderLevelUp();
		break;

	case EUIMenuType::GAMEOVER_MENU:
		RenderGameOver();
		break;

	case EUIMenuType::COUNT:
	default:
		std::cout << "Invalid menu type" << std::endl;
		break;
	}
}

void MenuManager::RenderMainMenu()
{
	float zoom = CameraManager::GetInstance()->GetCameraZoom();

	// Get the top-left corner, width, and height of the camera
	Vector2 topLeftCorner = CameraManager::GetInstance()->GetCameraTopLeftCorner();
	float cameraWidth = CameraManager::GetInstance()->GetCameraWidth();
	float cameraHeight = CameraManager::GetInstance()->GetCameraHeight();

	// Adjust the width and height of the rectangle based on the zoom value
	float adjustedWidth = cameraWidth / zoom;
	float adjustedHeight = cameraHeight / zoom;

	float halfWidth = adjustedWidth * HALF;
	float halfHeight = adjustedHeight * HALF;

	// Draw background
	DrawRectangle((int)topLeftCorner.x, (int)topLeftCorner.y, (int)adjustedWidth, (int)adjustedHeight, Fade(BLACK, 0.5f));

	// Draw Menu Box
	float menuBoxWidth = MAIN_MENU_WIDTH;
	float menuBoxHeight = GAMEOVER_MENU_HEIGHT;
	float menuBoxXPosition = topLeftCorner.x + halfWidth - menuBoxWidth * HALF;
	float menuBoxYPosition = topLeftCorner.y + halfHeight - menuBoxHeight * HALF;
	Rectangle menuBox = { menuBoxXPosition, menuBoxYPosition, menuBoxWidth, menuBoxHeight };
	DrawRectangleRounded(menuBox, DEFAULT_MENU_ROUNDNESS, DEFAULT_MENU_SEGMENTS, LIGHTGRAY);

	// Draw text

	// Press to start a new game
	string pressEnterText = PRESS_ENTER_TEXT;
	int menuFontSize = DEFAULT_MENU_TITLE_FONTSIZE;
	float textHeight = menuFontSize * HALF;
	int textWidth = MeasureText(pressEnterText.c_str(), menuFontSize);
	float uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	float uiPositionY = menuBox.y + textHeight;
	DrawText(pressEnterText.c_str(), (int)uiPositionX, (int)uiPositionY, menuFontSize, DARKBLUE);
}

void MenuManager::RenderLevelUp()
{
	float zoom = CameraManager::GetInstance()->GetCameraZoom();

	// Get the top-left corner, width, and height of the camera
	Vector2 topLeftCorner = CameraManager::GetInstance()->GetCameraTopLeftCorner();
	float cameraWidth = CameraManager::GetInstance()->GetCameraWidth();
	float cameraHeight = CameraManager::GetInstance()->GetCameraHeight();

	// Adjust the width and height of the rectangle based on the zoom value
	float adjustedWidth = cameraWidth / zoom;
	float adjustedHeight = cameraHeight / zoom;

	float halfWidth = adjustedWidth * HALF;
	float halfHeight = adjustedHeight * HALF;

	// Draw background
	DrawRectangle((int)topLeftCorner.x, (int)topLeftCorner.y, (int)adjustedWidth, (int)adjustedHeight, Fade(BLACK, 0.5f));

	// Draw Menu Box
	float menuBoxWidth = DEFAULT_MENU_WIDTH;
	float menuBoxHeight = LEVELUP_MENU_HEIGHT;
	float menuBoxXPosition = topLeftCorner.x + halfWidth - menuBoxWidth * HALF;
	float menuBoxYPosition = topLeftCorner.y + halfHeight - menuBoxHeight * HALF;
	Rectangle menuBox = { menuBoxXPosition, menuBoxYPosition, menuBoxWidth, menuBoxHeight };
	DrawRectangleRounded(menuBox, DEFAULT_MENU_ROUNDNESS, DEFAULT_MENU_SEGMENTS, LIGHTGRAY);

	// Draw text

	// Level Up
	string levelUpText = LEVEL_UP_TEXT;
	int menuFontSize = DEFAULT_MENU_TITLE_FONTSIZE;
	float textHeight = menuFontSize * HALF;
	int textWidth = MeasureText(levelUpText.c_str(), menuFontSize);
	float uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	float uiPositionY = menuBox.y + textHeight;
	DrawText(levelUpText.c_str(), (int)uiPositionX, (int)uiPositionY, menuFontSize, DARKBLUE);

	// Upgrades

	// Shooting rate
	string shootingRateText = SHOOTING_RATE_TEXT;
	int choicesFontSize = DEFAULT_MENU_CHOICES_FONTSIZE;
	textHeight = choicesFontSize * HALF;
	textWidth = MeasureText(shootingRateText.c_str(), choicesFontSize);
	float offsetDown = menuBoxHeight * EIGHTH;
	uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	uiPositionY += offsetDown;
	DrawText(shootingRateText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

	// Shooting Damage
	string shootingDamageText = SHOOTING_DAMAGE_TEXT;
	textHeight = choicesFontSize * HALF;
	textWidth = MeasureText(shootingDamageText.c_str(), choicesFontSize);
	offsetDown = menuBoxHeight * EIGHTH;
	uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	uiPositionY += offsetDown;
	DrawText(shootingDamageText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

	// Projectile Size
	string bulletSizeText = BULLET_SIZE_TEXT;
	textHeight = choicesFontSize * HALF;
	textWidth = MeasureText(bulletSizeText.c_str(), choicesFontSize);
	offsetDown = menuBoxHeight * EIGHTH;
	uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	uiPositionY += offsetDown;
	DrawText(bulletSizeText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

	// Health Capacity
	string healthCapText = HEALTH_CAP_TEXT;
	textHeight = choicesFontSize * HALF;
	textWidth = MeasureText(healthCapText.c_str(), choicesFontSize);
	offsetDown = menuBoxHeight * EIGHTH;
	uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	uiPositionY += offsetDown;
	DrawText(healthCapText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

	// New HandGun
	string newHandGunText = NEW_HAND_GUN_TEXT;
	textHeight = choicesFontSize * HALF;
	textWidth = MeasureText(newHandGunText.c_str(), choicesFontSize);
	offsetDown = menuBoxHeight * EIGHTH;
	uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	uiPositionY += offsetDown;
	DrawText(newHandGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

	// New Eplosive Gun
	string newExplosiveGunText = NEW_EXPLOSIVE_GUN_TEXT;
	textHeight = choicesFontSize * HALF;
	textWidth = MeasureText(newExplosiveGunText.c_str(), choicesFontSize);
	offsetDown = menuBoxHeight * EIGHTH;
	uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	uiPositionY += offsetDown;
	DrawText(newExplosiveGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

	// New Laser Gun
	string newLaserGunText = NEW_LASER_GUN_TEXT;
	textHeight = choicesFontSize * HALF;
	textWidth = MeasureText(newLaserGunText.c_str(), choicesFontSize);
	offsetDown = menuBoxHeight * EIGHTH;
	uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	uiPositionY += offsetDown;
	DrawText(newLaserGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

}

void MenuManager::RenderGameOver()
{
	float zoom = CameraManager::GetInstance()->GetCameraZoom();

	// Get the top-left corner, width, and height of the camera
	Vector2 topLeftCorner = CameraManager::GetInstance()->GetCameraTopLeftCorner();
	float cameraWidth = CameraManager::GetInstance()->GetCameraWidth();
	float cameraHeight = CameraManager::GetInstance()->GetCameraHeight();

	// Adjust the width and height of the rectangle based on the zoom value
	float adjustedWidth = cameraWidth / zoom;
	float adjustedHeight = cameraHeight / zoom;

	float halfWidth = adjustedWidth * HALF;
	float halfHeight = adjustedHeight * HALF;

	// Draw background
	DrawRectangle((int)topLeftCorner.x, (int)topLeftCorner.y, (int)adjustedWidth, (int)adjustedHeight, Fade(BLACK, 0.5f));

	// Draw Menu Box
	float menuBoxWidth = DEFAULT_MENU_WIDTH;
	float menuBoxHeight = GAMEOVER_MENU_HEIGHT;
	float menuBoxXPosition = topLeftCorner.x + halfWidth - menuBoxWidth * HALF;
	float menuBoxYPosition = topLeftCorner.y + halfHeight - menuBoxHeight * HALF;
	Rectangle menuBox = { menuBoxXPosition, menuBoxYPosition, menuBoxWidth, menuBoxHeight };
	DrawRectangleRounded(menuBox, DEFAULT_MENU_ROUNDNESS, DEFAULT_MENU_SEGMENTS, LIGHTGRAY);

	// Draw text

	// GameOver
	string gameOverText = GAMEOVER_TEXT;
	int menuFontSize = DEFAULT_MENU_TITLE_FONTSIZE;
	float textHeight = menuFontSize * HALF;
	int textWidth = MeasureText(gameOverText.c_str(), menuFontSize);
	float uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
	float uiPositionY = menuBox.y + textHeight;
	DrawText(gameOverText.c_str(), (int)uiPositionX, (int)uiPositionY, menuFontSize, DARKBLUE);
}
