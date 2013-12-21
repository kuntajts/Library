#include "StdAfx.h"
#include "Inventory.h"


Inventory::Inventory(void)
{
	myBT = new BookTracker;
	/*myBT->add("Moby Dick", 0, 5);
	myBT->add("Hansel and Gretel", 2, 5);
	myBT->add("Hunger Games", 0, 5);
	myBT->add("Harry Potter", 4, 1);
	myBT->addToWaitlist("Moby Dick", "Jordan");
	myBT->addToWaitlist("Moby Dick", "Jill");
	myBT->addToWaitlist("Moby Dick", "Jack");
	myBT->addToWaitlist("Moby Dick", "Mike");
	myBT->addToWaitlist("Hunger Games", "Jordan");
	myBT->addToWaitlist("Hunger Games", "Jill");
	myBT->addToWaitlist("Hunger Games", "Jack");
	myBT->addToWaitlist("Hunger Games", "Mike");
	
	^^ for testing */

	start();
}

//gives full list of actions that can be taken
void Inventory::help(void) {
	cout << "H (Help)" << endl;
	cout << "Provide a summary of all available commands." << endl << endl;

	cout << "I (Inquire)" << endl;
	cout << "Get information about a specific title" << endl << endl;

	cout << "L (List)" << endl;
	cout << "Get a list of the entire inventory in alphabetical order" << endl << endl;

	cout << "A (Add)" << endl;
	cout << "Add new book to the inventory" << endl << endl;

	cout << "M (Moddify)" << endl;
	cout << "Modify the current want value on a specific book" << endl << endl;

	cout << "O (Order)" << endl;
	cout << "Create a purchase order for additional books to level out have and want values" << endl << endl;

	cout << "D (Delivery)" << endl;
	cout << "Takes the information for a delivery and updates inventory" << endl << endl;

	cout << "R (Return)" << endl;
	cout << "return boks that were previoiusly delivered" << endl << endl;

	cout << "S (Sell)" << endl;
	cout << "Sell a book in the inventory or get it ordered" << endl << endl;

	cout << "Q (Quit)" << endl;
	cout << "Quit out this application" << endl;
}

//allows user to inquire about specific book
void Inventory::inquire(void) {
	cout << "INQUIRE" << endl;

	string title = "";
	cout << "Which book would you like to inquire about?" << endl;
	getline(cin, title);
	try {
		cout << myBT->getBookInfo(title) << endl;
	} catch (exception e) {
		cout << e.what() << endl;
	}
}

//prints a list of the current inventory
void Inventory::list(void) {
	cout << "LIST" << endl;
	cout << myBT->toString() << endl;
}

//adds a book to the inventory
void Inventory::add(void) {
	cout << "ADD" << endl;

	string title = "", forInt = "";
	int have = 0, want = 0;

	cout << "What title would you like to add?" << endl;
	getline(cin, title);
	cout << "What is the current have value for this book?" << endl;
	getline(cin, forInt);
	have = stoi(forInt);
	cout << "What is the current want value for this book?" << endl;
	getline(cin, forInt);
	want = stoi(forInt);
	
	if (title != "") {
		myBT->add(title, have, want);
		cout << endl << "The book " + title + " has been added." << endl;
	} else {
		cout << "You Must enter a valid book name" << endl;
	}
}

//modify's the want value of a specific book
void Inventory::modify(void) {
	cout << "MODIFY" << endl;

	string title = "", forInt = "";
	cout << "Which book would you like to modify?" << endl;
	getline(cin, title);
	try {
		cout << myBT->getBookInfo(title) << endl;

		int want = 0;
		cout << "What would you like to change the want value to?" << endl;
		getline(cin, forInt);
		want = stoi(forInt);
		myBT->changeWantValue(title, want);
		cout << "The want value for " + title + " has been changed." << endl;
	} catch (exception e) {
		cout << e.what() << endl;
	}
}

//prodcues output text file for order.
void Inventory::order(void) {
	cout << "ORDER" << endl;

	string fileName = "";
	cout << "What would you like the name of the order file to be? (without extentions)" << endl;
	getline(cin, fileName);
	myBT->printOrder(fileName);

	cout << "Your order has been outputed to " + fileName + ".txt" << endl;
}

void Inventory::returnInvoice(void) {
	cout << "RETURN" << endl;

	string fileName = "";
	cout << "What would you like the name of the return file to be? (without extentions)" << endl;
	getline(cin, fileName);
	myBT->printReturn(fileName);

	cout << "Your return invoice has been outputed to " + fileName + ".txt" << endl;
}

void Inventory::delivery(void) { 
	cout << "DELIVERY" << endl;

	try {
		string fileName = "";
		cout << "What is the name of the delivery file? (without extentions)" << endl;
		getline(cin, fileName);
		cout << myBT->readDelivery(fileName) << endl;
	} catch (logic_error e) {
		cout << e.what();
	}
}


//sells a book to the user if it is available
void Inventory::sell(void){
	cout << "SELL" << endl;

	string title = "", forInt = "";
	cout << "Which book would you like to sell?" << endl;
	getline(cin, title);
	try {
		myBT->sellBook(title);
	} catch (invalid_argument e) {
		int want = 0;
		string name = "";
		cout << e.what() << endl;
		cout << "We will add " + title + " to the inventory" << endl;
		cout << "What would you like the want value for this book to be?" << endl;
		getline(cin, forInt);
		want = stoi(forInt);
		while (name == "") {
			cout << "What is your name?" << endl;
			getline(cin, name);
		}
		
		myBT->add(title, 0, want);
		myBT->addToWaitlist(title, name);
	} catch (out_of_range x) {
		cout << x.what() << endl;
		cout << "We will add you to the wait list" << endl;

		string name = "";
		while (name == "") {
			cout << "What is your name?" << endl;
			getline(cin, name);
		}
		
		myBT->addToWaitlist(title, name);
	}
}

void Inventory::quit(void) {
	cout << myBT->saveInventory() << endl;
}

void Inventory::start(void) {
	string UInput = "";

	while (UInput != "Q") {
		cout << ">>";
		getline(cin, UInput);
		cout << endl;

		if (UInput == "H") {
			help();
		} else if (UInput == "I"){
			inquire();
		} else if (UInput == "A"){
			add();
		} else if (UInput == "M"){
			modify();
		} else if (UInput == "O"){
			order();
		} else if (UInput == "D"){
			delivery();
		} else if (UInput == "R"){
			returnInvoice();
		} else if (UInput == "S"){
			sell();
		} else if (UInput == "L"){
			list();
		} else if (UInput == "Q"){
			cout << "Quiting out of Application" << endl;
		} else {
			cout << "Invalid Input" << endl;
		}
		cout << endl;
	}

	quit();
	cout << "Press Enter to Close" << endl;
	cin >> UInput;
}

Inventory::~Inventory(void)
{
	delete myBT;
}
