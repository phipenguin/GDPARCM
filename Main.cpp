#include "ProducerThread.h"
#include "ConsumerThread.h"
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