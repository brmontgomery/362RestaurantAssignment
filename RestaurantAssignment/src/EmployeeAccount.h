#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include <vector>

class EmployeeAccount {
private:
	int number;
	bool admin;
	bool active;

public:
	EmployeeAccount() : active(true) {};
	EmployeeAccount(int newNumber) : number(newNumber), admin(false), active(true) {};
	EmployeeAccount(int newNumber, bool newAdmin) : number(newNumber), admin(newAdmin), active(true) {};
	EmployeeAccount(const EmployeeAccount& a2) { number = a2.number; admin = a2.admin; }
	~EmployeeAccount() {};

	int getNumber() { return number; }
	bool getAdmin() { return admin; }
	bool getActive() { return active; }

	void setNumber(int newNumber) { number = newNumber; };
	void setAdmin(bool newAdmin) { admin = newAdmin; };
	void setActive(bool newActive) { admin = newActive; };
};

class EmployeeAccounts {

	//singleton
	//--------------------------------------------------------------------------------------------------------------------------------
public:
	static EmployeeAccounts *getEmployeeAccounts();
protected:
	EmployeeAccounts();
	virtual ~EmployeeAccounts();

	friend class EmployeeAccountsDestroyer;

private:
	static EmployeeAccounts *m_EmployeeAccounts;
	static EmployeeAccountsDestroyer destroyer;

	//--------------------------------------------------------------------------------------------------------------------------------

	//non-singleton

public:
	int input(EmployeeAccount newEmployee, bool isNew = true)
	{
		// Object to write in file
		std::ofstream file_obj;

		// Opening file in append mode
		file_obj.open("EmployeeAccounts.txt", std::ios::app);

		// Object of class contestant to input data in file
		EmployeeAccount obj;

		// Feeding appropriate data in variables
		obj.setNumber(newEmployee.getNumber());
		obj.setAdmin(newEmployee.getAdmin());

		file_obj.write((char*)&obj, sizeof(obj));

		file_obj.close();

		if (isNew) {
			employeeList.push_back(obj);
		}

		return 0;
	}

	// Function definition of output_highest_rated() to
	// extract info from file Data Base
	int getEmployeeList()
	{
		// Object to read from file
		std::ifstream file_obj;

		// Opening file in input mode
		file_obj.open("EmployeeAccounts.txt", std::ios::in);

		if (!file_is_empty(file_obj)) {

			// Object of class contestant to input data in file
			EmployeeAccount obj;

			employeeList.clear();

			// Reading from file into object "obj"
			file_obj.read((char*)&obj, sizeof(obj));

			// Checking till we have the feed
			while (!file_obj.eof()) {
				if (obj.getActive()) {
					employeeList.push_back(EmployeeAccount(obj));
				}
				// Checking further
				file_obj.read((char*)&obj, sizeof(obj));
			}

		} else {
			EmployeeAccount EmployeeToAdd;

			EmployeeToAdd = EmployeeAccount(0, true);

			input(EmployeeToAdd);
			employeeList.push_back(EmployeeAccount(EmployeeToAdd));
		}

		file_obj.close();

		return 0;
	}

	void save() {
		// Object to write in file
		std::ofstream file_obj;
		file_obj.open("EmployeeAccounts.txt", std::ofstream::out | std::ofstream::trunc);
		file_obj.close();

		// Opening file in append mode
		file_obj.open("EmployeeAccounts.txt");

		for (int i = 0; i < employeeList.size(); i++) {
			input(employeeList[i]);
		}
	}

	bool file_is_empty(std::ifstream& pFile)
	{
		return pFile.peek() == std::ifstream::traits_type::eof();
	}

	bool exists(std::string str) {
		int empNum = std::stoi(str);

		//inefficient finder
		for (int i = 0; i < employeeList.size(); i++) {
			if (employeeList[i].getNumber() == empNum) {
				return true;
			}
		}

		return false;
	}

	bool isAdmin(std::string str) {
		int empNum = std::stoi(str);

		//inefficient finder
		for (int i = 0; i < employeeList.size(); i++) {
			if (employeeList[i].getNumber() == empNum) {
				return employeeList[i].getAdmin();
			}
		}

		return false;
	}

