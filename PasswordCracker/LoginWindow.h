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

public:
	void login();
	bool validatePassword(char password);
};

