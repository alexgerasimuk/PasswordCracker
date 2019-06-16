#include "Validator.h"
#include <iostream>
#include <thread>

Validator::Validator(std::string password){
	this->password = password;
}

void Validator::validate(Queue& passwordsQueue, std::atomic_bool& success, std::string &foundPassword)
{
	if (passwordsQueue.size() <= 1)
	{
		while (passwordsQueue.isLastOne)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));		
		}
	}

	std::string passwordToValidate = passwordsQueue.front();
	std::cout << passwordToValidate;
	passwordsQueue.pop();

	if (passwordToValidate == password)
	{
		success = true;
		foundPassword = passwordToValidate;
		return;
	}

	validate(passwordsQueue, success, foundPassword);
}
