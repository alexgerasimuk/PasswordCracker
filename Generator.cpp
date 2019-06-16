#include "Generator.h"
#include <thread>


void Generator::generateAlphabet()
{
    alphabet = alphabetLower + alphabetUpper + numerals + specialAnsi;
}

void Generator::generatorWrapper()
{
	int size = 1;
	while(!success)
	{
        password.resize(size);
		checkNextLetter(size, 0);
		size++;
	}
}


void Generator::checkNextLetter(int passwordLength, int currentIndex)
{
	for(unsigned int i = 0; i < alphabet.length(); i++)
	{
        if(success)
        {
            return;
        }
		password[currentIndex] = alphabet[i];
		if(queue.size() < maxQueueSize)
		{
			if ((passwordLength - 1) == currentIndex)
			{
				queue.push(password);
			}
			else
			{
				int newIndex = currentIndex + 1;
				checkNextLetter(passwordLength, newIndex);
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

Generator::Generator(Queue& queue, int maxQueueSize, std::atomic_bool& success)
    : queue(queue), maxQueueSize(maxQueueSize), success(success)
{
	generateAlphabet();
}
