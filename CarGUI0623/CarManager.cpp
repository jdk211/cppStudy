#include "CarManager.h"
#include "Car.h"
#include <iostream>
#include <mutex>

using namespace std::chrono_literals;

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

CarManager::CarManager(int nMaxCar)
{
	for (int i = 0; i < nMaxCar; ++i)
	{
		std::stringstream ss;
		ss << "NewCoreCar" << i;
		auto car1 = std::make_shared<Car>(ss.str());

		car1->CreateCompnent<ComponentEngine>("NewCoreEngine", EngineParam[i].weight, EngineParam[i].power, EngineParam[i].consumerate, EngineParam[i].maxspeed);
		car1->CreateCompnent<ComponentOilTank>("NewCoreOilTank", OilTankParam[i].weight, OilTankParam[i].capacity);
		car1->CreateCompnent<ComponentTire>("NewCoreTire", TireParam[i].weight, TireParam[i].frictional, TireParam[i].dura);
		car1->Reset();

		m_vecCars.push_back(car1);
	}
}

CarManager::~CarManager()
{
}

unsigned int Thread_Function(CarPtr car, size_t index, float TrackDistance, std::vector<int>& Standings)
{
	static std::mutex mutex_standing;
	auto beforeTick = std::chrono::high_resolution_clock::now();
	while (true)
	{
		auto currentTick = std::chrono::high_resolution_clock::now();
		if (car->GetCurrentMoveDistance() < TrackDistance)
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

			return 0;
		}

		std::this_thread::sleep_for(16ms);
	}

	return 0;
}

void CarManager::Run()
{
	for (size_t i = 0; i < m_vecCars.size(); ++i)
	{
		std::thread t = std::thread(Thread_Function, m_vecCars[i], i, m_fTrackDistance, std::ref(m_vecStandings));
		car_update_thread.emplace_back(std::move(t));
	}

	for (auto& thread : car_update_thread)
	{
		thread.join();
	}
}

