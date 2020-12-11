#include "Orders.h"

OrderQueue* OrderQueue::m_OrderQueue = nullptr;
OrderQueueDestroyer OrderQueue::destroyer;

OrderQueueDestroyer::OrderQueueDestroyer(OrderQueue *s)
{
	_singleton = s;
}

OrderQueue::OrderQueue()
{
	getOrderList();
}

OrderQueue* OrderQueue::getOrderQueue() {
	if (!m_OrderQueue)
	{
		m_OrderQueue = new OrderQueue;
		destroyer.SetSingleton(m_OrderQueue);
	}
	return m_OrderQueue;
}

OrderQueue::~OrderQueue()
{
}