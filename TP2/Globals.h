#pragma once
#include <string>
#include <raylib.h>

const unsigned short int MAX_HEATH_VALUE = 100;

// Directions default values
const Vector2 NO_DIRECTION = { 0.0f, 0.0f };
const Vector2 UP = { 0.0f, -1.0f };
const Vector2 DOWN = { 0.0f, 1.0f };
const Vector2 LEFT = { -1.0f, 0.0f };
const Vector2 RIGHT = { 1.0f, 0.0f };


// Projectile data default values
const unsigned short int NO_COUNTDOWN = 0;
const float NO_ANGLE = 0.0f;
const Vector2 NO_POSITION = { 0.0f, 0.0f };
const float INCREASE_PROJECTILE_FACTOR = 2.0f;

// Weapon data default values
const float WEAPON_ICON_OFFSET = 5.0f;
const unsigned short int MIN_COLOR_CHANNEL_VALUE = 30;
const unsigned short int MAX_COLOR_CHANNEL_VALUE = 200;
const unsigned short int FULL_ALPHA_VALUE = 255;

// HandGun Projectile data default values
const float HANDGUN_PROJECTILE_RADIUS = 5.0f;
const float HANDGUN_PROJECTILE_LIFETIME = 2.0f;
const float HANDGUN_PROJECTILE_DAMAGE = 20.0f;
const float HANDGUN_PROJECTILE_SPEED = 300.0f;
const Color HANDGUN_PROJECTILE_COLOR = LIGHTGRAY;
const float HANDGUN_PROJECTILE_RATE = 1.0f;
const float HANDGUN_ICON_ROW_OFFSET = 27.0f;

//Explosive gun projectiles data on fire
const float EXPLOSIVE_PROJECTILE_RADIUS = 7.0f;
const float EXPLOSIVE_PROJECTILE_LIFETIME = 0.5f;
const float EXPLOSIVE_PROJECTILE_DAMAGE = 40.0f;
const float EXPLOSIVE_PROJECTILE_SPEED = 50.0f;
const Color EXPLOSIVE_PROJECTILE_COLOR = GOLD;
const float EXPLOSIVE_PROJECTILE_RATE = 2.0f;
const float EXPLOSIVE_ICON_ROW_OFFSET = 22.0f;
// Explosion values
const unsigned short int EXPLOSIVE_PROJECTILE_NUMBER = 8;
const unsigned short int EXPLOSIVE_PROJECTILE_EXPLOSION_RADIUS = 16;
const float EXPLOSIVE_EXPLOSIVEGUN_OFFSET = 30.0F;
const unsigned short int EXPLOSIVE_PROJECTILE_EDGE_NUMBER = 3;

// Laser gun projectiles data on fire
const unsigned short int LASER_PROJECTILE_WALL_BOUNCES_COUNT = 2;
const float LASER_PROJECTILE_RADIUS = 4.0f;
const float LASER_PROJECTILE_LIFETIME = 2.0f;
const float LASER_PROJECTILE_DAMAGE = 100.0f;
const float LASER_PROJECTILE_SPEED = 600.0f;
const Color LASER_PROJECTILE_COLOR = SKYBLUE;
const float LASER_PROJECTILE_RATE = 3.0f;
const float LASER_ICON_ROW_OFFSET = 17.0f;

// Entity
const short int ENTITY_DEFAULT_HEALTH = 100;

