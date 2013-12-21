#include "StdAfx.h"
#include "BookTracker.h"

//class for sanatizing a string of non lowercase characters
string cleanString(string myString) {
	int size = myString.length();
	string newstring = "";
	for (int i = 0; i < size; i++) {
		if (myString[i] >= 'A' && myString[i] <= 'Z') {
			int lower = myString[i];
			lower = lower + 32; //32 is the ascii offset
			newstring = newstring + (char) lower;
		} else if (myString[i] >= 'a' && myString[i] <= 'z') {
			newstring = newstring + myString[i];
		}
	}
	return newstring;
}


BookTracker::BookTracker(void)
{
	head = nullptr;
	readInFile();
}

//adding a book in alphabetical order
void BookTracker::add(string bookName, int haveValue, int wantValue) {
	BookNode *bookNode = new BookNode(bookName, haveValue, wantValue);
	if (head == nullptr) {
		head = bookNode;
	} else {
		//if book is found print out info
		try {
			bookNode = findBook(bookName);
			cout << "Book was already added" << endl;
			cout << bookNode->toString() << endl;
		//if exception is caught proceed to add book
		} catch (exception e) {
			BookNode *current = head;
			BookNode *previous = head;
			while (current != nullptr && bookNode->getBookName().compare(current->getBookName()) > 0) {
				previous = current;
				current = current->getNext();
			}

			//if the book being added belongs at the head
			if (current == head) { 
				bookNode->setNext(head);
				head = bookNode;
			} else {
				bookNode->setNext(current);
				previous->setNext(bookNode);
			}
		}
	}
}

//remove a book from the list of books
//after correcting strings;
bool BookTracker::remove(string bookName) {
	if (head == nullptr) {
		return false;
	} else {
		bookName = cleanString(bookName);
		BookNode *itorator = head;
		while (itorator->getNext() != nullptr) {
			string nextBookName = cleanString(itorator->getNext()->getBookName());
			if (nextBookName == bookName) {
				BookNode *patch = itorator;
				itorator = itorator->getNext();
				patch->setNext(itorator->getNext());
				delete itorator;
				return true;
			} else {
				itorator = itorator->getNext();
			}
		}
	}

	return false;
}

//removes next person from queue
void BookTracker::sellBook(string bookNameIn) {
	try {
		BookNode *node = findBook(bookNameIn);
		WaitList *list = node->getList();
		//if the list is not empty
		if (list->peek() != nullptr) {
			throw out_of_range("There are people waiting for this book. ");
		} 
		node->addToHaveValue(-1);
	} catch (invalid_argument e) {
		//rethrow error
		throw e;
	} catch (out_of_range x) {
		//rethrow error
		throw x;
	}
}

//adds new costumer to waiting list 
void BookTracker::addToWaitlist(string bookNameIn, string costumerNameIn) {
	try {
		BookNode *node = findBook(bookNameIn);
		WaitList *list = node->getList();
		list->enqueue(costumerNameIn);
	} catch (logic_error e) {
		//rethrow error
		throw e;
	}
}

//finds book from book name
BookNode* BookTracker::findBook(string bookName) {
	if (head == nullptr) {
		throw invalid_argument("Inventory is empty!");
	} else {
		//sanatize bookName
		bookName = cleanString(bookName);
		BookNode *itorator = head;
		while (itorator != nullptr) {
			//sanitize the itorator's bookName
			if (cleanString(itorator->getBookName()) == bookName) {
				return itorator;
			} else {
				itorator = itorator->getNext();
			}
		}
	}

	throw invalid_argument(bookName + " could not be found");
}

//returns name of the book at the head
string BookTracker::getHead(void) {
	return head->getBookName();
}



//formated output for user
string BookTracker::toString(void) {
	string toString = "";
	if (head != nullptr) {
		BookNode* itorator = head;
		while (itorator != nullptr) {
			toString = toString + itorator->toString() + "\n";
			itorator = itorator->getNext();
		}
	} else {
		toString = "Inventory is empty!";
	}

	return toString;
}

//get's book information for specific book
string BookTracker::getBookInfo(string bookName) {
	try {
		BookNode *node = findBook(bookName);
		return node->toString();
	} catch (exception e) {
		//rethrow exception
		throw e;
	}
}

//method for changing the want value of a 
//specific book.
void BookTracker::changeWantValue(string bookName, int newValue) {
	try {
		BookNode *node = findBook(bookName);
		node->setWantValue(newValue);
	} catch(exception e) {
		//rethrow error
		throw e;
	}
}
string BookTracker::saveInventory(void) {
	ofstream outfile("SavedInventory.txt");
	
	if (outfile.is_open()) { 
		if (head != nullptr) {
			BookNode *current = head;
			while (current != nullptr) {
				WaitList *list = current->getList();
				//bookinfo first
				outfile << current->getBookName() << "~" << current->getHaveValue() << "~" << current->getWantValue();
				//waitlist info second
				if (list->peek() == nullptr) {
					outfile << "*null~";
				} else {
					Costumer *cos = list->peek();
					outfile << "*";
					while (cos != nullptr) {
						outfile << cos->getName() << "~";
						cos = cos->getNext();
					}
				}
				outfile << endl;
				current = current->getNext();
			}
		}
		outfile.close();
	} else {
		return "File could not be oppened";
	}

	return "File has been saved to SavedInventory.txt\n";
}

void BookTracker::readInFile(void) {
	ifstream infile("SavedInventory.txt");
	string line = "";
	string result = "";
	if (infile.is_open()) {
		while (getline(infile, line)) {
			addBookFromString(line);
			infile.clear();
		}
		infile.close();
	}
}

