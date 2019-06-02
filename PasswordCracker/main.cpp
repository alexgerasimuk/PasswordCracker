#include "LoginWindow.h"
#include "PasswordCracker.h"
#include <thread>

LoginWindow loginWindow;
PasswordCracker cracker;

int  main()
{
	std::vector<std::thread> threads;
	for(int i = 0; i< loginWindow.threadsNum; i++)
	{
		std::thread th1(cracker.checkOneLetter(loginWindow));
		threads.push_back(std::move(th1));
	}

}
