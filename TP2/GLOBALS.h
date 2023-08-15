#include <string>
#pragma once
const short int HEALTH_VALUE = 100;
const unsigned short int MAX_HEATH_VALUE = 100;

// Projectile data default values
const float PROJECTILE_RADIUS = 5.0f;
const float PROJECTILE_LIFETIME = 2.0f;
const float PROJECTILE_DAMAGE = 10.0f;
const float PROJECTILE_SPEED = 300.0f;
const Color PROJECTILE_COLOR = { 255, 255, 255, 255 };
const float P_INCREASE_DAMAGE_FACTOR = 2.0f;

//Explosive gun projectiles data on fire
const float E_PROJECTILE_RADIUS = 7.0f;
const float E_PROJECTILE_LIFETIME = 0.5f;
const float E_PROJECTILE_DAMAGE = 15.0f;
const float E_PROJECTILE_SPEED = 50.0f;
const Color E_PROJECTILE_COLOR = GOLD;
//const int E_PROJECTILE_RADIUS = 16;
//const int E_PROJECTILE_NUMBER = 8;
//const int E_EXPLOSIVEGUN_OFFSET = 30.0F;
//const int E_PROJECTILE_EDGE_NUMBER = 3;

//HandGun 
const int H_HANDGUN_OFFSET = 35.0f;
const int TO_DOUBLE = 2;


// Player 
const Color PLAYER_COLOR = { 40, 40, 40, 255 };
const Vector2 PLAYER_SIZE = { 40.0f, 40.0f };
const Vector2 PLAYER_DIRECTION = { 0.0f, 0.0f };
const float PLAYER_SPEED = 200.0f;
const unsigned short int PLAYER_LEVEL = 1;
const float P_HEALTH_WIDTH = 40.0f;
const float P_HEALTH_HEIGHT = 3.0f;
const float P_PLAYER_OFFSET = 3.0f;
const float P_PLAYER_HEALTH_DAMAGE = 10;
const float P_PLAYEROFFSET = 37.0f;
const float P_EXTRA_HEALTH_HEIGHT = 3.0f;
const int P_HEALTH_INCREASE = 10;
const int P_MAX_EXPERIENCE = 100;

const float P_EXTRA_HEALTH_FACTOR = 40.0f;
const int TO_PERCENT = 100;

// Game manager 
const int CAM_WIDTH = 1200;
const int CAM_HEIGHT = 800;
const float CAM_ZOOM = 0.8f;
const float MAP_WIDTH = 1601.0f;
const float MAP_HEIGHT = 1601.0f;
const float MAP_CELL_SIZE = 16.0f;
const float OFFSET_X = 0.0f;
const float OFFSET_Y = 33.0f;
const int CORNER_NUMBER = 4;

// Menu
const int MENU_WIDTH = 400;
const int MENU_HEIGHT = 700;
const float M_ROUNDNESS = 0.1f;
const int M_SEGMENTS = 12;
const int M_FONTSIZE_1 = 40;
const int M_FONTSIZE_2 = 30;
const std::string LEVEL_UP_TEXT = "Level Up!";
const std::string SHOOTING_RATE_TEXT = "1 Shooting Rate x 2";
const std::string SHOOTING_DAMAGE_TEXT = "2 Shooting Damage x 2";
const std::string BULLET_SIZE_TEXT = "3 Projectile Size x 2";
const std::string HEALTH_CAP_TEXT = "4 Health Bonus + 10";
const std::string NEW_HAND_GUN_TEXT = "5 New HandGun";
const std::string NEW_EXPLOSIVE_GUN_TEXT = "6 New Explosive Gun";
const std::string NEW_LASER_GUN_TEXT = "7 New Laser Gun";
// Enemy
const int ENEMY_AMOUNT = 10;
const int ENEMY_WIDTH = 32.0f;
const int ENEMY_HEIGHT = 32.0f;
const int ENEMY_HEALTH = 100;

// Health bar
const float HEALTH_WIDTH = 32.0f;
const float HEALTH_HEIGHT = 3.0f;

// Second Health bar
const float S_HEALTH_WIDTH = 40.0f;

// Threshold
const int MAX_THRESHOLD = 10;
const int MIN_THRESHOLD = 1;

// UI offset
const float UI_OFFSET_SET_RIGHT = 5.0f;

// Color
const int MIN_RANDOM_VALUE = 10;
const int MAX_RANDOM_VALUE = 240;

const float LAZER_GUN_OFFSET = 25.0f;

// Game
const int TARGET_FPS = 60;