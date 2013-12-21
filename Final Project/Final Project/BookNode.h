#pragma once
#include <string>
#include "WaitList.h"
using namespace std;

class BookNode
{
private:
	string bookName;
	int haveValue;
	int wantValue;
	BookNode* next;
	WaitList* list;

public:
	BookNode(string bookName, int haveValue, int wantValue);
	~BookNode(void);

	//adds negative or postive to want value
	void addToHaveValue(int);
	//formated string/bookname
	string toString(void);
	//returns wantvalue
	int getWantValue(void);
	//returns havevalue
	int getHaveValue(void);
	//returns bookName
	string getBookName(void);
	//returns pointer to next node
	BookNode* getNext(void);
	//sets the want value
	void setWantValue(int);
	//sets the next node
	void setNext(BookNode*);
	//returns the pointer to the waitlist
	WaitList* getList(void);
	//returns string of removed costumer
	string removeCostumer(void);
};

