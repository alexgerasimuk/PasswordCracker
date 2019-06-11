#pragma once
#include <string>
#include <vector>
#include <queue>
#include "Queue.h"
#include <mutex>

class Generator
{
	std::string alphabet;
	std::string numerals = "0123456789";
	std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
	std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string specialAnsi = "!\"#¤%&/()=?`^¨*';:_,.";
	std::string password;

	std::vector<std::string> passwordBucket;

	
public:
	std::mutex m_mutex;
	std::string publishPasswordToMain(std::queue<std::string> queue, int size);
	void generateAlthabet();
	void checkOneLetter(Queue queue, int maxSize, int currentSize);
};
