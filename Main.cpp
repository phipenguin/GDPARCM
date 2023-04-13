#include "ProducerThread.h"
#include "ConsumerThread.h"
#include "DataBuffer.h"
#include <iostream>
#include <vector>

int main()
{

	int num_of_producer;
	std::vector<ProducerThread*> producer_threads;

	int num_of_consumer;
	std::vector<ConsumerThread*> consumer_threads;

	std::cout << "Enter the number of producers: ";
	std::cin >> num_of_producer;

	std::cout << "Enter the number of consumers: ";
	std::cin >> num_of_consumer;

	DataBuffer* data_buffer = new DataBuffer(num_of_producer, num_of_consumer);

	for (int p = 0; p < num_of_producer; p++)
	{
		ProducerThread* producer_thread = new ProducerThread(p, num_of_producer);
		producer_thread->start();

		producer_threads.push_back(producer_thread);
	}

	for (int c = 0; c < num_of_consumer; c++)
	{
		ConsumerThread* consumer_thread = new ConsumerThread(c);
		consumer_thread->start();

		consumer_threads.push_back(consumer_thread);
	}

	bool standby = true;

	while(standby)
	{
		for (int p = 0; p < num_of_producer; p++)
		{
			standby = false;

			if (producer_threads[p]->is_running)
			{
				standby = true;
				break;
			}
		}

		for (int c = 0; c < num_of_consumer; c++)
		{
			standby = false;

			if (consumer_threads[c]->is_running)
			{
				standby = true;
				break;
			}
		}
	}

	return 0;
}