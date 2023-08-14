#pragma once

enum class EWeaponType : unsigned short int
{
	HAND_GUN,
	EXPLOSIVE_GUN,
	LAZER_GUN,
	COUNT
};

enum class EGameObjectType : unsigned short int
{
	PLAYER,
	ENEMY,
	PROJECTILE,
	WEAPON,
	ORB,
	UI,
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