#pragma once
#include "BookNode.h";
#include "WaitList.h";
#include <iostream>
#include <fstream>
#include <sstream>

class BookTracker
{
private:
	BookNode* head;
	//universal function that finds a node with given name
	//cleans all input
	BookNode* findBook(string bookName);
	
	//for adding a book from a formatted string
	string addBookFromDeliveryString(string line);
	//Empties waitlist if enough books are availible to be sent out
	string emptyWaitList(string bookName);
	//read a file from the last save
	void readInFile(void);
	//adds book from formatted string from saved
	void addBookFromString(string line);
public:
	BookTracker(void);
	~BookTracker(void);
	
	//simple add book
	void add(string bookName, int haveValue, int wantValue);

	//remove book by name 
	bool remove(string bookName);
	//removes book from inventory if availible
	void sellBook(string bookName);
	
	//adds name to waitlist by book name alphabetically
	void addToWaitlist(string bookName, string costumerName);
	//returns head of Inventory
	string getHead(void);
	//formatted string for output
	string toString(void);
	//gets info for specified book
	string getBookInfo(string bookName);
	//changes want value for specified book
	void changeWantValue(string bookName, int newValue);
	//print order to file
	void printOrder(string fileName);
	//prints return to text file
	void printReturn(string fileName);
	//takes delivery and takes care of those waiting
	string readDelivery(string fileName);
	//Format's String for saving
	string saveInventory(void);
};

