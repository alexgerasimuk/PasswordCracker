#pragma once
#include <string>
#include "Queue.h"

class Validator
{
	std::string password;

public:

	Validator(std::string password);
	void validate(Queue& passwordsQueue, std::atomic_bool&, std::string &foundPassword);
};
