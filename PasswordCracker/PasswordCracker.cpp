#include "PasswordCracker.h"

void PasswordCracker::generateAlthabet()
{
	alphabet = alphabetLower + alphabetUpper + numerals + specialAnsi;
}


void PasswordCracker::checkOneLetter(LoginWindow &loginWindow)
{
	bool result = false;
	while (result != true) {
		for (int i = 0; i < alphabet.length(); i++)
			result = loginWindow.validatePassword(alphabet[i]);
	}
}
