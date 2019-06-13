#pragma once
#include <queue>
#include <atomic>
#include <mutex>


class Queue
{
public:
	std::queue<std::string> queue;
	int maxSize;

	std::atomic_bool isFull;
	std::atomic_bool isLastOne;
	std::mutex m_mutex;

	Queue(int size);
	std::queue<std::string> getQueue();
	int size();
	std::string back();
	std::string front();
	void push(std::string tmp);
	void pop();
	bool empty();
};
