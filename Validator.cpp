#include "Validator.h"
#include <iostream>
#include <thread>

Validator::Validator(std::string password, Queue& queue) : passwordsQueue(queue)
{
	this->password = password;
}

void Validator::validate(std::atomic_bool& success, std::string &foundPassword)
{
	std::string passwordToValidate = passwordsQueue.front();
	std::cout << passwordToValidate << '\n';

	if (passwordToValidate == password)
	{
		success = true;
		foundPassword = passwordToValidate;
		return;
	}

	validate(success, foundPassword);
}
