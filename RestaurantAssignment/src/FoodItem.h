#pragma once
#include <memory>
#include <string>

typedef enum class FoodCategories : uint16_t
{
	// From glfw3.h
	
	Breakfast = 0,
	Lunch = 1,
	Dinner = 2,
	Appetizer = 3,
	Drink = 4,
	Sandwich = 5,
	Salad = 6,
	Soup = 7,
	Entree = 8,
	Vegetarian = 9,
	Vegan = 10
};

class FoodItem {
private:
	std::string name;
	float price;
	FoodCategories categories;
	int quantity;
	std::string specialInstructions;

public:
	FoodItem() {};
	FoodItem(float newPrice, FoodCategories newCategories) : price(newPrice), categories(newCategories), quantity(0), specialInstructions("") {};
	~FoodItem() {};

	std::string getName() { return name; };
	float getPrice() { return price; };
	bool isInCategory(FoodCategories checkCat) { return categories == checkCat; };
	int getQuantity() { return quantity; };
	std::string getSpecialInstructions() { return specialInstructions; };
};