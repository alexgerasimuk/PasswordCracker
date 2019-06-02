#pragma once
#include "LoginWindow.h"
//#include "main.cpp"
#include <thread>
#define MAX_CHARS 2

class PasswordCracker
{
	std::string alphabet;
	std::string numerals = "0123456789";
	std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
	std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string specialAnsi = "!\"#¤%&/()=?`^¨*';:_,.";

	bool found = false;
	char bruteWordInProgress;
	int passwordCurrentLength = 0;

	std::vector <std::thread> threads; //project assumption

	std::queue<std::string> crackedPasswords; //project assumption

public:
	void generateAlthabet();

	void checkOneLetter(LoginWindow &loginWindow);
	void generateThreads(int number); //project assumption
	void crackPasswords(int number); //project assumption

};
