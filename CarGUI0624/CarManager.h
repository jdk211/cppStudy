#pragma once
#include <memory>

class CarManager
{
public:
	explicit CarManager(int nMaxCar);
	~CarManager();

	void Run();
	bool IsThreadEnd();

private:
	class CarPimpl;
	std::unique_ptr<CarPimpl> m_pImpl;
};

