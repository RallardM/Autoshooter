#pragma once
class CameraManager
{
private:
	static CameraManager* _Instance;
	Camera2D* m_camera = nullptr;

	const int CAMERA_WIDTH = 1200;
	const int CAMERA_HEIGHT = 800;

public:
	static CameraManager* GetInstance();
	~CameraManager();

	void InitializeCamera();

	void UpdateCameraPosition(Vector2 playerPosition);

	// Camera getters
	Camera2D* GetCamera() { return m_camera; }
	const float GetCameraWidth() const { return (float)CAMERA_WIDTH; }
	const float GetCameraHeight() const { return (float)CAMERA_HEIGHT; }
	const float GetTransformedCameraWidth() const { return (float)CAMERA_WIDTH * m_camera->zoom; }
	const float GetTransformedCameraHeight() const { return (float)CAMERA_HEIGHT * m_camera->zoom; }

	// Camera limits 
	const float GetCameraLeftLimit()
	{
		Vector2 screenLeftBorderPosition = { 0.0f, ((float)GetScreenHeight()) / 2.0f };
		return GetScreenToWorld2D(screenLeftBorderPosition, *m_camera).x;
	}
	const float GetCameraTopLimit()
	{
		Vector2 screenTopBorderPosition = { ((float)GetScreenWidth()) / 2.0f, 0.0f };
		return GetScreenToWorld2D(screenTopBorderPosition, *m_camera).y;
	}
	const float GetCameraRightLimit()
	{
		Vector2 screenRightBorderPosition = { (float)GetScreenWidth(), ((float)GetScreenHeight()) / 2.0f };
		return GetScreenToWorld2D(screenRightBorderPosition, *m_camera).x;
	}
	const float GetCameraBottomLimit()
	{
		Vector2 screenBottomBorderPosition = { ((float)GetScreenWidth()) / 2.0f, (float)GetScreenHeight() };
		return GetScreenToWorld2D(screenBottomBorderPosition, *m_camera).y;
	}

	const Vector2 GetCameraPosition() { return m_camera->target; }
	const Vector2 GetCameraOffset() { return m_camera->offset; }
	const Vector2 GetCameraTopLeftCorner() { return { GetCameraLeftLimit(), GetCameraTopLimit() }; }
	const float GetCameraZoom() { return m_camera->zoom; }

private:
	CameraManager() {} // Private constructor for singleton pattern
};

