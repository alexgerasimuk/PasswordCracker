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
    Queue& queue;
    void checkNextLetter(int maxQueueSize, int passwordLenght, int currentIndex);

public:
	Generator(Queue& queue);
	void generateAlphabet();
	void generatorWrapper(int currentIndex, std::atomic_bool& success);
};
