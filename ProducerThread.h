#pragma once
#include "IETThread.h"
#include <semaphore>

class ProducerThread : public IETThread
{
public:
	ProducerThread(int id, int num_of_producers);
	~ProducerThread();

	int getID();
	void run() override;

	bool is_running;

private:
	int id;
};