// cars.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Car.h"

int main()
{
	/*Car car1();
	Car* Car2();
	CarPtr car1(new Car("NewCoreCar"));*/
	
	/*auto car1 = std::make_shared<Car>("NewCoreCar");

	car1->CreateCompnent<ComponentEngine>("NewCoreEngine", 10.0f, 10.0f, 10.0f);
	car1->CreateCompnent<ComponentOilTank>("NewCoreOilTank", 5.0f, 5.0f);
	car1->CreateCompnent<ComponentTire>("NewCoreTire", 2.0f, 2.0f, 2.0f);*/

	std::vector<std::shared_ptr<Car>> cars;

	struct EngineParameter
	{
		float weight;
		float power;
		float consumerate;
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

	std::vector<EngineParameter> EngineParam = 
	{ 
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	};
	std::vector<OilTankParameter> OilTankParam =
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	};
	std::vector<TireParameter> TireParam =
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	};

	for (int i = 0; i < 10; ++i)
	{
		auto car1 = std::make_shared<Car>("NewCoreCar");

		car1->CreateCompnent<ComponentEngine>("NewCoreEngine", EngineParam[i].weight, EngineParam[i].power, EngineParam[i].consumerate);
		car1->CreateCompnent<ComponentOilTank>("NewCoreOilTank", OilTankParam[i].weight, OilTankParam[i].capacity);
		car1->CreateCompnent<ComponentTire>("NewCoreTire", TireParam[i].weight, TireParam[i].frictional, TireParam[i].dura);

		cars.push_back(car1);
	}
}


//auto count = car1.use_count();
	//std::cout << count << std::endl;

	///*std::shared_ptr<Car> c2(car1.get());
	//count = car1.use_count();
	//std::cout << count << std::endl;*/
	//{
	//	std::shared_ptr<Car> c3 = car1;
	//	count = car1.use_count();
	//	std::cout << count << std::endl;
	//}
	//count = car1.use_count();
	//std::cout << count << std::endl;

	/*car1->AddComponent(ComponentPtr(new ComponentEngine("NewCoreEngine", car1, 10.0f, 10.0f, 10.0f)));
	car1->AddComponent(ComponentPtr(new ComponentOilTank("NewCoreOilTank", car1, 5.0f, 5.0f)));
	car1->AddComponent(ComponentPtr(new ComponentTire("NewCoreTire", car1, 2.0f, 2.0f, 2.0f)));*/
