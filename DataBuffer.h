#pragma once
#include <vector>
#include <semaphore>

class DataBuffer
{
public:
	DataBuffer(int num_of_producers, int num_of_consumers);
	static DataBuffer* getInstance();

	void addItem(int item);
	void consumeItem();

	int getBufferSize();

	std::counting_semaphore<>* producer_semaphore;
	std::counting_semaphore<>* consumer_semaphore;
	std::binary_semaphore* mutex;

private:
	DataBuffer(DataBuffer const&) {};
	DataBuffer& operator=(DataBuffer const&) {};
	static DataBuffer* shared_instance;

	std::vector<int> buffer;
};