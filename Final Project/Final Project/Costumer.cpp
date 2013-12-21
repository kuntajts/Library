#include "StdAfx.h"
#include "Costumer.h"

//constructor for setting the name
Costumer::Costumer(string nameIn)
{
	name = nameIn;
}

//sets the customer's name to something different
void Costumer::setName(string nameIn) {
	name = nameIn;
}

//returns next costumer
void Costumer::setNext(Costumer* newCostumer) {
	next = newCostumer;
}

string Costumer::getName(void) {
	return name;
}

Costumer* Costumer::getNext(void) {
	return next;
}

Costumer::~Costumer(void)
{
}
