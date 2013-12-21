#include "StdAfx.h"
#include "WaitList.h"

//constructor sets both the head and tail to nullptr
WaitList::WaitList(void)
{
	head = nullptr;
	tail = nullptr;
}

//adds a new costumer to the end of the list
void WaitList::enqueue(string costumerName) {
	Costumer *node = new Costumer(costumerName);
	if (head == nullptr) {
		head = node;
		tail = node;
	} else {
		tail->setNext(node);
		tail = node;
	}
	tail->setNext(nullptr);
}

//deletes node from the beginning of the queue
string WaitList::dequeue(void) {
	string name = "";
	if (head == nullptr) {
		throw logic_error("There is no one waiting for this book");
	} else {
		Costumer *node = head;
		name = node->getName();
		head = node->getNext();
		delete node;
		return name;
	}

}

//for printing out information to console
string WaitList::toString(void) {
	string toString = "";
	if (head == nullptr) {
		throw logic_error("There is no one waiting for this book");
	}
	Costumer *itorator = head;
	while (itorator != nullptr) {
		toString = toString + itorator->getName() + " ";
		itorator = itorator->getNext();
	}

	return toString;
}

//peeks the next next constumer
//returns pointer
Costumer* WaitList::peek(void) {
	return head;
}

//deletes allocated memory
WaitList::~WaitList(void)
{
	if (head != nullptr) {
		Costumer* current = head;
		//walk down list and call delete on each individual Costumer
		while (current != nullptr){
			Costumer* temp = current->getNext();
			delete current;
			current = temp;
		}
		head = nullptr;
	}
}
