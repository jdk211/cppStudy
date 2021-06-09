#include "Car.h"
#include <algorithm>

void Car::AddComponent(ComponentPtr&& comp)
{
	m_vecComponents.emplace_back(std::move(comp));
}

// 2
//struct ComponentNameEqual
//{
//public:
//	ComponentNameEqual(const std::string& name)
//		:m_strName(name)
//	{
//	};
//
//private:
//	std::string m_strName;
//
//public:
//	bool operator()(const std::unique_ptr<Component>& l)
//	{
//		return l->GetName() == m_strName;
//	}
//};

void Car::RemoveComponent(const std::string& componentName)
{
	// 2
	//std::remove_if(m_vecComponents.begin(), m_vecComponents.end(), ComponentNameEqual(componentName));

	auto it = std::remove_if(m_vecComponents.begin(), m_vecComponents.end(), 
		[componentName](const ComponentPtr& l)
		{
			return l->GetName() == componentName;
		}
	);

	// 1
	//for (auto& it:m_vecComponents)
	//{
	//	if ((it)->GetName() == componentName)
	//	{
	//		m_vecComponents.erase_if(it);
	//		break;
	//	}
	//}
}

void Car::Update(float Delta)
{
	/*for (auto it = m_vecComponents.begin(); it != m_vecComponents.end(); ++it)
	{
		(*it)->Update(Delta);
	}*/

	for (auto& comp : m_vecComponents)
	{
		comp->Update(Delta);
	}
}
