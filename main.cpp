#include <iostream>
#include <thread>
#include "Validator.h"
#include "Generator.h"
#include "Queue.h"

unsigned int queueSize = 0, validatorNum = 0;
std::atomic_int currNumOfThreads;

std::string alphabet;
std::string numerals = "0123456789";
std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string specialAnsi = "!\"#¤%&/()=?`^¨*';:_,.";
std::string randomGeneratedPasswords;

void menu()
{
	std::cout << "Podaj jak dluga ma byc kolejka: ";
	std::cin >> queueSize;
	std::cout << std::endl;
	std::cout << "Podaj ile watkow ma sprawdzac poprawnosc hasla: ";
	std::cin >> validatorNum;
	std::cout << std::endl;
}

void generateAlthabet()
{
	alphabet = alphabetLower;
}

void createPasswords(std::string& randomGeneratedPasswords)
{
	srand(time(NULL));

	int passwordLength = rand() % 10 + 1;
	for (int i = 0; i < passwordLength; i++)
	{
		int r = (rand() % (alphabet.length() - 1));
		auto c = alphabet[r];
		randomGeneratedPasswords += c;
	}
	std::cout << randomGeneratedPasswords.length();
}


int main(int argc, char* argv[])
{
	std::mutex m_mutex;
	std::atomic_bool success = false;

	menu();
	generateAlthabet();
	createPasswords(randomGeneratedPasswords); //stworzenie hase³ do z³amania
	Validator* validatorPointer = new Validator(randomGeneratedPasswords);
	Generator* generatorPointer = new Generator();
	Queue generatedPasswordsQueue(queueSize);

	std::cout << randomGeneratedPasswords.length();
	std::thread g1{&Generator::checkOneLetter, generatorPointer, std::ref(generatedPasswordsQueue), queueSize, 1, std::ref(m_mutex)};

	std::vector<std::thread> validation;

	for (int i = 0; i < validatorNum; i++)
	{
		validation[i] = std::thread{&Validator::validate, validatorPointer, std::ref(generatedPasswordsQueue), std::ref(success), std::ref(m_mutex)};
	}

	while (!success)
	{
		if (validation.size() < validatorNum)
		{
			for (unsigned int i = validation.size(); i < validatorNum; i++)
			{
				validation[i] = std::thread{&Validator::validate,validatorPointer, std::ref(generatedPasswordsQueue), std::ref(success), std::ref(m_mutex)};
			}
		}
	}

	g1.join();

	for (unsigned int i = 0; i < validatorNum; i++)
	{
		validation[i].join();
	}
	return 0;
}
