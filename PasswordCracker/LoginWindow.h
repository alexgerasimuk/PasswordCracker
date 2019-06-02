#pragma once
#include <iostream>
#include <locale>
#include <queue>

struct Credentials
{
	std::string login;
	std::string password;
};

class LoginWindow
{
	int matched = 0; //generate one per one password
	std::string generatedPassword; //generate one per one password
	Credentials credentials;
	std::queue<Credentials> credentialsToCrack;
	int createdCredentialsNum = 0;

public:
	int threadsNum = 1;
	int passwordSimultaneouslyCracked = 1;
	void login();
	bool validatePassword(char password);
};