#pragma once
#include <string>
#include <semaphore>

class ConsoleSynchronizer
{
public:
	static ConsoleSynchronizer* getInstance();

	void update();
	void updateMessage(std::string message);

private:
	ConsoleSynchronizer() {};
	ConsoleSynchronizer(ConsoleSynchronizer const&) {};
	ConsoleSynchronizer& operator=(ConsoleSynchronizer const&) {};
	static ConsoleSynchronizer* shared_instance;

	std::binary_semaphore guard{1};
	std::string console_message;
};