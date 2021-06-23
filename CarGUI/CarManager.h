#pragma once
#include <vector>
#include <thread>
#include <memory>

class Car;
using CarPtr = std::shared_ptr<Car>;

class CarManager
{
public:
	explicit CarManager(int nMaxCar);
	~CarManager();

	void Run();
	
private:
	std::vector<CarPtr> m_vecCars;
	const float m_fTrackDistance = 100.0f;
	
	std::vector<int> m_vecStandings;
	std::vector<std::thread> car_update_thread;
};

