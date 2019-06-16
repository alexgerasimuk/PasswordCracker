#include "Generator.h"
#include <thread>


void Generator::generateAlphabet()
{
	alphabet = alphabetLower;
	//+alphabetUpper + numerals;
}

void Generator::generatorWrapper(Queue& queue, int maxQueueSize, std::atomic_bool& success)
{
	int size = 1;
	while(!success)
	{
		checkNextLetter(queue, maxQueueSize, size, 0);
		size++;
	}
}


void Generator::checkNextLetter(Queue& queue, int maxQueueSize, int passwordLenght, int currentIndex)
{
	for(unsigned int i = 0; i < alphabet.length(); i++)
	{
		password[currentIndex] = alphabet[i];
		if(queue.size() < maxQueueSize)
		{
			if ((passwordLenght - 1) == currentIndex)
			{
				queue.push(password);
			}
			else
			{
				int newIndex = currentIndex + 1;
				checkNextLetter(queue, maxQueueSize, passwordLenght, newIndex);
			}
		}
		else
		{
			while(queue.isFull)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			queue.push(password);
		}
	}
}

Generator::Generator() : password(4, ' ')
{
	generateAlphabet();
}