// Player 
const Color PLAYER_COLOR = { 40, 40, 40, 255 };
const Vector2 PLAYER_SIZE = { 32.0f, 32.0f };
const float PLAYER_SPEED = 200.0f;
const unsigned short int PLAYER_STARTING_LEVEL = 1;
const unsigned short int FIVE_LEVELS_DEBUG = 5;
// Player health bar
const Vector2 PLAYER_HEALTH_BAR_SIZE = { 32.0f, 3.0f }; // TODO Remi: change the player size and xp/health bar to 40
const Vector2 PLAYER_HEALTH_BAR_OFFSET = { 0.0f, 33.0f }; // TODO Remi: change the player size and xp/health bar to 40
const Vector2 PLAYER_SECOND_HEALTH_BAR_OFFSET = { 0.0f, 37.0f }; // TODO Remi: change the player size and xp/health bar to 40
// Experience text
const unsigned short int PLAYER_EXPERIENCE_FONT_SIZE = 15;
const Vector2 PLAYER_EXPERIENCE_TEXT_OFFSET = { 3.0f, 4.0f }; // TODO Remi: change the player size and xp/health bar to 40
// Experience bar
const Vector2 PLAYER_EXPERIENCE_BAR_SIZE = { 32.0f, 3.0f }; // TODO Remi: change the player size and xp/health bar to 40
const Vector2 PLAYER_EXPERIENCE_BAR_OFFSET = { 0.0f, -3.0f }; // TODO Remi: change the player size and xp/health bar to 40
 
// Level up bonus
const unsigned short int TEN_HEALTH_POINTS_BONUS = 10;
// Orb Experience points
const unsigned short int ORB_EXPERIENCE_POINTS = 10;

// Enemy
const short int ENEMY_DAMAGE = 10; // Enemy damage is kept outside the class to make the Enemy objects smaller in size
const Vector2 ENEMY_SIZE = { 32.0f, 32.0f };
const float ENEMY_SPEED = 100.0f; // Enemy speed  is kept outside the class to make the Enemy objects smaller in size
const Color ENEMY_DEFAULT_COLOR = BLUE;
const unsigned short int ENEMY_AMOUNT = 10;
// Enemy health bar
const Vector2 ENEMY_HEALTH_BAR_SIZE = { 32.0f, 3.0f }; // Has to be different from player's if we happen to change the player's size and no the enemy's
const Vector2 ENEMY_HEALTH_BAR_OFFSET = { 0.0f, 33.0f };
// Enemy spawner
const unsigned short int ENEMY_SPAWN_CLOSEST_THRESHOLD = 1;
const unsigned short int ENEMY_SPAWN_FARTHEST_THRESHOLD = 10;
// Enemies properties
const int MAX_ENEMY_AMOUNT_PER_LEVELS = 10;

// Camera manager 
const float CAM_ZOOM = 0.8f;
const unsigned short int SCREEN_CORNER_COUNT = 4;

// Default Menu values
const float DEFAULT_MENU_WIDTH = 400.0f;
const float DEFAULT_MENU_ROUNDNESS = 0.1f;
const unsigned short int DEFAULT_MENU_SEGMENTS = 12;
const unsigned short int DEFAULT_MENU_TITLE_FONTSIZE = 40;
const unsigned short int DEFAULT_MENU_CHOICES_FONTSIZE = 30;

// Main Menu
const float MAIN_MENU_WIDTH = 600.0f;

// Level up Menu
const float LEVELUP_MENU_HEIGHT = 700.0f;

// GameOver Menu
const float GAMEOVER_MENU_HEIGHT = 100.0f;

const std::string PRESS_ENTER_TEXT = "Press Enter to Start!";
const std::string LEVEL_UP_TEXT = "Level Up!";
const std::string SHOOTING_RATE_TEXT = "1 Shooting Rate x 2";
const std::string SHOOTING_DAMAGE_TEXT = "2 Shooting Damage x 2";
const std::string BULLET_SIZE_TEXT = "3 Projectile Size x 2";
const std::string HEALTH_CAP_TEXT = "4 Health Bonus + 10";
const std::string NEW_HAND_GUN_TEXT = "5 New HandGun";
const std::string NEW_EXPLOSIVE_GUN_TEXT = "6 New Explosive Gun";
const std::string NEW_LASER_GUN_TEXT = "7 New Laser Gun";
const std::string GAMEOVER_TEXT = "Game Over!";

// Game
const unsigned short int TARGET_FPS = 60;