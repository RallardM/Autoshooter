/*
* Globals file that contains all declaration of globals variables use in this game prototype
*/
#pragma once
#include <iostream>
#include <raylib.h>
#include "BoxCollider.h"

enum FireMode
{
	Manual,
	SemiAuto,
	Auto
};

//const char* WINDOW_TITLE = "Auto Shooter - V.0.01";
const int WIDTH = 1280;
const int HEIGHT = 720; // default value pick by Maxime would be 800 pixel
const Vector2 SCREEN_CENTER_POINT = { WIDTH * 0.5f , HEIGHT * 0.5f};
const int UPS = 60;

const int DEFAULT_ENEMY_AMOUNT = 10;

// Player default parameter
const int PLAYER_WIDTH = 32.0f;
const int PLAYER_HEIGHT = 32.0f;
const float PLAYER_SPEED = 200.0f;

// Projectile default parameter
const int PROJECTILE_WIDTH = 16.0f;
const int PROJECTILE_HEIGHT = 16.0f;
const float PROJECTILE_SPEED = 200.0f;

// Enemy default parameter
const int ENEMY_WIDTH = 32.0f;
const int ENEMY_HEIGHT = 32.0f;
const float MAX_ENEMY_SPEED = 100.0f;
const float MIN_ENEMY_SPEED = 50.0f;

