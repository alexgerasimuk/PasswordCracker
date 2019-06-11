#include "Generator.h"
#include <thread>

void Generator::generateAlthabet()
{
	alphabet = alphabetLower + alphabetUpper + numerals + specialAnsi;
}

std::string Generator::publishPasswordToMain(std::queue<std::string>queue, int size)
{
	if(queue.size() < size && !passwordBucket.empty())
	{
		queue.push(passwordBucket.front());

	}
	return password;
}

void Generator::checkOneLetter(Queue queue,int maxSize, int currentSize)
{
	if (currentSize == 1)
	{
		for (int k = 0; k < alphabet.size(); k++)
		{
			password[currentSize] = alphabet[k];
			if (queue.size() < maxSize) {
				m_mutex.lock();
				queue.push(password);
				m_mutex.unlock();
			}
			else {
				while (queue.isFull != false)
				{
					// Release the lock
					m_mutex.unlock();
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					// Acquire the lock
					m_mutex.lock();
				}
				// Release the lock
				m_mutex.unlock();
			}
			if (k == alphabet.size() - 1)
				k = 0;
		}
	}
	for (int s = 0; s < currentSize; s++)
	{
		for (int r = 0; r < alphabet.size(); r++) {
			password[s] = alphabet[r];
			for (int l = 0; l < alphabet.size(); l++)
			{
				password[currentSize + 1] = alphabet[l];
				if (queue.size() < maxSize) {
					m_mutex.lock();
					queue.push(password);
					m_mutex.unlock();
				}
				else
					while (queue.isFull != false)
					{
						m_mutex.unlock();
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						m_mutex.lock();
					}
				m_mutex.unlock();

				if (l == alphabet.size() - 1)
				{
					l = 0;
					checkOneLetter(queue, maxSize, currentSize + 1);
				}
			}
		}
	}
}