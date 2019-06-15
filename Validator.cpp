#include "Validator.h"
#include <iostream>

Validator::Validator(std::string password){
	this->password = password;
}

void Validator::validate(Queue& passwordsQueue, std::atomic_bool& success, std::mutex& m_mutex, std::string &foundPassword)
{
	if (passwordsQueue.size() <= 1)
	{
		while (passwordsQueue.isLastOne)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));		
		}
	}

	std::string passwordToValidate = passwordsQueue.front();
	m_mutex.lock();
	std::cout << passwordToValidate;
	passwordsQueue.pop();
	m_mutex.unlock();

	if (passwordToValidate == password)
	{
		success = true;
		foundPassword = passwordToValidate;
	}

	validate(passwordsQueue, success, m_mutex, foundPassword);
}
