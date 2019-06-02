#include"LoginWindow.h"

void LoginWindow::login()
{
	std::cout << " ____________________________________________________________" << std::endl;
	std::cout << "|                                                            |" << std::endl;
	std::cout << "|                          LOGOWANIE                         |" << std::endl;
	std::cout << "|                                                            |" << std::endl;
	std::cout << "|                                                            |" << std::endl;
	std::cout << "|             LOGIN:";
	std::cin >> credentials.login; 
	std::cout << std::endl;
	std::cout << "|                                                            |" << std::endl;
	std::cout << "|             HASLO:";
	std::cin >> credentials.password;
	std::cout << std::endl;
	std::cout << "|                                                            |" << std::endl;
	std::cout << "|                                                            |" << std::endl;
	std::cout << "|____________________________________________________________|" << std::endl;
	credentialsToCrack.push(credentials);
	std::cout << "Press ENTER to start brute forcing..." << std::endl;
}

bool LoginWindow::validatePassword(char password)
{
	Credentials passwordToCrack = credentialsToCrack.front();

	for(int i = 0; i< passwordToCrack.password.length(); i++)
	{
		if (password == passwordToCrack.password[i])
		{
			generatedPassword[i] = password;
			matched++;
		}
	}
	if (matched == passwordToCrack.password.length())
		return true;
	return false;
}



