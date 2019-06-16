#pragma once
#include <string>
#include "Queue.h"

class Validator
{
	std::string password;
    Queue& passwordsQueue;

public:

	Validator(std::string password, Queue& queue);
	void validate(std::atomic_bool&, std::string &foundPassword);
};
