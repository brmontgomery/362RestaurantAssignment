#pragma once

#include <fstream>
#include <vector>
#include "FoodItem.h"

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

	Order getOpenOrders(std::string str) {
		int checkNum = std::stoi(str);

		for (int i = 0; i < orderList.size(); i++) {
			if (orderList[i].getNumber() == checkNum && orderList[i].getStatus() == OrderStatus::Open) {
				return orderList[i];
			}
		}
	}

	Order getOrder(std::string str) {
		int checkNum = std::stoi(str);

		for (int i = 0; i < orderList.size(); i++) {
			if (orderList[i].getNumber() == checkNum) {
				return orderList[i];
			}
		}
	}

	//iterator funcs
	Order getOrderFromIt(int it) {
		return orderList[it];
	}

	int getOrderListSize() {
		return orderList.size();
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
	OrderIterator() { orderList = OrderQueue::getOrderQueue(); }

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
	void execute(OrderCommandType type, std::string str, Order order = Order(OrderStatus::Canceled, 0, 0))
	{
		m_OrderQueue = OrderQueue::getOrderQueue();

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

private:
	OrderQueue* m_OrderQueue;
};

class OrderController {

};