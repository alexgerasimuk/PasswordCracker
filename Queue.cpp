#include "Queue.h"

Queue::Queue(int size)
{
	maxSize = size;
	isFull = false;
	isLastOne = true;
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
    std::lock_guard<std::mutex> lock(m_mutex);
	return queue.front();
}

void Queue::push(std::string tmp)
{
    std::lock_guard<std::mutex> lock(m_mutex);
	if (queue.size() < maxSize)
	{
		queue.push(tmp);
		if(queue.size() > 1)
		{
			isLastOne = false;
		}
	}
	else
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		this->isFull = true;
	}
}

void Queue::pop()
{
    std::lock_guard<std::mutex> lock(m_mutex);
	if (queue.back() != queue.front())
	{
		queue.pop();
		isFull = false;
	}
	else
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		isLastOne = true;
	}
}

bool Queue::empty()
{
	return queue.empty();
}
