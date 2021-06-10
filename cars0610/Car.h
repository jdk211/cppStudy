#pragma once
#include<memory>
#include<vector>
#include<string>

class Car;
class Component;

//구식
//typedef std::unique_ptr<Component> ComponentPtr;
//typedef std::shared_ptr<Car> CarPtr;
//신식
using ComponentPtr = std::unique_ptr<Component>;
using CarPtr = std::shared_ptr<Car>;

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
	CarPtr GetOwner() { return Owner; }
	std::string GetName() { return m_strName; }

	virtual void Update(float Delta) {}
};

class ComponentEngine :public Component
{
public:
	ComponentEngine(CarPtr owner, const std::string& name, float weight, float power, float consumerate)
		: Component(owner, name, weight)
		, m_fMaxHorsePower(power)
		, m_fOilConsumeRate(consumerate)
	{

	};
	~ComponentEngine() override {};

	void Update(float Delta) override {}

private:
	float m_fMaxHorsePower;
	float m_fOilConsumeRate;

};

class ComponentOilTank : public Component
{
public:
	ComponentOilTank(CarPtr owner, const std::string& name, float weight, float capacity)
		: Component(owner, name, weight)
		, m_fMaxCapacity(capacity)
	{

	};
	~ComponentOilTank() override {};

	void Update(float Delta) override {}

private:
	float m_fMaxCapacity;
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

public:
	template<typename T, class... _Types> void CreateCompnent(_Types&&... _Args)
	{
		m_vecComponents.emplace_back(ComponentPtr(new T(shared_from_this(), _STD forward<_Types>(_Args)...)));
	}

	void RemoveComponent(const std::string& componentName);

	std::string GetName() { return m_strName; }

	void Update(float Delta);


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
