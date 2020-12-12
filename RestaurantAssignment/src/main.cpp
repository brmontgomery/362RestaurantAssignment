#include <iostream>
#include <string>


#include "EmployeeAccount.h"
#include "Orders.h"

void goToEmployeeInterface(std::string RestaurantName);
void goToAdminInterface(std::string RestaurantName);

int main() 
{
	std::string RestaurantName = "Your Restaurant Name";

	bool exit = false;

	while (!exit) {
		//figure out if guest or employee
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

		std::cout << "Are you a guest (G/g) or an employee (E/e)? Or, would you like to exit? (X/x)\n\n";

		std::string userStr;
		std::cin >> userStr;


		//if employee
		if (userStr == "E" || userStr == "e") {
			bool isLoggedIn = false;

			while (!isLoggedIn)
			{
				EmployeeAccountsController empAccounts;

				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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
							std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
							std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

							std::cout << "Enter Admin (A/a) or Employee (E/e) interface?\n\n";

							std::cin >> userStr;

							if (userStr == "A" || userStr == "a") {
								goToAdminInterface(RestaurantName);
							}
							else {
								goToEmployeeInterface(RestaurantName);
							}
						}
						else {
							goToEmployeeInterface(RestaurantName);
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
				OrderController orders;

				//figure out where the guest wants to go
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "Would you like to enter the Reservation System (R/r), the Menu (M/m), or exit (X/x)?\n\n";

				std::cin >> userStr;


				if (userStr == "R" || userStr == "r") {
					//go to make a reservation

					
				}
				else if (userStr == "M" || userStr == "m") {
					//go to the menu and order

					orders.guestOrderInterface(RestaurantName);
				}
				 if (userStr == "X" || userStr == "x") {
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

void goToEmployeeInterface(std::string RestaurantName)
{
	std::string userStr;
	bool exit = false;

	while (!exit)
	{
		OrderController orders;

		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

		std::cout << "Would you like to enter Order manager(O/o) the Timeclock (T,t), or exit (X/x)?\n\n";

		std::cin >> userStr;

		if (userStr == "R" || userStr == "r") {
			//go to reservation manager

			//probably not being done
		}
		else if (userStr == "O" || userStr == "o") {
			//go to order manager

			orders.employeeOrderInterface(RestaurantName);
		}
		else if (userStr == "T" || userStr == "t") {
			//go to timeclock

			//probably not getting to this
		}
		else if (userStr == "X" || userStr == "x") {
			exit = true;
		}
		else {
			std::cout << "Please choose either (R/r, T/t, I/i, or X/x)\n\n";
		}
	}
}

void goToAdminInterface(std::string RestaurantName)
{
	std::string userStr;
	bool exit = false;

	while (!exit)
	{
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

		std::cout << "Would you like to enter the Menu Editor (M/m), Employee List Editor(E/e) or exit (X/x)?\n\n";

		std::cin >> userStr;

		if (userStr == "T" || userStr == "t") {
			//go to table editor

			//doesn't look like I'll get to this
		}
		else if (userStr == "M" || userStr == "m") {
			//go to menu editor

			MenuController menu;
			menu.adminMenuInterface(RestaurantName);
		}
		else if (userStr == "E" || userStr == "e") {
			//go to employee editor

			EmployeeAccountsController empAccounts;
			empAccounts.employeeInterface(RestaurantName);
		}
		else if (userStr == "X" || userStr == "x") {
			exit = true;
		}
		else {
			std::cout << "Please choose either (T/t, M/m, or X/x)\n\n";
		}
	}
}