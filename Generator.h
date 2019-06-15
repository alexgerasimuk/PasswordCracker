#pragma once
#include "Queue.h"

class Generator
{
	std::string alphabet;
	std::string numerals = "0123456789";
	std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
	std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//	std::string specialAnsi = "!\"#¤%&/()=?`^¨*';:_,.";
	std::string password = {};

public:
	Generator();
	void generateAlphabet();
	void checkOneLetter(Queue& queue, int maxSize, int currentSize, std::mutex& m_mutex);
};
