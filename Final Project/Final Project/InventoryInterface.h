#pragma once
#include <string>
#include <iostream>
using namespace std;

class InventoryInterface
{
public:
	//Provide a summary of all available commands.
	virtual void help(void)=0;

	//Display the information for a specified title.
	virtual void inquire(void)=0;

	//List the information for the entire inventory (in alphabetical order by title)
	virtual void list (void)=0;

	//Add a book to the inventory. Prompt for initial want value. 
	//If the title already exists, inform the user and print the information for that title.
	virtual void add(void)=0;

	//Modify the want value for the specified title. 
	//Display current want value, and prompt user for new want value.
	virtual void modify(void)=0;

	//Create a purchase order for additional books based on a comparison 
	//of the have and want values in the inventory, so that the have 
	//value is brought up to the want value.
	virtual void order(void)=0;

	//Take information from a delivery shipment of books, in a file.  
	//The file will contain the title and the count of each book shipped. 
	//Read the file, and update the "have" values in the inventory accordingly. 
	//Note that the program must add an item to the inventory if the 
	//delivered title is not present in the current inventory.
	//if there is a wait list for books delivered, the program 
	//should print the title of the book and the name of the person it should 
	//be put on hold for. The book should then be considered sold (the person should be removed 
	//from wait list, and the want value updated accordingly). 
	virtual void delivery(void)=0;

	//Write a return invoice to a file specifying books to be returned. 
	//This should bring the have value down to the want value for each book in the inventory.
	virtual void returnInvoice(void)=0;

	//Decrease the count for the specified title by 1.  
	//If the title doesn't exist yet, it should be added. 
	//If the title is sold out (or didn't exist), prompt the user 
	//for the buyer's name and enter them on the wait list.  
	virtual void sell(void)=0;

	//Save the inventory and wait lists in a file and terminate execution.
	virtual void quit(void)=0;
};
