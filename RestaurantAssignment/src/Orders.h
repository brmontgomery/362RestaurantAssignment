#pragma once

#include <fstream>
#include <vector>
#include "FoodItem.h"
#include "Menu.h"

typedef enum class OrderStatus : uint16_t
{
	// From glfw3.h
	Open = 0,
	Closed = 1,
	Canceled = 2
};

typedef enum class OrderCommandType : uint16_t
{
	// From glfw3.h
	AddOrder = 0,
	CancelOrder = 1,
	CompleteOrder = 2
};

//class with an instance for each order
class Order {
private:
	// Instance variables
	std::vector<FoodItem> orderFoodItems;
	OrderStatus status;
	bool paid;
	int number;

public:
	Order() {}
	Order(OrderStatus newStatus, bool newPaid, int newNumber) : status(newStatus), paid(newPaid), number(newNumber) {}
	// FoodItem manipulation
	std::vector<FoodItem> getItems() { return orderFoodItems; }
	void addItem(FoodItem newItem) { orderFoodItems.push_back(newItem); }
	void removeItem(int itemNum) { orderFoodItems.erase(orderFoodItems.begin() + itemNum - 1); }

	OrderStatus getStatus() { return status; }
	bool getPaid() { return paid; }
	int getNumber() { return number; }

	//order state manipulation
	void changeStatus(OrderStatus newStatus) { status = newStatus; }
	void changePaid(bool newPaid) { paid = newPaid; }
	void setNumber(int newNumber) { number = newNumber; }
	bool isPaid() { return paid; }
	bool closeOrder(std::string str)
	{
		changeStatus(OrderStatus::Closed);
		return true;
	}
};

class OrderQueue {

	//singleton
	//--------------------------------------------------------------------------------------------------------------------------------
public:
	static OrderQueue *getOrderQueue();
protected:
	OrderQueue();
	virtual ~OrderQueue();

	friend class OrderQueueDestroyer;

private:
	static OrderQueue *m_OrderQueue;
	static OrderQueueDestroyer destroyer;

	//--------------------------------------------------------------------------------------------------------------------------------

	//non-singleton
public:
	int input(Order newOrder, bool isNew = true)
	{
		// Object to write in file
		std::ofstream file_obj;

		// Opening file in append mode
		file_obj.open("OrderList.txt", std::ios::app);

		// Feeding appropriate data in variables
		int size = newOrder.getItems().size();

		file_obj.write((char*)&size, sizeof(size));

		for (int i = 0; i < size; i++) {
			FoodItem tempItem = newOrder.getItems()[i];

			file_obj.write((char*)&tempItem, sizeof(tempItem));
		}

		OrderStatus status = newOrder.getStatus();
		file_obj.write((char*)&status, sizeof(status));

		bool paid = newOrder.getPaid();
		file_obj.write((char*)&paid, sizeof(paid));

		size = newOrder.getNumber();
		file_obj.write((char*)&size, sizeof(size));

		if (isNew) {
			orderList.push_back(newOrder);
		}

		file_obj.close();

		return 0;
	}

	// Function definition of output_highest_rated() to
	// extract info from file Data Base
	int getOrderList()
	{
		// Object to read from file
		std::ifstream file_obj;

		// Opening file in input mode
		file_obj.open("OrderList.txt", std::ios::in);

		if (!file_is_empty(file_obj)) {

			// Object of class contestant to input data in file
			Order obj;
			int size;
			FoodItem foodObj;
			bool paid;
			OrderStatus status;

			orderList.clear();

			// Reading from file into object "obj"
			file_obj.read((char*)&size, sizeof(size));

			// Checking till we have the feed
			while (!file_obj.eof()) {
				//get vector Items
				for (int i = 0; i < size; i++)
				{
					file_obj.read((char*)&foodObj, sizeof(foodObj));

					obj.addItem(foodObj);
				}

				//get non-vector items
				file_obj.read((char*)&status, sizeof(status));

				obj.changeStatus(status);

				file_obj.read((char*)&paid, sizeof(paid));

				obj.changePaid(paid);

				file_obj.read((char*)&size, sizeof(size));

				obj.setNumber(size);

				//push order on List
				orderList.push_back(Order(obj));

				// Checking further
				file_obj.read((char*)&size, sizeof(size));
			}

		}
		else {
			Order orderToAdd = Order(OrderStatus::Canceled, 0, 0);

			input(orderToAdd);
			orderList.push_back(Order(orderToAdd));
		}

		file_obj.close();

		return 0;
	}

