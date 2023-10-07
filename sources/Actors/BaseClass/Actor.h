#pragma once

#include <list>
#include <memory>

class Actor: public std::enable_shared_from_this<Actor>
{
private:
	std::list<std::shared_ptr<class ComponentBase>> Components;

	MyVector2 Location;
	MyVector2 Rotation;
	
public:
	virtual ~Actor(){}

	void AddComponent(std::shared_ptr<ComponentBase> Component);
	void RemoveComponent(std::shared_ptr<ComponentBase> Component);
	const std::list<std::shared_ptr<ComponentBase>>& GetAllComponents() const;

	virtual void Update(float Tick);
	virtual void Draw() = 0;
};

