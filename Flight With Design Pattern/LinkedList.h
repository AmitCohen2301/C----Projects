#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

using namespace std;

template <class T>
class Node 
{
public:
	T data;
	Node<T>* next;

	// Constructor
	Node(const T& value) : data(value), next(nullptr) {};

	// Get data
	T getData() { return this->data; }
};

template <class T>
class LinkedList 
{
private:
	Node<T>* head;
	Node<T>* tail;

public:
	// Constructor
	LinkedList() : head(nullptr), tail(nullptr) {}

	// Destructor
	~LinkedList()
	{
		Node<T>* currentNode = head;
		Node<T>* nodeToDelete = head;
		while (currentNode != nullptr)
		{
			currentNode = currentNode->next;
			delete nodeToDelete;
			nodeToDelete = currentNode;
		}
		head = nullptr;
		tail = nullptr;
	}

	// Insert a value to end of the list
	bool insert(const T& value)
	{
		Node<T>* nodeToInsert = new Node<T>(value);
		if (head == nullptr) // First node in list
			head = nodeToInsert;
		else // Not first node in list
			tail->next = nodeToInsert;
		tail = nodeToInsert;
		return true;
	}

	// Get head
	Node<T>* getHead() const
	{
		return this->head;
	}

	// Get tail
	Node<T>* getTail() const
	{
		return this->tail;
	}

	// Get node in index
	Node<T>* getDataInIndex(int index) const 
	{
		Node<T>* currentNode = head;
		int indexCount = 0;
		while (currentNode != nullptr) 
		{
			if (indexCount == index) 
				return currentNode;
			indexCount++;
			currentNode = currentNode->next;
		}
		return NULL;
	}

	// Remove node at index
	bool removeNodeAt(int index) 
	{
		Node<T>* currentNode = head;
		Node<T>* previousNode = nullptr;
		int indexCount = 0;
		while (currentNode != nullptr) 
		{
			if (indexCount == index)
			{
				if (previousNode == nullptr) // Remove node in head
				{
					if (currentNode == tail) // Remove node in tail (there is only one node in list)
						tail = previousNode;
					head = currentNode->next;
				}
				else if (currentNode == tail) // Remove node in tail
					tail = previousNode;
				else // Remove node that not head and not tail
					previousNode->next = currentNode->next;
				delete currentNode;
				return true;
			}
			indexCount++;
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		return false;
	}

	// Print all the nodes in list
	void printList() 
	{
		Node<T>* currentNode = head;
		while (currentNode != nullptr) 
		{
			cout << currentNode->data << " ";
			currentNode = currentNode->next;
		}
		cout << endl;
	}
};

#endif // !LINKED_LIST_H