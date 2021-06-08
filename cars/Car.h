#pragma once
#include<memory>
#include<vector>
#include<string>

class Car;

class Component
{
public:
	Component(const std::string& name, std::shared_ptr<Car> owner)
		: m_strName(name)
		, Owner(owner)
	{

	};
	~Component() {};

private:
	std::shared_ptr<Car> Owner;
	std::string m_strName;

public:
	std::shared_ptr<Car> GetOwner() { return Owner; }
	std::string GetName() { return m_strName; }
};


class Car
{
public:
	Car(const std::string& name)
		: m_strName(name)
	{
	};

private:
	std::string m_strName;
	std::vector<std::unique_ptr<Component>> m_vecComponents;

public:
	void AddComponent(std::unique_ptr<Component> comp);
	void RemoveComponent(const std::string& componentName);

	std::string GetName() { return m_strName; }



	/*float MaxSpeed;
	float MaxAcceleration;
	float MaxBreakForce;
	float SteeringForce;
	float Durability;*/

};




//shared_ptr, unique_ptr
//const std::string& ������ ������
//����... �̵�... 
//����... �̸����� �Լ� [](){}

// 2 ������ �Ķ���ʹ� pred ����..? ����ü���� ���������ϴ� ��Ȳ�� �߻�
//std::remove_if(m_vecComponents.begin(), m_vecComponents.end(), ComponentNameEqual(componentName));
