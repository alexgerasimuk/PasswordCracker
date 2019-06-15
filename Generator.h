#pragma once
#include <iostream>
#include "Queue.h"
#include <string>

class Generator
{
	std::string alphabet;
	std::string numerals = "0123456789";
	std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
	std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//	std::string specialAnsi = "!\"#�%&/()=?`^�*';:_,.";
	std::string password;
	void checkNextLetter(Queue& queue, int maxQueueSize, int passwordLenght, int currentIndex, std::mutex& m_mutex);

public:
	Generator();
	void generateAlphabet();
	void Generator::generatorWrapper(Queue& queue, int currentIndex, std::mutex& m_mutex, std::atomic_bool& success);
};
