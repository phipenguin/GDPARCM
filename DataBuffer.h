#pragma once
#include <vector>

class DataBuffer
{
public:
	DataBuffer();
	~DataBuffer();

	void addItem();
	void consumerItem();

private:
	std::vector<int> buffer;
};