	void deactivateUser(std::string str) {
		int empNum = std::stoi(str);

		if (!(employeeList.size() > 1)) {
			std::cout << "Cannot delete without getting rid of last admin.\n";
			return;
		}
		//inefficient finder
		for (int i = 0; i < employeeList.size(); i++) {
			if (employeeList[i].getNumber() == empNum) {
				employeeList.erase(employeeList.begin() + i - 1);
				save();
				return;
			}
		}
	}

	void printEmployees()
	{
		std::cout << "Employee List\n\n\n";

		std::cout << "Number        |    Admin?\n";
		std::cout << "              |\n";

		for (int i = 0; i < employeeList.size(); i++) {
			if (employeeList[i].getAdmin()) {
				if (i < 10) {
					std::cout << i << "             | " << i << "    Yes\n";
				}
				else {
					std::cout << i << "            | " << i << "    Yes\n";
				}
			}
			else {
				if (i < 10) {
					std::cout << i << "             | " << i << "    No\n";
				}
				else {
					std::cout << i << "            | " << i << "    No\n";
				}
			}
		}

		std::cout << "\n\n";
	}

private:
	std::vector<EmployeeAccount> employeeList;
};

class EmployeeAccountsDestroyer
{
public:
	EmployeeAccountsDestroyer(EmployeeAccounts * = 0);
	~EmployeeAccountsDestroyer() { delete _singleton; }
	void SetSingleton(EmployeeAccounts *s) { _singleton = s; }

private:
	EmployeeAccounts *_singleton;
};

class EmployeeAccountsController {
public:
	EmployeeAccountsController() { m_EmployeeAccounts = EmployeeAccounts::getEmployeeAccounts(); };
	~EmployeeAccountsController() {};

	bool exists(std::string str)
	{
		return m_EmployeeAccounts->exists(str);
	}

	bool isAdmin(std::string str)
	{
		return m_EmployeeAccounts->isAdmin(str);
	}

	void printEmployees() {
		m_EmployeeAccounts->printEmployees();
	}

	void employeeInterface(std::string RestaurantName) {
		std::string userStr;

		bool exit = false;

		while (!exit)
		{
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

			std::cout << "Would you like to add a user (A/a), delete a user (D/d), or exit (X/x)?\n\n";

			std::cin >> userStr;

			if (userStr == "A" || userStr == "a") {
				//add User

				EmployeeAccount emp;

				std::cout << "\n\nWhat should the new employee's number be?\n\n";

				std::cin >> userStr;

				if (!m_EmployeeAccounts->exists(userStr))
				{
					emp.setNumber(std::stoi(userStr));

					std::cout << "\n\nMark the new user as an admin? YES (Y/y) or NO (N/n)\n\n";

					std::cin >> userStr;

					if (userStr == "Y" || userStr == "y") {
						emp.setAdmin(true);
					}
					else if (userStr == "N" || userStr == "n") {
						emp.setAdmin(false);
					}
					else {
						std::cout << "\n\nAdding user failed. Please choose (Y/y) or (N/n) next time.\n\n";
					}

					m_EmployeeAccounts->input(emp);
				}
				else {
					std::cout << "\n\nThat number is taken, you will need to choose another one. \n\n";
				}
			}
			else if (userStr == "D" || userStr == "d") {
				//delete user

				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "\n\nWhich employee would you like to delete?\n\n";

				printEmployees();

				std::cin >> userStr;

				if (m_EmployeeAccounts->exists(userStr))
				{
					m_EmployeeAccounts->deactivateUser(userStr);
				}
				else {
					std::cout << "\n\nUser does not exist!.\n\n";
				}
			}
			else if (userStr == "X" || userStr == "x") {
				exit = true;
			}
			else {
				std::cout << "\n\nPlease choose either (T/t, M/m, or X/x)\n\n";
			}
		}
	}

private:
	EmployeeAccounts* m_EmployeeAccounts;
};