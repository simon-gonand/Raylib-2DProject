#pragma once

#include <vector>
#include <memory>

#include "../../Components/Camera/CameraComponent.h"

class CameraManager 
{
private:
	static std::shared_ptr<CameraManager> Instance;
	
	std::vector<std::shared_ptr<CameraComponent>> CameraComponents;

	CameraManager();

public:
	static std::shared_ptr<CameraManager> Get();

	~CameraManager();

	CameraManager(CameraManager& InInputManager) = delete;
	void operator=(const CameraManager& InInputManager) = delete;

	void RegisterCameraComponent(std::shared_ptr<CameraComponent> CameraComponentToRegister);
	void UnregisterCameraComponent(std::shared_ptr<CameraComponent> CameraComponentToUnregister);
	void UnregisterAllCameraComponents();

	void UseCamera(std::shared_ptr<CameraComponent> CameraComponentToUse);
	const Camera2D GetCameraToUse() const;
};