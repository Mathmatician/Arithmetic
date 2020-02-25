// Author: Jerome Richards
// Start Date: 02/24/2020
// Last Date Edited: 02/24/2020

#include "LNM.h"

LNM::LNM()
{
	number = "0";
}

LNM::LNM(std::string obj)
{
	number = obj;
}

LNM::LNM(std::string obj1, std::string obj2)
{
	number = Add(obj1, obj2);
}

LNM::LNM(LNM obj1, LNM obj2)
{
	number = Add(obj1.getNumber(), obj2.getNumber());
}



std::string LNM::Add(std::string obj1, std::string obj2)
{
	std::string s = obj1 + " + " + obj2;
	return s;
}

const std::string LNM::getNumber()
{
	return number;
}

void LNM::setNumber(std::string obj)
{
	number = obj;
}

void LNM::operator= (const LNM& obj)
{
	number = obj.number;
}

void LNM::operator= (const std::string& obj)
{
	number = obj;
}
