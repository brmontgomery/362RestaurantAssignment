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
	Vegan = 10,
	None = 11
};

class FoodItem {
private:
	std::string name;
	float price;
	FoodCategories category;
	int quantity;
	std::string specialInstructions;
	bool active;

public:
	FoodItem() {};
	FoodItem(std::string newName, float newPrice, FoodCategories newCategories, bool newActive) : name(newName), price(newPrice), category(newCategories), quantity(0), specialInstructions(""), active(newActive) {};
	~FoodItem() {};

	std::string getName() { return name; };
	float getPrice() { return price; };
	FoodCategories getCategory() { return category; };
	int getQuantity() { return quantity; };
	std::string getSpecialInstructions() { return specialInstructions; };
	bool getActive() { return active; };
	bool isInCategory(FoodCategories checkCat) { return category == checkCat; };

	void setName(std::string newName) { name = newName; };
	void setPrice(float newPrice) { price = newPrice; };
	void setCategory(FoodCategories newCat) { category = newCat; };
	void setQuantity(int newQuantity) { quantity = newQuantity; };
	void setSpecialInstructions(std::string newSpecInst) { specialInstructions = newSpecInst; };
	void setActive(bool newActive) { active = newActive; };
};