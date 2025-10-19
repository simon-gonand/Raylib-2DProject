#include "CameraManager.h"

std::shared_ptr<CameraManager> CameraManager::Instance;

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
	UnregisterAllCameraComponents();
}

std::shared_ptr<CameraManager> CameraManager::Get()
{
	if (!Instance)
		Instance.reset(new CameraManager());

	return Instance;
}

void CameraManager::RegisterCameraComponent(std::shared_ptr<CameraComponent> CameraComponentToRegister)
{
	CameraComponents.insert(CameraComponents.begin(), CameraComponentToRegister);
}

void CameraManager::UnregisterCameraComponent(std::shared_ptr<CameraComponent> CameraComponentToUnregister)
{
	std::vector<std::shared_ptr<CameraComponent>>::iterator ToUnregister = std::find(CameraComponents.begin(), CameraComponents.end(), CameraComponentToUnregister);
	if(ToUnregister != CameraComponents.end())
		CameraComponents.erase(ToUnregister);
}

void CameraManager::UnregisterAllCameraComponents()
{
	CameraComponents.empty();
}

void CameraManager::UseCamera(std::shared_ptr<CameraComponent> CameraComponentToUse)
{
	std::vector<std::shared_ptr<CameraComponent>>::iterator CameraToUse = std::find(CameraComponents.begin(), CameraComponents.end(), CameraComponentToUse);
	if(CameraToUse != CameraComponents.end())
		std::rotate(CameraComponents.begin(), CameraToUse, CameraToUse + 1);
}

const Camera2D CameraManager::GetCameraToUse() const
{
	if (CameraComponents.size() > 0) 
	{
		if (CameraComponents[0]) {
			return CameraComponents[0]->GetCamera();
		}
	}
	return Camera2D();
}
