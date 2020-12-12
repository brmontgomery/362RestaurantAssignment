#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "FoodItem.h"

class Menu {

	//singleton
	//--------------------------------------------------------------------------------------------------------------------------------
public:
	static Menu *getMenu();
protected:
	Menu();
	virtual ~Menu();

	friend class MenuDestroyer;

private:
	static Menu *m_Menu;
	static MenuDestroyer destroyer;

	//--------------------------------------------------------------------------------------------------------------------------------

	//non-singleton

public:
	int input(FoodItem newFoodItem, bool isNew = true)
	{
		// Object to write in file
		std::ofstream file_obj;

		// Opening file in append mode
		file_obj.open("Menu.txt", std::ios::app);

		// Feeding appropriate data in variables
		FoodCategories cat = newFoodItem.getCategory();
		std::string name = newFoodItem.getName();
		float price = newFoodItem.getPrice();

		file_obj.write((char*)&cat, sizeof(cat));

		int size = name.size();
		file_obj.write((char*)&size, sizeof(size));

		for (int i = 0; i < size; i++) {
			char myChar = name[i];
			file_obj.write((char*)&myChar, sizeof(myChar));
		}

		file_obj.write((char*)&price, sizeof(price));

		bool active = true;
		file_obj.write((char*)&active, sizeof(active));

		file_obj.close();

		if (isNew) {
			menuList.push_back(newFoodItem);
		}

		return 0;
	}

	// Function definition of output_highest_rated() to
	// extract info from file Data Base
	int getMenuList()
	{
		// Object to read from file
		std::ifstream file_obj;

		// Opening file in input mode
		file_obj.open("Menu.txt", std::ios::in);

		if (!file_is_empty(file_obj)) {

			// Object of class contestant to input data in file
			FoodItem obj;

			menuList.clear();

			FoodCategories cat;
			std::string name;
			char myChar;
			float price;
			bool active;
			int size;

			// Reading from file into object "obj"
			file_obj.read((char*)&cat, sizeof(cat));

			// Checking till we have the feed
			while (!file_obj.eof()) {
				obj.setCategory(cat);

				//get Name ready
				name = "";
				file_obj.read((char*)&size, sizeof(size));

				for (int i = 0; i < size; i++) {
					file_obj.read((char*)&myChar, sizeof(myChar));
					name += myChar;
				}

				obj.setName(name);

				file_obj.read((char*)&price, sizeof(price));
				file_obj.read((char*)&active, sizeof(active));

				obj.setPrice(price);
				obj.setActive(active);

				if (obj.getActive()) {
					menuList.push_back(FoodItem(obj));
				}
				// Checking further
				file_obj.read((char*)&cat, sizeof(cat));
			}

		}
		else {
			FoodItem FoodItemToAdd;

			FoodItemToAdd = FoodItem("default", 0.0f, FoodCategories::None, true);

			input(FoodItemToAdd);
			menuList.push_back(FoodItem(FoodItemToAdd));
		}

		file_obj.close();

		return 0;
	}

	void save() {
		// Object to write in file
		std::ofstream file_obj;
		file_obj.open("Menu.txt", std::ofstream::out | std::ofstream::trunc);
		file_obj.close();

		// Opening file in append mode
		file_obj.open("Menu.txt");

		for (int i = 0; i < menuList.size(); i++) {
			input(menuList[i], false);
		}
	}

	bool file_is_empty(std::ifstream& pFile)
	{
		return pFile.peek() == std::ifstream::traits_type::eof();
	}

	bool exists(std::string str) {
		//inefficient finder
		for (int i = 0; i < menuList.size(); i++) {
			if (menuList[i].getName() == str) {
				return true;
			}
		}

		return false;
	}

	FoodItem getMenuItem(std::string str) {
		for (int i = 0; i < menuList.size(); i++) {
			if (menuList[i].getName() == str) {
				return menuList[i];
			}
		}
	}

	void deactivateFoodItem(std::string str) {
		//inefficient finder
		for (int i = 0; i < menuList.size(); i++) {
			if (menuList[i].getName() == str) {
				menuList.erase(menuList.begin() + i - 1);
				save();
				return;
			}
		}
	}

