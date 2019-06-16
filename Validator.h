#pragma once
#include <string>
#include "Queue.h"

class Validator
{
	std::string password;
    Queue& passwordsQueue;
    std::atomic_bool& success;
    std::string &foundPassword;

public:

	Validator(std::string password, Queue& queue, std::atomic_bool& success, std::string &foundPassword);
	void validate();
};
