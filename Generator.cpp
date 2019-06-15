#include "Generator.h"
#include <thread>


void Generator::generateAlphabet()
{
	alphabet = alphabetLower;
	//+alphabetUpper + numerals;
}

void Generator::generatorWrapper(Queue& queue, int maxQueueSize, std::mutex& m_mutex, std::atomic_bool& success)
{
	int size = 1;
	while(!success)
	{
//	for(int i = 0;i<4; i++){
		checkNextLetter(queue, maxQueueSize, size, 0, m_mutex);
		size++;
	}
}


void Generator::checkNextLetter(Queue& queue, int maxQueueSize, int passwordLenght, int currentIndex, std::mutex& m_mutex)
{
	for(unsigned int i = 0; i < alphabet.length(); i++)
	{
		password[currentIndex] = alphabet[i];
		if(queue.size() < maxQueueSize)
		{
			if ((passwordLenght - 1) == currentIndex)
			{
				m_mutex.lock();
				queue.push(password);
				m_mutex.unlock();
			}
			else
			{
				int newIndex = currentIndex + 1;
				checkNextLetter(queue, maxQueueSize, passwordLenght, newIndex, m_mutex);
			}
		}
		else
		{
			while(queue.isFull)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			m_mutex.lock();
			queue.push(password);
			m_mutex.unlock();
		}
	}
}

Generator::Generator() : password(4, ' ')
{
	generateAlphabet();
}
