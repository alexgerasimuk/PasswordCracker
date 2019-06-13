#include "Validator.h"

Validator::Validator(std::string password): password(password)
{
}

std::string Validator::validate(Queue& passwordsQueue, std::atomic_bool& success, std::mutex& m_mutex)
{
	std::string passwordToValidate;
	m_mutex.lock();
	if (passwordsQueue.size() <= 1)
	{
		while (passwordsQueue.isLastOne == true)
		{
			m_mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			m_mutex.lock();
		}
		m_mutex.unlock();
	}
	else
	{
		m_mutex.lock();
		passwordToValidate = passwordsQueue.front();
		passwordsQueue.pop();
		m_mutex.unlock();
	}

	if (passwordToValidate == password)
	{
		m_mutex_success.lock();
		success = true;
		m_mutex_success.unlock();
		return passwordToValidate;
	}
	else
	{
		m_mutex_success.lock();
		success = false;
		m_mutex_success.unlock();
	}

	validate(passwordsQueue, success, m_mutex);
	return nullptr;
}
