#include <thread>
#include "Queue.h"

Queue::Queue(int size)
{
	maxSize = size;
}

int Queue::size()
{
	return queue.size();
}

std::string Queue::front()
{
    std::lock_guard<std::mutex> lock_validator(validator_mutex);
    while(empty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    auto temp = queue.front();
    pop();
	return temp;
}

void Queue::pop()
{
    if (!empty())
    {
        queue.pop();
    }
}

void Queue::push(std::string tmp)
{
	while (isFull())
	{
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
    std::lock_guard<std::mutex> lock(m_mutex);
    queue.push(tmp);
}


bool Queue::empty()
{
	return queue.empty();
}

bool Queue::isFull()
{
    return queue.size() >= maxSize;
}
