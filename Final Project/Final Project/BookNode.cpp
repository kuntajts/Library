#include "StdAfx.h"
#include "BookNode.h"

//constructor taking the values for the book name and have and want values
BookNode::BookNode(string bookNameIn, int haveValueIn, int wantValueIn)
{
	bookName = bookNameIn;
	haveValue = haveValueIn;
	wantValue = wantValueIn;
	list = new WaitList();
	next = nullptr;
}

//updates the have value
void BookNode::addToHaveValue(int update) {
	if (update > 0) {
		haveValue = haveValue + update;
	} else if (update < 0) {
		if (haveValue != 0) {
			int positiveUpdate = update*-1;
			for (int i = 0; i < positiveUpdate && haveValue != 0; i++) {
				haveValue =- 1;
			}

			//if the have value went to zero before finishing program
			if (haveValue == 0) {
				throw out_of_range(bookName + " is out of stock"); 
			}
		} else {
			//throw if there are no books currently
			throw out_of_range(bookName + " is out of stock");
		}
	}
}


int BookNode::getWantValue(void) {
	return wantValue;
}

int BookNode::getHaveValue(void) {
	return haveValue;
}

string BookNode::getBookName(void) {
	return bookName;
}

//sets next book node to input node
void BookNode::setNext(BookNode *BN) {
	next = BN;
}

//change want value
void BookNode::setWantValue(int newValue) {
	wantValue = newValue;
}

//returns pointer to the next BookNode.
BookNode* BookNode::getNext(void) {
	return next;
}

WaitList* BookNode::getList(void) {
	return list;
}

string BookNode::removeCostumer(void) {
	string result = list->dequeue();
	haveValue--;

	return result;
}


//formated string for output
string BookNode::toString(void) {
	char forString[21];

	string toString = "";
	toString = toString + bookName + "\n";
	toString = toString + "Have Value: " + itoa(haveValue, forString, 10) + "\n";
	toString = toString + "Want Value: " + itoa(wantValue, forString, 10) + "\n";
	toString = toString + "WaitList:\n";
	try {
		toString = toString + list->toString();
	} catch (exception e) {
		toString = toString + "No one waiting for this book";
	}

	return toString + "\n";
}

BookNode::~BookNode(void)
{
	delete list;
}
