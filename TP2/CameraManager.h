#pragma once
#include "MathUtils.h"

class CameraManager
{
	friend class Game;
	friend class Player;
	friend class Enemy;
	friend class MenuManager;
	friend class Projectile;

private:
	static CameraManager* _Instance;
	Camera2D* m_camera = nullptr;

	const int CAMERA_WIDTH = 1200;
	const int CAMERA_HEIGHT = 800;

public:
	static CameraManager* GetInstance();
	~CameraManager();

private:
	CameraManager() {} // Private constructor for singleton pattern

	void InitializeCamera();

	// Camera size fields
	Camera2D* GetCamera() { return m_camera; }
	const float GetCameraWidth() const { return (float)CAMERA_WIDTH; }
	const float GetCameraHeight() const { return (float)CAMERA_HEIGHT; }
	const float GetTransformedCameraWidth() const { return (float)CAMERA_WIDTH * m_camera->zoom; }
	const float GetTransformedCameraHeight() const { return (float)CAMERA_HEIGHT * m_camera->zoom; }

	// Camera2D position fields
	void UpdateCameraPosition(Vector2 playerPosition);
	const Vector2 GetCameraPosition() { return m_camera->target; }
	const Vector2 GetCameraOffset() { return m_camera->offset; }
	const Vector2 GetCameraTopLeftCorner() { return { GetCameraLeftLimit(), GetCameraTopLimit() }; }
	const float GetCameraZoom() { return m_camera->zoom; }

	// Camera limits 
	const float GetCameraLeftLimit();
	const float GetCameraTopLimit();
	const float GetCameraRightLimit();
	const float GetCameraBottomLimit();

	// Camera limits with moving camera
	const float GetMovingCameraLeftLimit();
	const float GetMovingCameraTopLimit();
	const float GetMovingCameraRightLimit();
	const float GetMovingCameraBottomLimit();
};

