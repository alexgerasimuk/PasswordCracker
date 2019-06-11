#include <queue>
#include <iostream>
#include <thread>
#include "Validator.h"
#include "Generator.h"
#include "Queue.h"
#include <atomic>
#include <mutex>

int queueSize = 0, validatorNum = 0;
Validator validator;
Generator generator;


std::mutex m_mutex;

std::string alphabet;
std::string numerals = "0123456789";
std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string specialAnsi = "!\"#¤%&/()=?`^¨*';:_,.";
std::vector <std::string> randomGeneratedPasswords;

void menu()
{
	std::cout << "Podaj jak dluga ma byc kolejka: ";
	std::cin >> queueSize;
	std::cout << std::endl;
	std::cout << "Podaj ile w¹tków ma sprawdzac poprawnosc hasla: ";
	std::cin >> validatorNum;
	std::cout << std::endl;

}

void generateAlthabet()
{
	alphabet = alphabetLower + alphabetUpper + numerals + specialAnsi;
}

void createPasswords(int validatorNum)
{
	srand(time(nullptr));
	for (int k = 0; k< validatorNum; k++)
	{
		int passwordLength = rand() % 10 + 1;
		for (int i = 0; i< passwordLength; i++)
		{
			randomGeneratedPasswords[k] = alphabet[rand() % (alphabet.size() - 1)];
		}
	}
}



int main()
{
	menu();

	createPasswords(validatorNum); //stworzenie hase³ do z³amania
	Queue generatedPasswordsQueue(queueSize);

	generator.generateAlthabet(); //stworzenie alfabetu w generatorze
	std::thread g1{ &Generator::checkOneLetter,generatedPasswordsQueue, 1};
	

	std::vector <std::thread> validation;
	for(int i = 0; i<validatorNum; i++)
	{
		validation[i] = std::thread { &Validator::validate, generatedPasswordsQueue };
	}
}

