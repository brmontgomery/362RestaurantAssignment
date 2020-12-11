#include <iostream>
#include <string>

#include "EmployeeAccount.h"

std::string RestaurantName = "Your Restaurant Name";

void goToEmployeeInterface();
void goToAdminInterface();

void clearText();

int main() 
{
	bool exit = false;

	while (!exit) {
		//figure out if guest or employee
		clearText();
		std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

		std::cout << "Are you a guest (G/g) or an employee (E/e)? Or, would you like to exit? (X/x)\n\n";

		std::string userStr;
		std::cin >> userStr;


		//if employee
		if (userStr == "E" || userStr == "e") {
			bool isLoggedIn = false;

			while (!isLoggedIn)
			{
				EmployeeAccounts empAccounts;

				clearText();
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "Please enter your employee number or type (X/x) to exit: \n\n";

				std::cin >> userStr;

				//check if exit
				if (userStr == "X" || userStr == "x") {
					isLoggedIn = true;
					exit = true;
				} else {
					//check if user exists
					if (empAccounts.exists(userStr)) {
						isLoggedIn = true;

						if (empAccounts.isAdmin(userStr)) {
							clearText();
							std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

							std::cout << "Enter Admin (A/a) or Employee (E/e) interface?\n\n";

							std::cin >> userStr;

							if (userStr == "A" || userStr == "a") {
								goToAdminInterface();
							}
							else {
								goToEmployeeInterface();
							}
						}
						else {
							goToEmployeeInterface();
						}
					}
					else {
						std::cout << "\n\n Employee Number not found. Press enter to re-enter a number.\n\n";
						std::cin >> userStr;
					}
				}
			}
		} else if (userStr == "G" || userStr == "g") {
			bool isLoggedIn = false;

			while (!isLoggedIn)
			{
				//figure out where the guest wants to go
				clearText();
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "Would you like to enter the Reservation System (R/r), the Menu (M/m), track your order (O/o), or exit (X/x)?\n\n";

				std::cin >> userStr;


				if (userStr == "R" || userStr == "r") {
					//go to make a reservation

				}
				else if (userStr == "M" || userStr == "m") {
					//go to the menu and order

				}
				else if (userStr == "O" || userStr == "o") {
					//go to the order tracker

				} if (userStr == "X" || userStr == "x") {
					isLoggedIn = true;
					exit = true;
				}
			}
		} else if (userStr == "X" || userStr == "x") {
			exit = true;
		}
		else {
			std::cout << "Please input either G/g or E/e for guest or employee.\n\n";
		}
	}
}

void goToEmployeeInterface()
{
	std::string userStr;
	bool exit = false;

	while (!exit)
	{
		clearText();
		std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

		std::cout << "Would you like to enter the Reservation Manager (R/r), the Table Manager (T/t), the Timeclock (I,i), or exit (X/x)?\n\n";

		std::cin >> userStr;

		if (userStr == "R" || userStr == "r") {
			//go to reservation manager
		}
		else if (userStr == "T" || userStr == "t") {
			//go to table manager
		}
		else if (userStr == "I" || userStr == "i") {
			//go to timeclock
		}
		else if (userStr == "X" || userStr == "x") {
			exit = true;
		}
		else {
			std::cout << "Please choose either (R/r, T/t, I/i, or X/x)\n\n";
		}
	}
}

void goToAdminInterface()
{
	std::string userStr;
	bool exit = false;

	while (!exit)
	{
		clearText();
		std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

		std::cout << "Would you like to enter the Table Editor (T/t) the Menu Editor (M/m), Employee List Editor(E/e) or exit (X/x)?\n\n";

		std::cin >> userStr;

		if (userStr == "T" || userStr == "t") {
			//go to table editor


		}
		else if (userStr == "M" || userStr == "m") {
			//go to menu editor


		}
		else if (userStr == "E" || userStr == "e") {
			//go to employee editor


		}
		else if (userStr == "X" || userStr == "x") {
			exit = true;
		}
		else {
			std::cout << "Please choose either (T/t, M/m, or X/x)\n\n";
		}
	}
}

void clearText()
{
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}