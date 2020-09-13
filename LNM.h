#pragma once
#include <iostream>
#include <string>
class LNM {
private:
	std::string Add(std::string, std::string);
	std::string Subtract(std::string, std::string);
	std::string Multiply(std::string, std::string);
	std::string Divide(std::string, std::string);

	bool isGreaterThan(std::string, std::string);

protected:
	std::string num;

public:
	static std::string precision;

	LNM();
	LNM(std::string);

	LNM operator+(LNM const &obj)
	{
		LNM result = Add(num, obj.num);
		return result;
	}

	LNM operator-(LNM const& obj)
	{
		LNM result = Subtract(num, obj.num);
		return result;
	}

	LNM operator*(LNM const& obj)
	{
		LNM result = Multiply(num, obj.num);
		return result;
	}

	LNM operator/(LNM const& obj)
	{
		LNM result = Divide(num, obj.num);
		return result;
	}

	friend std::ostream &operator << (std::ostream &out, const LNM &obj)
	{
		std::cout << obj.num;
		return out;
	}

	void operator= (const LNM &obj)
	{
		num = obj.num;
	}
};

