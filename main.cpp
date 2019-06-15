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
std::string randomGeneratedPassword;

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

	int passwordLength = 2;
	for (int i = 0; i < passwordLength; i++)
	{
		int r = (rand() % (alphabet.length() - 1));
		auto c = alphabet[r];
		randomGeneratedPasswords += c;
	}
	std::cout <<  randomGeneratedPasswords.length();
}


int main(int argc, char* argv[])
{
	std::mutex m_mutex;
	std::atomic_bool success = false;
	std::string foundPassword = {};

	menu();
	generateAlthabet();
	createPasswords(randomGeneratedPassword); //stworzenie hase³ do z³amania
	std::cout << "Wygenerowane haslo do zlamania to: " << randomGeneratedPassword;
	Validator* validatorPointer = new Validator(randomGeneratedPassword);
	Generator* generatorPointer = new Generator();
	Queue generatedPasswordsQueue(queueSize);

	std::thread g1{&Generator::generatorWrapper, generatorPointer, std::ref(generatedPasswordsQueue), queueSize, std::ref(m_mutex), std::ref(success)};
	std::vector<std::thread> validation;
	for (unsigned int i = 0; i < validatorNum; i++)
	{
		validation.push_back(std::thread{ &Validator::validate, validatorPointer, std::ref(generatedPasswordsQueue), std::ref(success), std::ref(m_mutex), std::ref(foundPassword) });
	}

//	while (!success)
//	{
//		if (validation.size() < validatorNum)
//		{
//			for (unsigned int i = validation.size(); i < validatorNum; i++)
//			{
//				validation[i] = std::thread{&Validator::validate,validatorPointer, std::ref(generatedPasswordsQueue), std::ref(success), std::ref(m_mutex), std::ref(foundPassword) };
//			}
//		}
//	}
	g1.join();
	validation[0].join();
//	system("pause");
//	for (unsigned int i = 0; i < validatorNum; i++)
//	{
//		validation[i].join();
//	}

	if (success)
	{
		g1.detach();

		for (unsigned int i = 0; i < validatorNum; i++)
		{
			validation[i].detach();
		}
		std::cout << "Znalezione haslo to: " << foundPassword;
	}
	return 0;
}
