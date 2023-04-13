#pragma once
#include <vector>

class DataBuffer
{
public:
	static DataBuffer* getInstance();

	void addItem();
	void consumerItem();

private:
	DataBuffer(){};

	std::vector<int> buffer;
};