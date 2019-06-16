#pragma once
#include <iostream>
#include "Queue.h"
#include <string>

class Generator
{
public:
	Generator(Queue& queue,int maxQueueSize, std::atomic_bool& success);
	void generateAlphabet();
	void generatorWrapper();

private:
    std::string alphabet;
    std::string numerals = "0123456789";
    std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
    std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string specialAnsi = "!\"#%&/()=?`^*';:_,.";
    std::string password;
    Queue& queue;
    int maxQueueSize;
    std::atomic_bool& success;

    void checkNextLetter(int passwordLenght, int currentIndex);
};
