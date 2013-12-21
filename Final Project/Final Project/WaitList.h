#pragma once
#include <string>
#include "Costumer.h"
using namespace std;

class WaitList
{
private:
	Costumer *head;
	Costumer *tail;
public:
	//constructor no inputs
	WaitList(void);
	//deltes all nodes
	~WaitList(void);

	//puts new costumer on the end of the list
	void enqueue(string costumerName);
	//returns costumer at head
	string dequeue(void);
	//formatted string function
	string toString(void);
	//returns node of the head
	Costumer* peek(void);
};

