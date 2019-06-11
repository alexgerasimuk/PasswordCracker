#pragma once
#include <string>
#include "Queue.h"

class Queue;

class Validator
{
	std::string password;

public:
	std::mutex m_mutex;
	Validator(std::string password);
	bool validate(Queue passwordsQueue);
};
