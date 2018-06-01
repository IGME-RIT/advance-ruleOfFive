//Rule of five includes the move constructor and move assignment operator along with the Big three i.e Copy constructor, copy assignment operator, and destructor
//This program has the implementation of "move constructor and move assignment operator"
//For the examples of the Big three please refer: https://github.com/IGME-RIT/advance-ruleOfThree

#include<iostream>
#include<conio.h>
#include<string.h>
using namespace std;

class RuleOfFive
{
	char* cstring; // raw pointer used as a handle to a dynamically-allocated memory block

public:	
	
	RuleOfFive(const char* arg)
		: cstring(new char[strlen(arg) + 1]) // allocate
	{
		strcpy(cstring, arg); // populate
	}
	
	~RuleOfFive()
	{
		delete[] cstring;  // deallocate
	}
	
	RuleOfFive(const RuleOfFive& other) // copy constructor
	{
		cstring = new char[strlen(other.cstring) + 1];
		strcpy(cstring, other.cstring);
	}
	
	RuleOfFive(RuleOfFive&& other) : cstring(other.cstring) // move constructor
	{
		cout << "Move constructor called" << endl;

		other.cstring = nullptr;
	}
	
	RuleOfFive& operator=(const RuleOfFive& other) // copy assignment
	{
		char* tmp_cstring = new char[strlen(other.cstring) + 1];
		strcpy(tmp_cstring, other.cstring);
		delete[] cstring;
		cstring = tmp_cstring;
		return *this;
	}
	
	RuleOfFive& operator=(RuleOfFive&& other) // move assignment
	{
		cout << "Move assignment operator called" << endl;

		if (this != &other) // prevent self-move
		{
			delete[] cstring;
			cstring = other.cstring;
			other.cstring = nullptr;
		}
		return *this;
	}

	void print()
	{
		cout << cstring << endl;
	}
};

int main()
{
	RuleOfFive r("hello world");
	r.print();
	
	RuleOfFive r1(r);				//Copy Constructor
	r1.print();

	RuleOfFive r2 = move(r);		//Move Constructor
	r2.print();
	//r.print();					//Throws an excpetion since the string in object r has be moved to r2 and r now points to nullptr

	RuleOfFive r3("hello world, the second time");
	RuleOfFive r4("Nothing here");

	cout << "Before move assignment operator called" << endl;

	r3.print();
	r4.print();

	r4 = move(r3);

	cout << "After move assignment operator called" << endl;

	//r3.print();					//Throws an exception since the string in object r3 has now been assigned to r4;
	r4.print();

	_getch();

	return 0;
}