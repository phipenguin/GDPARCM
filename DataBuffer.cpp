#include "DataBuffer.h"

DataBuffer* DataBuffer::shared_instance = nullptr;

DataBuffer* DataBuffer::getInstance()
{
	return shared_instance;
}

void DataBuffer::addItem(int item)
{
	buffer.push_back(item);
}

void DataBuffer::consumeItem()
{
	buffer.pop_back();
}

int DataBuffer::getBufferSize()
{
	return buffer.size();
}

DataBuffer::DataBuffer(int num_of_producers, int num_of_consumers)
{
	this->producer_semaphore = new std::counting_semaphore<>(num_of_producers);
	this->consumer_semaphore = new std::counting_semaphore<>(num_of_consumers);
	this->mutex = new std::binary_semaphore(1);

	shared_instance = this;
}