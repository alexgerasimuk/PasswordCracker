#pragma once
#include <queue>
#include <atomic>
#include <mutex>


class Queue
{
public:
	Queue(int size);
	int size();
	std::string front();
	void push(std::string tmp);
	void pop();
	bool empty();
    bool isFull();

private:
    std::queue<std::string> queue;
    unsigned int maxSize;
    std::mutex m_mutex, validator_mutex;
};