	void save() {
		// Object to write in file
		std::ofstream file_obj;
		file_obj.open("OrderList.txt", std::ofstream::out | std::ofstream::trunc);
		file_obj.close();

		// Opening file in append mode
		file_obj.open("OrderList.txt");

		for (int i = 0; i < orderList.size(); i++) {
			input(orderList[i], false);
		}
	}

	bool file_is_empty(std::ifstream& pFile)
	{
		return pFile.peek() == std::ifstream::traits_type::eof();
	}

	bool addOrder(Order newOrder, OrderStatus newStatus = OrderStatus::Open)
	{
		input(newOrder);
orderList.push_back(newOrder);

save();

return 0;
	}

	bool changeOrderStatus(std::string str, OrderStatus newStatus)
	{
		int place = exists(str);
		if (!place == -1) {
			orderList[place].changeStatus(newStatus);
		}

		save();

		return false;
	}

	int exists(std::string str) {
		int checkNum = std::stoi(str);

		//inefficient finder
		for (int i = 0; i < orderList.size(); i++) {
			if (orderList[i].getNumber() == checkNum) {
				return i;
			}
		}

		return -1;
	}

	std::vector<Order> getOpenOrders() {
		std::vector<Order> openList;

		for (int i = 0; i < orderList.size(); i++) {
			if (orderList[i].getStatus() == OrderStatus::Open) {
				openList.push_back(orderList[i]);
			}
		}

		return openList;
	}

	Order getOrder(std::string str) {
		int checkNum = std::stoi(str);

		for (int i = 0; i < orderList.size(); i++) {
			if (orderList[i].getNumber() == checkNum) {
				return orderList[i];
			}
		}
	}

	int getNextNumber() {
		int largest = 0;
		for (int i = 0; i < getOrderListSize(); i++) {
			if (orderList[i].getNumber() > largest) {
				largest = orderList[i].getNumber();
			}
		}
		return largest;
	}

	//iterator funcs
	Order getOrderFromIt(int it) {
		return orderList[it];
	}

	int getOrderListSize() {
		return orderList.size();
	}

	void printOpenOrders() {
		std::cout << "Open Orders\n\n\n";

		std::cout << "Number        |    Status?\n";
		std::cout << "              |";

		std::vector<Order> openOrders = getOpenOrders();

		for (int i = 0; i < openOrders.size(); i++) {
			printOrder(openOrders[i]);
		}
	}

	void printSingleOrder(Order order) {
		std::cout << "Order " << order.getNumber() << "\n\n\n";

		std::cout << "Number        |    Items?\n";
		std::cout << "              |\n";

		printOrder(order);
	}

	void printOrder(Order order) {
		std::cout << order.getNumber();

		if (order.getNumber() < 10) {
			std::cout << "             |    " << order.getItems()[0].getName() << " x " << order.getItems()[0].getQuantity() << "\n";
		}
		else if (order.getNumber() < 100) {
			std::cout << "            |    " << order.getItems()[0].getName() << " x " << order.getItems()[0].getQuantity() << "\n";
		}
		else if (order.getNumber() < 1000) {
			std::cout << "           |    " << order.getItems()[0].getName() << " x " << order.getItems()[0].getQuantity() << "\n";
		}
		else {
			std::cout << "          |    " << order.getItems()[0].getName() << " x " << order.getItems()[0].getQuantity() << "\n";
		}

		for (int i = 1; i < order.getItems().size(); i++) {
			std::cout << "              |    " << order.getItems()[i].getName() << " x " << order.getItems()[i].getQuantity() << "\n";
		}

		std::cout << "\n";
	}

private:
	std::vector<Order> orderList;
};

//super janky iterator (it works tho)
class OrderIterator {
private:
	int iteratorNum;
	OrderQueue* orderList;

public:
	OrderIterator() : iteratorNum(0) { orderList = OrderQueue::getOrderQueue(); }

	void next()
	{
		if (iteratorNum + 1 != orderList->getOrderListSize()) {
			iteratorNum += 1;
		}
	}

	void last()
	{
		if (iteratorNum != 0) {
			iteratorNum -= 1;
		}
	}

	int getIt() {
		return iteratorNum;
	}
};

class OrderQueueDestroyer
{
public:
	OrderQueueDestroyer(OrderQueue * = 0);
	~OrderQueueDestroyer() { delete _singleton; }
	void SetSingleton(OrderQueue *s) { _singleton = s; }

private:
	OrderQueue *_singleton;
};

class OrderCommands {
public:
	OrderCommands() { m_OrderQueue = OrderQueue::getOrderQueue(); }

