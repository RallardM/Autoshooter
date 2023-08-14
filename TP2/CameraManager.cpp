#include <raylib.h>

#include "CameraManager.h"
#include "MathUtils.h"

CameraManager* CameraManager::_Instance = 0;

CameraManager* CameraManager::GetInstance()
{
    if (_Instance == nullptr || NULL)
    {
        _Instance = new CameraManager();
    }
    return _Instance;
}

CameraManager::~CameraManager()
{
    if(m_camera != nullptr || NULL)
	{
		delete m_camera;
		m_camera = nullptr;
	}

    // Keep _Instance check at the end
    if (_Instance != nullptr || NULL)
    {
        delete _Instance;
        _Instance = nullptr;
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
