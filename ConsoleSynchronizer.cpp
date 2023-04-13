#include "ConsoleSynchronizer.h"
#include <iostream>

ConsoleSynchronizer* ConsoleSynchronizer::shared_instance = nullptr;

ConsoleSynchronizer* ConsoleSynchronizer::getInstance()
{
	if (shared_instance == nullptr) {
		shared_instance = new ConsoleSynchronizer();
	}

	return shared_instance;
}

void ConsoleSynchronizer::update()
{
	std::cout << console_message << std::endl;
}

void ConsoleSynchronizer::updateMessage(std::string message)
{
	this->guard.acquire();
	this->console_message.clear();
	this->console_message += message + "\n";
	this->guard.release();
}