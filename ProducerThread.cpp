#include "ProducerThread.h"
#include "ConsoleSynchronizer.h"
#include "DataBuffer.h"
#include <random>
#include <string>

ProducerThread::ProducerThread(int id, int num_of_producers)
{
	this->id = id;
}

ProducerThread::~ProducerThread()
{
	this->id = NULL;
	this->is_running = NULL;
}

int ProducerThread::getID()
{
	return this->id;
}

void ProducerThread::run()
{
	this->is_running = true;

	DataBuffer::getInstance()->producer_semaphore->acquire();
	DataBuffer::getInstance()->mutex->acquire();

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rand(1000, 5000);

	this->sleep(rand(mt));

	std::random_device rd1;
    std::mt19937 mt1(rd1());
    std::uniform_real_distribution<double> rand1(1, 100);

	DataBuffer::getInstance()->addItem((int)rand1(mt1));

	std::string message = "Producer ";
	message += std::to_string(this->id);
	message += " successfully added item ";
	message += std::to_string((int)rand1(mt1));
	message += " to the list. List size: ";
	message += std::to_string(DataBuffer::getInstance()->getBufferSize());

	ConsoleSynchronizer::getInstance()->updateMessage(message);
	ConsoleSynchronizer::getInstance()->update();

	DataBuffer::getInstance()->mutex->release();
	DataBuffer::getInstance()->consumer_semaphore->release();

	this->is_running = false;
}