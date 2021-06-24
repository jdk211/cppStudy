#pragma once
#include<memory>
#include<vector>
#include<string>
#include<string_view>

class Car;
class Component;

using ComponentPtr = std::unique_ptr<Component>;
using CarPtr = std::shared_ptr<Car>;

struct EngineParameter
{
	float weight;
	float power;
	float consumerate;
	float maxspeed;
};

struct OilTankParameter
{
	float weight;
	float capacity;
};

struct TireParameter
{
	float weight;
	float frictional;
	float dura;
};

class Component
{
public:
	Component(CarPtr owner, const std::string& name,  float weight)
		: m_strName(name)
		, Owner(owner)
		, m_fWeight(weight)
	{

	};
	virtual ~Component() {};

private:
	CarPtr Owner;
	std::string m_strName;

	float m_fWeight;

public:
	CarPtr GetOwner() const { return Owner; }
	std::string GetName() const { return m_strName; }
	virtual float GetWeight() const { return m_fWeight; }
	virtual void Reset() {};
	template<typename T> T GetParameter(std::string_view name) { return T{}; };

	virtual bool GetParameterBool(std::string_view name)
	{
		throw std::exception("no such parameter");
	}
	virtual float GetParameterFloat(std::string_view name)
	{
		throw std::exception("no such parameter");
	}
	virtual int GetParameterInt(std::string_view name) 
	{
		throw std::exception("no such parameter");
	}

	virtual void Update(float Delta) {}
};

class ComponentEngine :public Component
{
public:
	ComponentEngine(CarPtr owner, const std::string& name, float weight, float power, float consumerate, float maxspeed)
		: Component(owner, name, weight)
		, m_fMaxHorsePower(power)
		, m_fOilConsumeRate(consumerate)
		, m_fMaxSpeed(maxspeed)
	{

	};
	~ComponentEngine() override {};

	void Update(float Delta) override;

	float GetConsumeRate() const { return m_fOilConsumeRate; }

	float GetParameterFloat(std::string_view name) override
	{
		if (name == "MaxHorsePower")
		{
			return m_fMaxHorsePower;
		}
		else if (name == "OilConsumeRate")
		{
			return m_fOilConsumeRate;
		}
		else if (name == "MaxSpeed")
		{
			return m_fMaxSpeed;
		}
		else
		{
			return Component::GetParameterFloat(name);
		}
	}
private:
	float m_fMaxHorsePower;
	float m_fOilConsumeRate;
	float m_fMaxSpeed;

};

class ComponentOilTank : public Component
{
public:
	ComponentOilTank(CarPtr owner, const std::string& name, float weight, float capacity)
		: Component(owner, name, weight)
		, m_fMaxCapacity(capacity)
		, m_fCurrentCapacity(capacity)
		, m_bCharging(false)
	{
	};
	~ComponentOilTank() override {};

	void Update(float Delta) override;

	float GetWeight() const override 
	{ 
		return Component::GetWeight() + m_fCurrentCapacity / 10; 
	}
	void Reset() override { m_fCurrentCapacity = m_fMaxCapacity; }
	bool IsEmpty() const { return m_fCurrentCapacity <= 0.0f; }
	bool IsCharging() const { return m_bCharging; }

	bool GetParameterBool(std::string_view name) override
	{
		if (name == "isCharging")
		{
			return m_bCharging;
		}
		else
		{
			return Component::GetParameterBool(name);
		}
	}
	float GetParameterFloat(std::string_view name) override
	{
		if (name == "MaxCapacity")
		{
			return m_fMaxCapacity;
		}
		else if (name == "CurrentCapacity")
		{
			return m_fCurrentCapacity;
		}
		else
		{
			return Component::GetParameterFloat(name);
		}
	}

private:
	float m_fMaxCapacity;
	float m_fCurrentCapacity;
	bool m_bCharging;
};

class ComponentTire : public Component
{
public:
	ComponentTire(CarPtr owner, const std::string& name, float weight, float frictional, float dura)
		:Component(owner, name, weight)
		, m_fFrictionalFactor(frictional)
		, m_fDurability(dura)
	{

	};
	~ComponentTire() override {};

	void Update(float Delta) override {}

private:
	float m_fFrictionalFactor;
	float m_fDurability;

};


class Car : public std::enable_shared_from_this<Car>
{
public:
	Car(const std::string& name)
		: m_strName(name)
	{
	};

private:
	std::string m_strName;
	std::vector<ComponentPtr> m_vecComponents;
	
	float m_fWeight = 0.0f;
	float m_fCurrentSpeed = 0.0f;
	float m_fCurrentMoveDistance = 0.0f;

public:
	void Update(float Delta);

	template<typename T, class... _Types> void CreateCompnent(_Types&&... _Args)
	{
		m_vecComponents.emplace_back(ComponentPtr(new T(shared_from_this(), _STD forward<_Types>(_Args)...)));
		m_fWeight = CalculateWeight();
	}

	void RemoveComponent(const std::string& componentName);

	float CalculateWeight() const;

	std::string GetName() const { return m_strName; }
	float GetCurrentSpeed() const { return m_fCurrentSpeed; }
	void SetCurrentSpeed(float newspeed) { m_fCurrentSpeed = newspeed; }
	float GetWeight() const
	{
		return m_fWeight;
	}
	float GetCurrentMoveDistance() const { return m_fCurrentMoveDistance; }
	void Reset() { m_fCurrentMoveDistance = 0.0f; }
	ComponentPtr& FindComponent(const std::string& name);

	/*float MaxSpeed;
	float MaxAcceleration;
	float MaxBreakForce;
	float SteeringForce;
	float Durability;*/
};



















//shared_ptr, unique_ptr
//const std::string& 무조건 쓰고보기
//복사... 이동... 
//람다... [](){}

// 2 마지막 파라미터는 pred 프레..? 구조체까지 만들어줘야하는 상황이 발생
//std::remove_if(m_vecComponents.begin(), m_vecComponents.end(), ComponentNameEqual(componentName));
