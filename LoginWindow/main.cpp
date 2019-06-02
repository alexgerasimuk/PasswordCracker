#include <iostream>
#include <fstream>
#include<string>

std::string login, password;

void writeToFile(std::string filename, std::string login, std::string password)
{
	std::ofstream outputFile;
	outputFile.open(filename, std::ios::out);

	if (outputFile.good())
	{
		for (int i = 0; i< (sizeof(login) + sizeof(password)-2); i++)
		{
			if (i < sizeof(login) - 1) {
				outputFile << login;
			}
			else
				outputFile << password[i - sizeof(login)];
		}

		std::cout << "Zapisano do pliku." << std::endl;
	}
	else
	{
		std::cout << "Blad zapisu." << std::endl;
	}

	outputFile.close();
}

int main()
{

	std::cout << " ____________________________________________________________"<< std::endl;
	std::cout << "|                                                            |"<< std::endl;
	std::cout << "|                          LOGOWANIE                         |"<< std::endl;
	std::cout << "|                                                            |"<< std::endl;
	std::cout << "|                                                            |"<< std::endl;
	std::cout << "|             LOGIN:";
	std::cin >> login;
	std::cout << std::endl;
	std::cout << "|                                                            |"<< std::endl;
	std::cout << "|             HASLO:";                                        
	std::cin >> password;
	std::cout << std::endl;
	std::cout << "|                                                            |"<< std::endl;
	std::cout << "|                                                            |"<< std::endl;
	std::cout << "|____________________________________________________________|" << std::endl;
	writeToFile("password.txt", login, password);


}


