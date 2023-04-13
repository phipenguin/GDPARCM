#include "ConsumerThread.h"
#include "ConsoleSynchronizer.h"
#include "DataBuffer.h"
#include <random>
#include <string>

ConsumerThread::ConsumerThread(int id)
{
	this->id = id;
}

ConsumerThread::~ConsumerThread()
{
}

int ConsumerThread::getID()
{
	return this->id;
}

void ConsumerThread::run()
{
	this->is_running = true;

	DataBuffer::getInstance()->consumer_semaphore->acquire();
	DataBuffer::getInstance()->mutex->acquire();

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rand(1000, 5000);

	this->sleep(rand(mt));

	DataBuffer::getInstance()->consumeItem();

	std::string message = "Consumer ";
	message += std::to_string(this->id);
	message += " consumed an item from the list. List size: ";
	message += std::to_string(DataBuffer::getInstance()->getBufferSize());

	ConsoleSynchronizer::getInstance()->updateMessage(message);
	ConsoleSynchronizer::getInstance()->update();

	DataBuffer::getInstance()->mutex->release();
	DataBuffer::getInstance()->producer_semaphore->release();

	this->is_running = false;
}