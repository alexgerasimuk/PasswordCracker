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
std::string specialAnsi = "!\"#�%&/()=?`^�*';:_,.";
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
	std::atomic_bool success(false);
	std::string foundPassword = {};

	menu();
	generateAlthabet();
	createPasswords(randomGeneratedPassword); //stworzenie hase� do z�amania
	std::cout << "Wygenerowane haslo do zlamania to: " << randomGeneratedPassword;
    Queue generatedPasswordsQueue(queueSize);
	Validator* validatorPointer = new Validator(randomGeneratedPassword, generatedPasswordsQueue);
	Generator* generatorPointer = new Generator(generatedPasswordsQueue);

	std::thread g1{&Generator::generatorWrapper, generatorPointer, queueSize, std::ref(success)};
	std::vector<std::thread> validation;
	for (unsigned int i = 0; i < validatorNum; i++)
	{
		validation.push_back(std::thread{ &Validator::validate, validatorPointer, std::ref(success), std::ref(foundPassword)});
	}

 	g1.join();
	validation[0].join();

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
