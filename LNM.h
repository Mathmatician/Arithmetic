// Author: Jerome Richards
// Start Date: 02/24/2020

#include <iostream>
#include <string>

class LNM {
private:
	std::string number; // The number that holds the actual number value
	std::string Add(std::string, std::string); // Adds two string numbers, provided they are valid numbers


public:
	/*--------------
	| Constructors |
	---------------*/
	LNM(); // Initializes number to 0
	LNM(std::string); // Initializes number by the given string parameter
	LNM(std::string, std::string); // Adds two string numbers and stores it in number
	LNM(LNM, LNM); // Takes two LMN data types and adds their numbers to store in number

	void setNumber(std::string); // Sets number
	const std::string getNumber(); // Returns number


	/*-----------------------------------
	| Overloading the addition operator |
	------------------------------------*/
	friend LNM operator+(const LNM& obj1, const LNM& obj2)
	{
		LNM test(obj1, obj2);
		return test;
	}


	/*------------------------------------
	| Overloading the insertion operator |
	-------------------------------------*/
	friend std::ostream& operator<<(std::ostream& os, const LNM& obj)
	{
		os << obj.number;
		return os;
	}


	/*----------------------------------
	| Overloading assignment operators |
	-----------------------------------*/
	void operator= (const LNM& obj);
	void operator= (const std::string& obj);

};


