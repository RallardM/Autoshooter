#pragma once

enum class EWeaponType : unsigned short int
{
	HANDGUN,
	EXPLOSIVEGUN,
	LAZERGUN,
	COUNT
};

enum class EGameObjectType : unsigned short int
{
	PLAYER,
	ENEMY,
	PROJECTILE,
	WEAPON,
	ORB,
	UIELEMENT,
	CAMERA,
	COUNT
};

enum class EUIElementType : unsigned short int
{
	PROGRESS_BAR,
	REGRESS_BAR,
	TEXT,
	COUNT
};

enum class EUIMenuType : unsigned short int
{
	MAIN_MENU,
	LEVELUP_MENU,
	GAMEOVER_MENU,
	COUNT
};