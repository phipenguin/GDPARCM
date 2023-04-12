#pragma once
#include <string>
#include <semaphore>

class ConsoleSynchronizer
{
public:
	ConsoleSynchronizer();
	~ConsoleSynchronizer();

	void update();
	void updateMessage(std::string message);

private:
	std::binary_semaphore guard;
	std::string console_message;
};