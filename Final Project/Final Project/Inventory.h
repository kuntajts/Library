#pragma once
#include "InventoryInterface.h"
#include "BookTracker.h"

class Inventory : public InventoryInterface
{
private: 
	BookTracker *myBT;
public:
	Inventory(void);
	//deletes all nodes
	~Inventory(void);

	//function displaying all options
	void help(void);

	//inquire about a specific book
	void inquire(void);

	//List the current books in Inventory
	void list(void);

	//add a  book to the inventory
	void add(void);

	//modify a want value of a book currently in the inventory
	void modify(void);

	//outputs file for order
	void order(void);

	//sells a specific book
	void sell(void);

	//takes a file for delivery
	void delivery(void);
	
	//outputs file for return
	void returnInvoice(void);

	//quits out of the interface
	void quit(void);

	//handles input for other functions
	void start(void);
};

