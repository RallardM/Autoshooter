#pragma once

#include "MathUtils.h"

class CameraManager
{
	friend class GameObjectPool;
	friend class Player;
	friend class Enemy;
	friend class MenuManager;
	friend class Projectile;

	
public: // Public member variables

private: // Private member variables
	static CameraManager* _Instance;
	Camera2D* m_camera = nullptr;

	const int CAMERA_WIDTH = 1200;
	const int CAMERA_HEIGHT = 800;

public: // Public methods
	static CameraManager* GetInstance();
	~CameraManager();

private: // Private methods
	CameraManager() {} // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I

	const void InitializeCamera();

	// Camera limits 
	const float GetCameraLeftLimit() const;
	const float GetCameraTopLimit() const;
	const float GetCameraRightLimit() const;
	const float GetCameraBottomLimit() const;

	// Camera limits with moving camera
	const float GetMovingCameraLeftLimit() const;
	const float GetMovingCameraTopLimit() const;
	const float GetMovingCameraRightLimit() const;
	const float GetMovingCameraBottomLimit() const;

	// Camera size fields
	Camera2D* GetCamera() { return m_camera; }
	const float GetCameraWidth() const { return (float)CAMERA_WIDTH; }
	const float GetCameraHeight() const { return (float)CAMERA_HEIGHT; }
	const float GetTransformedCameraWidth() const { return (float)CAMERA_WIDTH * m_camera->zoom; }
	const float GetTransformedCameraHeight() const { return (float)CAMERA_HEIGHT * m_camera->zoom; }

	// Camera2D position fields
	const void UpdateCameraPosition(const Vector2 playerPosition) const;
	const Vector2 GetCameraPosition() const { return m_camera->target; }
	const Vector2 GetCameraOffset() const { return m_camera->offset; }
	const Vector2 GetCameraTopLeftCorner() const { return { GetCameraLeftLimit(), GetCameraTopLimit() }; }
	const float GetCameraZoom() const { return m_camera->zoom; }

};