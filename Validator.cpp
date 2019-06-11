#include "Validator.h"

Validator::Validator(std::string password)
{
	this->password = password;
}

bool Validator::validate(Queue passwordsQueue)
{
	std::string passwordToValidate;
	m_mutex.lock();
	if (passwordsQueue.size() <= 1) {
		while (passwordsQueue.isLastOne == true)
		{
			m_mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			m_mutex.lock();
		}
		// Release the lock
		m_mutex.unlock();
	}
	else
	{
		passwordToValidate = passwordsQueue.front();
		passwordsQueue.pop();
	}
	if(passwordToValidate == password)
		return true;
	return false;
}


