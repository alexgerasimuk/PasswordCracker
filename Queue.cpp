#include "Queue.h"

Queue::Queue(int size)
{
	this->maxSize = size;
	this->isFull = false;
}

std::queue<std::string> Queue::getQueue()
{
	return queue;
}

int Queue::size()
{
	return queue.size();
}

std::string Queue::back()
{
	return queue.back();
}

std::string Queue::front()
{
	return queue.front();
}

void Queue::push(std::string tmp)
{
	if (queue.size() < maxSize) {
		queue.push(tmp);
	}
	else {
		std::lock_guard<std::mutex> guard(m_mutex);
		this->isFull = true;
	}
}

void Queue::pop()
{
	if (queue.back() != queue.front()){
		queue.pop();
	}
	else {
		std::lock_guard<std::mutex> guard(m_mutex);
		isLastOne = true;
	}
}

bool Queue::empty()
{
	return queue.empty();
}
