#pragma once
#include <queue>
#include <atomic>
#include <mutex>


class Queue
{
public:
	std::queue<std::string> queue;
	unsigned int maxSize;
	std::mutex m_mutex;

	Queue(int size);
	std::queue<std::string> getQueue();
	int size();
	std::string back();
	std::string front();
	void push(std::string tmp);
	void pop();
	bool empty();
    bool isFull();
};
