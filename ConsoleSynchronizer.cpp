#include "ConsoleSynchronizer.h"
#include <iostream>

ConsoleSynchronizer::ConsoleSynchronizer()
{
}

ConsoleSynchronizer::~ConsoleSynchronizer()
{
}

void ConsoleSynchronizer::update()
{
	std::cout << console_message << std::endl;
}

void ConsoleSynchronizer::updateMessage(std::string message)
{
	this->guard.acquire();
	this->console_message += message + "\n";
	this->guard.release();
}