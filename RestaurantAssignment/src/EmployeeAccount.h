#pragma once
#include <fstream>
#include <string>
#include <vector>

class EmployeeAccount {
private:
	int number;
	bool admin;

public:
	EmployeeAccount() {};
	EmployeeAccount(int newNumber) : number(newNumber), admin(false) {};
	EmployeeAccount(int newNumber, bool newAdmin) : number(newNumber), admin(newAdmin) {};
	EmployeeAccount(const EmployeeAccount& a2) { number = a2.number; admin = a2.admin; }
	~EmployeeAccount() {};

	int getNumber() { return number; };
	bool getAdmin() { return admin; };

	void setNumber(int newNumber) { number = newNumber; };
	void setAdmin(bool newAdmin) { admin = newAdmin; };
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

	EmployeeAccounts() {
		getEmployeeList();
	};

	int input(EmployeeAccount newEmployee)
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
				employeeList.push_back(EmployeeAccount(obj));
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