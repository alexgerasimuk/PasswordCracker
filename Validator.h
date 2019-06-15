#pragma once
#include <string>
#include "Queue.h"

class Validator
{
	std::string password;

public:
	std::mutex m_mutex_success;
	Validator(std::string password);
	std::string validate(Queue& passwordsQueue, std::atomic_bool&, std::mutex& m_mutex);
};