void BookTracker::addBookFromString(string line) {
	string word = "";

	const int PARAMTYPES = 2;
	string bookAndListParams[PARAMTYPES];
	stringstream splitter(line);

	for (int i = 0; i < PARAMTYPES; i++) {
		if (getline(splitter, word, '*')) {
			bookAndListParams[i] = word;
		}
	}

	stringstream bookSplitter(bookAndListParams[0]);
	const int BOOKPARAMS = 3;
	string bookParams[BOOKPARAMS];
	for (int i = 0; i < BOOKPARAMS; i++) {
		if (getline(bookSplitter, word, '~')) {
			bookParams[i] = word;
		}
	}

	int have, want;
	string name = "";
	//store params for creation 
	name = bookParams[0];
	have = stoi(bookParams[1]);
	want = stoi(bookParams[2]);
	//add book
	add(name, have, want);
	//add waitlist
	stringstream waitSplitter(bookAndListParams[1]);
	while (getline(waitSplitter, word, '~')) {
		if (word != "null" && word != "") {
			addToWaitlist(name, word);
		}
	}
}

//responsible for printing out the order.
void BookTracker::printOrder(string fileName) {
	ofstream outfile(fileName + ".txt");
	
	if (outfile.is_open()) { //successful open
		outfile << "Order Reciept" << endl;

		if (head != nullptr) { //check if inventory is not empty
			char forString[21];
			int i = 1, orderNumber = 0; 
			BookNode *current = head;
			
			while (current != nullptr) {
				outfile << "*******************************************" << endl;
				outfile << itoa(i, forString, 10) << ": " + current->getBookName() << endl;
				if (current->getHaveValue() < current->getWantValue()) {
					orderNumber = current->getWantValue() - current->getHaveValue(); //subtract for difference
					outfile << "Need " << itoa(orderNumber, forString, 10) << " more copies of this book." << endl << endl;
				} else {
					outfile << "This book has does not need to be orded anymore" << endl << endl;
				}

				current = current->getNext();
				i++;
			}
		} else {
			outfile << "Inventory is empty" << endl;
		}
		outfile.close();
	}
}


//responsible for printing out the return.
void BookTracker::printReturn(string fileName) {
	ofstream outfile(fileName + ".txt");
	
	if (outfile.is_open()) { //successful open
		outfile << "Return Reciept" << endl;

		if (head != nullptr) { //check if inventory is not empty
			char forString[21];
			int i = 1, returnNumber = 0; 
			BookNode *current = head;
			
			while (current != nullptr) {
				outfile << "*******************************************" << endl;
				outfile << itoa(i, forString, 10) << ": " + current->getBookName() << endl;
				if (current->getHaveValue() > current->getWantValue()) {
					returnNumber = current->getHaveValue() - current->getWantValue(); //subtract for difference
					outfile << "Need to return " << itoa(returnNumber, forString, 10) << " copies of this book." << endl << endl;
				} else {
					outfile << "This book does not need any returns" << endl << endl;
				}

				current = current->getNext();
				i++;
			}
		} else {
			outfile << "Inventory is empty" << endl;
		}
		outfile.close();
	}
}

//reads delivery from text file and sends for processing
//returns books that must be given to those in the waitlist
string BookTracker::readDelivery(string fileName) {
	ifstream infile(fileName + ".txt");
	string line = "";
	string result = "";
	if (infile.is_open()) {
		while (getline(infile, line)) {
			try {
				result = result + (addBookFromDeliveryString(line));
				infile.clear();
			} catch (exception e) {
			}
		}
		infile.close();
	} else {
		throw invalid_argument("file not found");
	}

	return result;
}

//adds a book from formatted string with delimitor 
//returns book with those off waitlist
string BookTracker::addBookFromDeliveryString(string lineIn) {
	string line = lineIn;
	string word = "";
	const int NUMOFPARAMS = 3;

	//get params in a array
	string bookParams[NUMOFPARAMS];
	stringstream splitter(line);
	for (int i = 0; i < NUMOFPARAMS; i++) {
		if (getline(splitter, word, '~')) {
			bookParams[i] = word;
		}
	}

	int have, want;
	string name = "";
	//store params for creation 
	name = bookParams[0];
	have = stoi(bookParams[1]);
	want = stoi(bookParams[2]);

	try {
		string result = "";
		BookNode *node = findBook(name);
		node->addToHaveValue(have);
		node->setWantValue(want);
		result = emptyWaitList(name);
		return result;
	} catch (logic_error e) { //add book if not found
		add(name, have, want);
		return "The book " + name + " has been added to the Inventory.";
	}

	return "";

}

//dequeue people
string BookTracker::emptyWaitList(string bookName) {
	string result = "";
	try {
		BookNode *node = findBook(bookName);
		WaitList *list = node->getList();

		if (list->peek() != nullptr) {
			result = bookName;
			int maxHave = node->getHaveValue();
			for (int i = 0; i < maxHave && list->peek() != nullptr; i++) {
				result = result + "\n\t";
				result = result + node->removeCostumer();
			}
			result = result + "\nHave all been removed from " + bookName + "'s waiting list\n\n";
		}
		return result;
	} catch (logic_error e) {
		//rethrow
		throw e;
	}

	return result;
}

BookTracker::~BookTracker(void)
{
	if (head != nullptr) {
		BookNode* current = head;
		//walk down list and call delete on each individual Costumer
		while (current != nullptr){
			BookNode* temp = current->getNext();
			delete current;
			current = temp;
		}
		head = nullptr;
	}
}
