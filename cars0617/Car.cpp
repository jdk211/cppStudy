#include "Car.h"
#include <iostream>
#include <algorithm>
#include <numeric>

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
		[componentName, this](const ComponentPtr& l)
		{
			m_fWeight = CalculateWeight();
			return l->GetName() == componentName;
		}
	);



	// 1
	//for (auto& it:m_vecComponents)
	//{
	//	if ((it)->GetName() == componentName)
	//	{
	//		m_vecComponents.erase(it);
	//		break;
	//	}
	//}
}

//struct WeightOp
//{
//	float operator()(float&& init, const ComponentPtr& comp) 
//	{
//		return init + comp->GetWeight();
//	}
//};

float Car::CalculateWeight() const
{
	// 기존 반복문
	//float result = 0.0f;
	/*for (const auto& comp : m_vecComponents)
	{
		result += comp->GetWeight();
	}*/

	//struct를 사용한 반복문
	//return std::accumulate(m_vecComponents.begin(), m_vecComponents.end(), 0.0f, WeightOp());

	//lambda를 사용한 반복문
	return std::accumulate(m_vecComponents.begin(), m_vecComponents.end(), 0.0f, 
		[](float&& init, const ComponentPtr& comp)->float { return init + comp->GetWeight(); }
		);

	//return result;
}

ComponentPtr& Car::FindComponent(const std::string name)
{
	auto it = std::find_if(m_vecComponents.begin(), m_vecComponents.end(),
		[](const ComponentPtr& comp)->bool
		{
			return comp->GetName() == "NewCoreEngine";
		}
	);

	if (it != m_vecComponents.end())
	{
		//ComponentPtr -> Component*
		//it -> Component
		// = copy operator
		//ComponentPtr& comp = *it;

		return *it;
	}
	//return ComponentPtr();
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

	/*auto it = std::find_if(m_vecComponents.begin(), m_vecComponents.end(),
		[](const ComponentPtr& comp)->bool
		{
			return comp->GetName() == "NewCoreEngine";
		}
	);

	if (it != m_vecComponents.end())
	{
		ComponentPtr& comp = *it;
		static_cast<ComponentEngine*>(comp.get())->
	}*/

	m_fCurrentMoveDistance += m_fCurrentSpeed * Delta;
}

void ComponentEngine::Update(float Delta)
{
	auto weight = GetOwner()->GetWeight();

	auto accel = m_fMaxHorsePower / weight;

	auto newSpeed = GetOwner()->GetCurrentSpeed() + accel * Delta;
	if (newSpeed > m_fMaxSpeed)
	{
		newSpeed = m_fMaxSpeed;
	}
		
	GetOwner()->SetCurrentSpeed(newSpeed);

	//std::cout << newSpeed << std::endl;
}
