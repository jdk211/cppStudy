// cars.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>
#include "Car.h"

using namespace std::chrono_literals;

int main()
{
	/*Car car1();
	Car* Car2();
	CarPtr car1(new Car("NewCoreCar"));*/
	
	/*auto car1 = std::make_shared<Car>("NewCoreCar");

	car1->CreateCompnent<ComponentEngine>("NewCoreEngine", 10.0f, 10.0f, 10.0f);
	car1->CreateCompnent<ComponentOilTank>("NewCoreOilTank", 5.0f, 5.0f);
	car1->CreateCompnent<ComponentTire>("NewCoreTire", 2.0f, 2.0f, 2.0f);*/

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

	std::vector<EngineParameter> EngineParam = 
	{ 
		{ 10.0f, 150.0f, 1.5f, 100.0f},
		{ 11.0f, 200.0f, 2.0f, 110.0f},
		{ 12.0f, 250.0f, 2.5f, 90.0f},
		{ 13.0f, 150.0f, 1.5f, 80.0f},
		{ 15.0f, 200.0f, 2.0f, 120.0f},
		{ 16.0f, 250.0f, 2.5f, 100.0f},
		{ 17.0f, 150.0f, 1.5f, 110.0f},
		{ 18.0f, 200.0f, 2.0f, 90.0f},
		{ 19.0f, 250.0f, 2.5f, 80.0f},
		{ 20.0f, 300.0f, 3.0f, 120.0f},
	};
	std::vector<OilTankParameter> OilTankParam =
	{
		{ 1.0f, 1000.0f },
		{ 1.0f, 2000.0f },
		{ 1.0f, 3000.0f },
		{ 1.0f, 4000.0f },
		{ 1.0f, 5000.0f },
		{ 1.0f, 6000.0f },
		{ 1.0f, 7000.0f },
		{ 1.0f, 8000.0f },
		{ 1.0f, 9000.0f },
		{ 1.0f, 10000.0f },
	};
	std::vector<TireParameter> TireParam =
	{
		{ 1.0f, 1.0f, 1.0f },
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

	std::vector<std::shared_ptr<Car>> cars;
	const int MaxCars = 10;

	for (int i = 0; i < MaxCars; ++i)
	{
		std::stringstream ss;
		ss << "NewCoreCar" << i;
		auto car1 = std::make_shared<Car>(ss.str());

		car1->CreateCompnent<ComponentEngine>("NewCoreEngine", EngineParam[i].weight, EngineParam[i].power, EngineParam[i].consumerate, EngineParam[i].maxspeed);
		car1->CreateCompnent<ComponentOilTank>("NewCoreOilTank", OilTankParam[i].weight, OilTankParam[i].capacity);
		car1->CreateCompnent<ComponentTire>("NewCoreTire", TireParam[i].weight, TireParam[i].frictional, TireParam[i].dura);
		car1->Reset();

		cars.push_back(car1);
	}
	
	const float trackDistance = 100.0f;
	std::vector<int> Standings;
	std::thread car_update_thread[MaxCars];
	std::mutex mutex_standing;
	
	auto thread_function = [trackDistance, &Standings, &mutex_standing](CarPtr car, int index)
	{
		auto beforeTick = std::chrono::high_resolution_clock::now();
		while (true)
		{
			auto currentTick = std::chrono::high_resolution_clock::now();
			if (car->GetCurrentMoveDistance() < trackDistance)
			{
				auto perTick = std::chrono::duration_cast<std::chrono::duration<float>>(currentTick - beforeTick).count();
				car->Update(perTick);
				beforeTick = currentTick;
			}
			else
			{
				std::lock_guard<std::mutex> l(mutex_standing);
				auto it = std::find(Standings.begin(), Standings.end(), index);
				if (it == Standings.end())
				{
					Standings.push_back(index);
					std::cout << Standings.size() << " : car number " << index << std::endl;
				}

				return;
			}

			std::this_thread::sleep_for(16ms);
		}
	};

	for (int i = 0; i < MaxCars; ++i)
	{
		car_update_thread[i] = std::thread(thread_function, cars[i], i);
	}

	for (int i = 0; i < MaxCars; ++i)
	{
		car_update_thread[i].join();
	}

	/*auto beforeTick = std::chrono::high_resolution_clock::now();
	while (Standings.size() != cars.size())
	{
		auto currentTick = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < MaxCars; ++i)
		{
			if (cars[i]->GetCurrentMoveDistance() < trackDistance)
			{
				cars[i]->Update(std::chrono::duration_cast<std::chrono::milliseconds>(currentTick - beforeTick).count() / 1000.0f);
				beforeTick = currentTick;
			}
			else
			{
				auto it = std::find(Standings.begin(), Standings.end(), i);
				if (it == Standings.end())
				{
					Standings.push_back(i);
					std::cout << Standings.size() << " : car number " << i << std::endl;
				}
			}
		}
	}*/

	std::cout << "Race End" << std::endl;

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
