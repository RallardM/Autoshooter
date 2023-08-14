#include <iostream>
#include <raylib.h>
#include <string>

#include "MenuManager.h"
#include "MathUtils.h"
#include "CameraManager.h"

using namespace std;

MenuManager* MenuManager::_Instance = 0;

MenuManager::~MenuManager()
{

    // Keep _Instance check at the end
    if (_Instance != nullptr || NULL)
	{
		delete _Instance;
		_Instance = nullptr;
	}
}

MenuManager* MenuManager::GetInstance()
{

    // Keep _Instance check at the end
    if (_Instance == nullptr || NULL)
    {
        _Instance = new MenuManager();
    }
    return _Instance;
}

void MenuManager::RenderPause()
{
    if (m_isPlayerDeadMenuOn)
    {
        RenderGameOver();
        return;
    }

    if (m_isLevelUpMenuOn)
    {
        RenderLevelUp();
    }
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
    float menuBoxWidth = 400;
    float menuBoxHeight = 700;
    float menuBoxXPosition = topLeftCorner.x + halfWidth - menuBoxWidth * HALF;
    float menuBoxYPosition = topLeftCorner.y + halfHeight - menuBoxHeight * HALF;
    Rectangle menuBox = { menuBoxXPosition, menuBoxYPosition, menuBoxWidth, menuBoxHeight };
    DrawRectangleRounded(menuBox, 0.1f, 12, LIGHTGRAY);

    // Draw text

    // Level Up
    string levelUpText = "Level Up!";
    int menuFontSize = 40;
    float textHeight = menuFontSize * HALF;
    int textWidth = MeasureText(levelUpText.c_str(), menuFontSize);
    float uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    float uiPositionY = menuBox.y + textHeight;
    DrawText(levelUpText.c_str(), (int)uiPositionX, (int)uiPositionY, menuFontSize, DARKBLUE);

    // Upgrades

    // Shooting rate
    string shootingRateText = "1 Shooting Rate x 2";
    int choicesFontSize = 30;
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(shootingRateText.c_str(), choicesFontSize);
    float offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(shootingRateText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // Shooting Damage
    string shootingDamageText = "2 Shooting Damage x 2";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(shootingDamageText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(shootingDamageText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // Projectile Size
    string bulletSizeText = "3 Projectile Size x 2";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(bulletSizeText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(bulletSizeText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // Health Capacity
    string healthCapText = "4 Health Bonus + 10";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(healthCapText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(healthCapText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // New HandGun
    string newHandGunText = "5 New HandGun";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(newHandGunText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(newHandGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // New Eplosive Gun
    string newExplosiveGunText = "6 New Explosive Gun";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(newExplosiveGunText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(newExplosiveGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // New Laser Gun
    string newLaserGunText = "7 New Laser Gun";
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
    float menuBoxWidth = 400;
    float menuBoxHeight = 100;
    float menuBoxXPosition = topLeftCorner.x + halfWidth - menuBoxWidth * HALF;
    float menuBoxYPosition = topLeftCorner.y + halfHeight - menuBoxHeight * HALF;
    Rectangle menuBox = { menuBoxXPosition, menuBoxYPosition, menuBoxWidth, menuBoxHeight };
    DrawRectangleRounded(menuBox, 0.1f, 12, LIGHTGRAY);

    // Draw text

    // Level Up
    string levelUpText = "Game Over!";
    int menuFontSize = 40;
    float textHeight = menuFontSize * HALF;
    int textWidth = MeasureText(levelUpText.c_str(), menuFontSize);
    float uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    float uiPositionY = menuBox.y + textHeight;
    DrawText(levelUpText.c_str(), (int)uiPositionX, (int)uiPositionY, menuFontSize, DARKBLUE);
}