	void execute(OrderCommandType type, std::string str, Order order = Order(OrderStatus::Canceled, 0, 0))
	{
		if (type == OrderCommandType::AddOrder) {
			m_OrderQueue->addOrder(order);
		}
		else if (type == OrderCommandType::CancelOrder) {
			m_OrderQueue->changeOrderStatus(str, OrderStatus::Canceled);
		}
		else {
			m_OrderQueue->changeOrderStatus(str, OrderStatus::Closed);
		}
	}

	void printOpenOrders() {
		m_OrderQueue->printOpenOrders();
	}

	void printSingleOrder(std::string str) {
		Order order = m_OrderQueue->getOrder(str);
		m_OrderQueue->printSingleOrder(order);
	}

	void printSingleOrder(Order order) {
		m_OrderQueue->printSingleOrder(order);
	}

	int getNextNumber() {
		return m_OrderQueue->getNextNumber();
	}

private:
	OrderQueue* m_OrderQueue;
};

class OrderController {
private:
	OrderCommands commands;
	MenuController menu;

public:
	void guestOrderInterface(std::string RestaurantName) {
		FoodItem item;
		Order newOrder;
		std::string userStr;
		bool exit = false;


		while (!exit) {
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

			std::cout << "Would you like to order (O/o), cancel an order (C/c), check an order's details (H/h), or exit (X/x)?\n\n";

			std::cin >> userStr;

			if (userStr == "O" || userStr == "o") {
				bool done = false;

				while (!done) {
					std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

					item = menu.printMenu();

					if (item.getName() != "") {
						bool added = false;
						for (int i = 0; i < newOrder.getItems().size(); i++) {
							if (!added) {
								if (item.getName() == newOrder.getItems()[i].getName()) {
									newOrder.getItems()[i].setQuantity(newOrder.getItems()[i].getQuantity() + 1);
									added = true;
								}
							}
						}
						if (!added) {
							newOrder.addItem(item);
						}
					}

					bool correctResponse = false;
					while (!correctResponse) {
						std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
						std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

						std::cout << "Would you like to add another item to the order (A/a), proceed to payment (P/p), or cancel and exit (X/x)?\n\n";

						std::cin >> userStr;


						if (userStr == "A" || userStr == "a") {
							// add to order
							correctResponse = true;
						}
						else if (userStr == "P" || userStr == "p") {
							//finalize order
							std::cout << "\n\nReview your order.\n\n";

							commands.printSingleOrder(newOrder);

							std::cout << "Is this correct? Yes (Y/y) or No (N/n)?\n\n";

							std::cin >> userStr;

							if (userStr == "Y" || userStr == "y") {
								newOrder.changeStatus(OrderStatus::Open);
								newOrder.changePaid(true);
								newOrder.setNumber(commands.getNextNumber());

								commands.execute(OrderCommandType::AddOrder, "", newOrder);

								std::cout << "\n\nOrder added!\n Your order ticket is " << newOrder.getNumber() << ". Please remember this number to recieve your order upon arrival. Thank you!\n\n";
							}

							correctResponse = true;
						}
						else if (userStr == "X" || userStr == "x") {
							//go to make a reservation

							std::cout << "\n\nOrder canceled.\n\n";
							correctResponse = true;
							done = true;
						}
						else {
							std::cout << "\n\nPlease enter a correct response.\n\n";
						}
					}
				}
			} else if (userStr == "C" || userStr == "c") {
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "Enter the order number of the order you wish to cancel.\n\n";

				std::cin >> userStr;

				commands.execute(OrderCommandType::CancelOrder, userStr);
			}
			else if (userStr == "H" || userStr == "h") {
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "Enter the order number of the order you wish to check.\n\n";

				std::cin >> userStr;

				commands.printSingleOrder(userStr);
			}
			else if (userStr == "X" || userStr == "x") {
				exit = true;
			}
		}
	}

	void employeeOrderInterface(std::string RestaurantName) {
		std::string userStr;
		bool exit = false;


		while (!exit) {
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

			std::cout << "Would you like to close an order (C/c), check an order's details (H/h), or exit (X/x)?\n\n";

			std::cin >> userStr;

			if (userStr == "C" || userStr == "c") {
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "Enter the order number of the order you wish to close.\n\n";

				std::cin >> userStr;

				commands.execute(OrderCommandType::CompleteOrder, userStr);
			}
			else if (userStr == "H" || userStr == "h") {
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				std::cout << RestaurantName << std::endl << std::endl << std::endl << std::endl;

				std::cout << "Enter the order number of the order you wish to check.\n\n";

				std::cin >> userStr;

				commands.printSingleOrder(userStr);
			}
			else if (userStr == "X" || userStr == "x") {
				exit = true;
			}
		}
	}
};