#pragma once
#include <string>
using namespace std;

class Costumer
{
private:
	string name;
	Costumer *next;
public:
	//constructor which takes in the costumer name as data
	Costumer(string nameIn);
	~Costumer(void);

	//sets name
	void setName(string);
	//sets the next node
	void setNext(Costumer*);
	//returns name
	string getName(void);
	//returns next node
	Costumer* getNext(void);
};

