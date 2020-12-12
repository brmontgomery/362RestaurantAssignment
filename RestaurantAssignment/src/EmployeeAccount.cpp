#include "EmployeeAccount.h"

EmployeeAccounts* EmployeeAccounts::m_EmployeeAccounts = nullptr;
EmployeeAccountsDestroyer EmployeeAccounts::destroyer;

EmployeeAccountsDestroyer::EmployeeAccountsDestroyer(EmployeeAccounts *s)
{
	_singleton = s;
}

EmployeeAccounts::EmployeeAccounts()
{
	getEmployeeList();
}

EmployeeAccounts* EmployeeAccounts::getEmployeeAccounts() {
	if (!m_EmployeeAccounts)
	{
		m_EmployeeAccounts = new EmployeeAccounts;
		destroyer.SetSingleton(m_EmployeeAccounts);
	}
	return m_EmployeeAccounts;
}

EmployeeAccounts::~EmployeeAccounts()
{
}