	FoodItem printMenu(bool ordering = true)
	{
		bool exitMenu = false;
		std::string userStr;
		while (!exitMenu) {
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			std::cout << "Menu\n\n\n";

			std::cout << "Categories:\n";
			std::cout << "Please enter the number of the category you wish to see or press (X/x) to exit.\n\n";

			std::cout << "1. Breakfast\n2. Lunch\n3. Dinner\n4. Appetizer\n5. Drink\n6. Sandwich\n7. Salad\n8. Soup\n9. Entree\n10. Vegetarian\n11. Vegan\n\n";

			std::cin >> userStr;

			if (userStr == "X" || userStr == "x") {
				exitMenu = true;
			}
			else {
				bool exit2 = false;

				while (!exit2) {
					std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					std::cout << "Menu\n\n\n";

					int userChoice = std::stoi(userStr) - 1;
					FoodCategories choice;
					switch (userChoice) {
					case 0:
						choice = FoodCategories::Breakfast;
						std::cout << "Breakfast:\n";
						break;
					case 1:
						choice = FoodCategories::Lunch;
						std::cout << "Lunch:\n";
						break;
					case 2:
						choice = FoodCategories::Dinner;
						std::cout << "Dinner:\n";
						break;
					case 3:
						choice = FoodCategories::Appetizer;
						std::cout << "Appetizer:\n";
						break;
					case 4:
						choice = FoodCategories::Drink;
						std::cout << "Drink:\n";
						break;
					case 5:
						choice = FoodCategories::Sandwich;
						std::cout << "Sandwich:\n";
						break;
					case 6:
						choice = FoodCategories::Salad;
						std::cout << "Salad:\n";
						break;
					case 7:
						choice = FoodCategories::Soup;
						std::cout << "Soup:\n";
						break;
					case 8:
						choice = FoodCategories::Entree;
						std::cout << "Entree:\n";
						break;
					case 9:
						choice = FoodCategories::Vegetarian;
						std::cout << "Vegetarian:\n";
						break;
					case 10:
						choice = FoodCategories::Vegan;
						std::cout << "Vegan:\n";
						break;
					}

					if (ordering) {
						std::cout << "Please enter the name of your item selection, or enter (X/x) to exit.\n\n";
					}
					else {
						std::cout << "Enter the name of the food item you wish to delete or exit by entering (X/x)\n\n";
					}

					std::cout << "Name                          |    Price?\n";
					std::cout << "                              |\n";

					for (int i = 0; i < menuList.size(); i++) {
						if (menuList[i].getCategory() == choice) {
							std::cout << menuList[i].getName();
							for (int j = menuList[i].getName().size() - 1; j < 30; j++) {
								std::cout << " ";
							}
							std::cout << "|    " << std::to_string(menuList[i].getPrice()) << "\n";
						}
					}

					std::cout << "\n\n";
					std::cin >> userStr;

					if (userStr == "X" || userStr == "x") {
						exitMenu = true;
					}

					if (ordering) {
						if (exists(userStr)) {
							return getMenuItem(userStr);
						}
					}
				}
			}
		}

		return FoodItem();
	}

private:
	std::vector<FoodItem> menuList;
};

class MenuDestroyer
{
public:
	MenuDestroyer(Menu * = 0);
	~MenuDestroyer() { delete _singleton; }
	void SetSingleton(Menu *s) { _singleton = s; }

private:
	Menu* _singleton;
};

class MenuController {
public:
	MenuController() { m_Menu = Menu::getMenu(); };
	~MenuController() {};

	FoodItem printMenu() {
		return m_Menu->printMenu();
	}

	void adminMenuInterface(std::string RestaurantName) {
		std::string userStr;

		bool exit = false;

		while (!exit)
		{
			FoodItem foodItem;

			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

			std::cout << "Would you like to add a Food Item (A/a), delete a Food Item (D/d), or exit (X/x)?\n\n";

			std::cin >> userStr;

			if (userStr == "A" || userStr == "a") {
				//add User

				std::cout << "\n\nWhat should the new food Item's name be?\n\n";

				std::cin >> userStr;

				if (!m_Menu->exists(userStr))
				{
					foodItem.setName(userStr);

					std::cout << "\n\nWhat should the new food item's price be? (Please put in format of 00.00\n\n";

					std::cin >> userStr;

					foodItem.setPrice(std::stof(userStr + "f"));

					std::cout << "\n\nWhat section of the manu should the food item be placed in? \n\n";

					std::cout << "Breakfast = 0\nLunch = 1\nDinner = 2\nAppetizer = 3\nDrink = 4\nSandwich = 5\nSalad = 6\nSoup = 7\nEntree = 8\nVegetarian = 9\nVegan = 10\n\n";

					std::cin >> userStr;

					int sectionNum = std::stoi(userStr);

					switch (sectionNum) {
					case 0:
						foodItem.setCategory(FoodCategories::Breakfast);
						break;
					case 1:
						foodItem.setCategory(FoodCategories::Lunch);
						break;
					case 2:
						foodItem.setCategory(FoodCategories::Dinner);
						break;
					case 3:
						foodItem.setCategory(FoodCategories::Appetizer);
						break;
					case 4:
						foodItem.setCategory(FoodCategories::Drink);
						break;
					case 5:
						foodItem.setCategory(FoodCategories::Sandwich);
						break;
					case 6:
						foodItem.setCategory(FoodCategories::Salad);
						break;
					case 7:
						foodItem.setCategory(FoodCategories::Soup);
						break;
					case 8:
						foodItem.setCategory(FoodCategories::Entree);
						break;
					case 9:
						foodItem.setCategory(FoodCategories::Vegetarian);
						break;
					case 10:
						foodItem.setCategory(FoodCategories::Vegan);
						break;
					}

					foodItem.setQuantity(0);
					foodItem.setSpecialInstructions("");
					foodItem.setActive(true);

					m_Menu->input(foodItem);
				}
				else {
					std::cout << "\n\nThat name is taken, you will need to choose another one. \n\n";
				}
			}
			else if (userStr == "D" || userStr == "d") {
				//delete user
				foodItem = printMenu();

				if (m_Menu->exists(foodItem.getName()))
				{
					m_Menu->deactivateFoodItem(foodItem.getName());
				}
				else {
					std::cout << "\n\Food Item does not exist!.\n\n";
				}
			}
			else if (foodItem.getName() == "") {
				exit = true;
			}
			else {
				std::cout << "\n\nPlease choose either (T/t, M/m, or X/x)\n\n";
			}
		}
	}

private:
	Menu* m_Menu;
};