#include <iostream>
#include <thread>
#include "Validator.h"
#include "Generator.h"
#include "Queue.h"

unsigned int queueSize = 0, validatorNum = 0;

std::string alphabet;
std::string numerals = "0123456789";
std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string specialAnsi = "!\"#%&/()=?`^*';:_,.";


void menu()
{
	std::cout << "Queue size: ";
	std::cin >> queueSize;
	std::cout << std::endl;
	std::cout << "Number of validator threads: ";
	std::cin >> validatorNum;
	std::cout << std::endl;
}

void generateAlthabet()
{
	alphabet = alphabetLower + alphabetUpper + numerals + specialAnsi;
}

std::string createPasswords()
{
    std::string password;
	srand(time(NULL));

//	int passwordLength = (rand() % 5 + 1);
	int passwordLength = 2;
	for (int i = 0; i < passwordLength; i++)
	{
		int r = (rand() % (alphabet.length() - 1));
		auto c = alphabet[r];
		password += c;
	}
	return password;
}

int main(int argc, char* argv[])
{
	std::atomic_bool success(false);
	std::string foundPassword = {};

	menu();
	generateAlthabet();
    std::string randomGeneratedPassword = createPasswords();
	std::cout << "Random generated password to crack: " << randomGeneratedPassword << '\n';
    Queue generatedPasswordsQueue(queueSize);
	Validator* validatorPointer = new Validator(randomGeneratedPassword, generatedPasswordsQueue, success,foundPassword);
	Generator* generatorPointer = new Generator(generatedPasswordsQueue, queueSize, success);

	std::thread g1{&Generator::generatorWrapper, generatorPointer};

	std::vector<std::thread> validation;
	for (unsigned int i = 0; i < validatorNum; i++)
	{
		validation.push_back(std::thread{ &Validator::validate, validatorPointer});
	}

 	g1.join();
	for(unsigned int i = 0; i < validation.size(); i++){
        validation[i].join();
	}

	std::cout << "Znalezione haslo to: " << foundPassword;

	return 0;
}
