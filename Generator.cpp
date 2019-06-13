#include "Generator.h"
#include <thread>
#include <iostream>

void Generator::generateAlphabet()
{
	alphabet = alphabetLower;
	//+alphabetUpper + numerals;
}

void Generator::checkOneLetter(Queue& queue, int maxSize, int currentSize, std::mutex& m_mutex)
{
	if (currentSize == 1)
	{
		for (auto k = 0; k < alphabet.length(); k++)
		{
			std::cout << alphabet[k];
			password[currentSize - 1] = alphabet.at(k);
			m_mutex.lock();
			if (queue.size() < maxSize)
			{
				queue.push(password);
				m_mutex.unlock();
			}
			else
			{
				while (queue.isFull == true)
				{
					// Release the lock
					m_mutex.unlock();
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					// Acquire the lock
					m_mutex.lock();
				}
				queue.push(password);
				m_mutex.unlock();
			}
			// Release the lock


			if (k == alphabet.size() - 1)
				k = 0;
		}
	}

	for (int s = 0; s < currentSize; s++)
	{
		for (auto letterPosition = 0; letterPosition < alphabet.length(); letterPosition++)
		{
			password[s] = alphabet[letterPosition];
			for (auto l = 0; l < alphabet.length(); l++)
			{
				password[currentSize + 1] = alphabet[l];
				if (queue.size() < maxSize)
				{
					m_mutex.lock();
					queue.push(password);
					m_mutex.unlock();
				}
				else
					while (queue.isFull == true)
					{
						m_mutex.unlock();
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						m_mutex.lock();
						queue.push(password);
					}
				m_mutex.unlock();

				if (l == alphabet.size() - 1)
				{
					l = 0;
					checkOneLetter(queue, maxSize, currentSize + 1, m_mutex);
				}
			}
		}
	}
}

Generator::Generator()
{
	generateAlphabet();
}
