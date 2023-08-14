#include <raylib.h>

#include "CameraManager.h"
#include "MathUtils.h"
#include "Game.h"

CameraManager* CameraManager::_Instance = 0;

CameraManager* CameraManager::GetInstance()
{
    if (_Instance == nullptr)
    {
        _Instance = new CameraManager();
    }
    return _Instance;
}

CameraManager::~CameraManager()
{
    if(m_camera != nullptr)
	{
		delete m_camera;
		m_camera = nullptr;
	}
}

void CameraManager::InitializeCamera()
{
    // Initialize camera
    m_camera = new Camera2D();
    m_camera->offset = { (float)CAMERA_WIDTH * HALF, (float)CAMERA_HEIGHT * HALF };
    m_camera->rotation = 0.0f;
    m_camera->zoom = 0.8f;
}

void CameraManager::UpdateCameraPosition(Vector2 playerPosition)
{
    m_camera->target = { playerPosition.x, playerPosition.y };
}

const float CameraManager::GetCameraLeftLimit()
{
    Vector2 screenLeftBorderPosition = { 0.0f, ((float)GetScreenHeight()) / 2.0f };
    return GetScreenToWorld2D(screenLeftBorderPosition, *m_camera).x;
}

const float CameraManager::GetCameraTopLimit()
{
    Vector2 screenTopBorderPosition = { ((float)GetScreenWidth()) / 2.0f, 0.0f };
    return GetScreenToWorld2D(screenTopBorderPosition, *m_camera).y;
}

const float CameraManager::GetCameraRightLimit()
{
    Vector2 screenRightBorderPosition = { (float)GetScreenWidth(), ((float)GetScreenHeight()) / 2.0f };
    return GetScreenToWorld2D(screenRightBorderPosition, *m_camera).x;
}

const float CameraManager::GetCameraBottomLimit()
{
    Vector2 screenBottomBorderPosition = { ((float)GetScreenWidth()) / 2.0f, (float)GetScreenHeight() };
    return GetScreenToWorld2D(screenBottomBorderPosition, *m_camera).y;
}

const float CameraManager::GetMovingCameraLeftLimit()
{
    Vector2 screenLeftBorderPosition = { 0.0f, ((float)GetScreenHeight()) / 2.0f };
    Vector2 worldPosition = GetScreenToWorld2D(screenLeftBorderPosition, *m_camera);

    Vector2 playerPosition = Game::GetInstance()->GetPlayerPosition();
    Vector2 playerPosOnScreen = GetWorldToScreen2D(playerPosition, *m_camera);
    Vector2 cameraOffset = m_camera->offset;
    Vector2 camOffsetAndZoom = { cameraOffset.x / m_camera->zoom, cameraOffset.y / m_camera->zoom };

    return worldPosition.x + camOffsetAndZoom.x;
}

const float CameraManager::GetMovingCameraTopLimit()
{
    Vector2 screenTopBorderPosition = { ((float)GetScreenWidth()) / 2.0f, 0.0f };
    Vector2 worldPosition = GetScreenToWorld2D(screenTopBorderPosition, *m_camera);
    Vector2 cameraOffset = m_camera->offset;
    Vector2 camOffsetAndZoom = { cameraOffset.x / m_camera->zoom, cameraOffset.y / m_camera->zoom };

    return worldPosition.y + camOffsetAndZoom.y;
}

const float CameraManager::GetMovingCameraRightLimit()
{
    Vector2 screenRightBorderPosition = { (float)GetScreenWidth(), ((float)GetScreenHeight()) / 2.0f };
    Vector2 worldPosition = GetScreenToWorld2D(screenRightBorderPosition, *m_camera);
    Vector2 cameraOffset = m_camera->offset;
    Vector2 camOffsetAndZoom = { cameraOffset.x / m_camera->zoom, cameraOffset.y / m_camera->zoom };

    return worldPosition.x + camOffsetAndZoom.x;
}

const float CameraManager::GetMovingCameraBottomLimit()
{
    Vector2 screenBottomBorderPosition = { ((float)GetScreenWidth()) / 2.0f, (float)GetScreenHeight() };
    Vector2 worldPosition = GetScreenToWorld2D(screenBottomBorderPosition, *m_camera);
    Vector2 cameraOffset = m_camera->offset;
    Vector2 camOffsetAndZoom = { cameraOffset.x / m_camera->zoom, cameraOffset.y / m_camera->zoom };

    return worldPosition.y + camOffsetAndZoom.y;
}
