#include "PasswordCracker.h"
#include "LoginWindow.h"

void PasswordCracker::generateAlthabet()
{
	alphabet = alphabetLower + alphabetUpper + numerals + specialAnsi;
}

void PasswordCracker::generatePassword()
{
	// _ _ _ _
	//|P|A|S|S|

	for(int i = 0;i < MAX_CHARS; i++)
	{
		
	}

}

void PasswordCracker::checkOneLetter()
{
	for(int i = 0; i<alphabet.length(); i++)
	{
		bruteWordInProgress = alphabet[i];
		loginWindow.validatePassword(bruteWordInProgress);
	}
}
