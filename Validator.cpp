#include "Validator.h"
#include <iostream>
#include <thread>

Validator::Validator(std::string password, Queue& queue, std::atomic_bool& success, std::string &foundPassword)
    : password(password), passwordsQueue(queue), success(success), foundPassword(foundPassword)
{
}

void Validator::validate()
{
	std::string passwordToValidate = passwordsQueue.front();
	std::cout << passwordToValidate << '\n';
    if(success)
    {
        return;
    }

	if (passwordToValidate == password)
	{
		success = true;
		foundPassword = passwordToValidate;
	}

	else
    {
        validate();
    }

}

