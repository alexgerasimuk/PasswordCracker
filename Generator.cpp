#include "Generator.h"
#include <thread>


void Generator::generateAlphabet()
{
	alphabet = alphabetLower;
	//+alphabetUpper + numerals;
}

void Generator::generatorWrapper(int maxQueueSize, std::atomic_bool& success)
{
	int size = 1;
	while(!success)
	{
		checkNextLetter(maxQueueSize, size, 0);
		size++;
	}
}


void Generator::checkNextLetter(int maxQueueSize, int passwordLenght, int currentIndex)
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
				checkNextLetter(maxQueueSize, passwordLenght, newIndex);
			}
		}
		else
		{
			while(queue.isFull())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			queue.push(password);
		}
	}
}

Generator::Generator(Queue& queue) : password(4, ' '), queue(queue)
{
	generateAlphabet();
}
