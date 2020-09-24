#pragma once
#include <iostream>
#include <string>
#include <vector>
class LNM {
private:

	int integer_carry = 0;
	bool sub_negative = false;

	void Add(LNM, LNM&);
	void Alt_Add(std::vector<int>, std::vector<int>, bool);

	void Subtract(LNM, LNM&);
	void Alt_Subtract(std::vector<int>, std::vector<int>, bool);

	void Multiply(LNM, LNM&);
	void Divide(LNM, LNM&);

	bool isLessThan(LNM, bool);
	bool isEqualTo(LNM);

	void FlipSign();

protected:
	std::vector<int> integer;
	std::vector<int> decimals;

public:
	static std::string precision;
	static std::string Pi;

	LNM();
	LNM(std::string);

	LNM operator + (LNM const &obj)
	{
		LNM result;
		Add(obj, result);
		return result;
	}

	LNM operator - (LNM const& obj)
	{
		LNM result;
		Subtract(obj, result);
		return result;
	}

	LNM operator * (LNM const& obj)
	{
		LNM result;
		Multiply(obj, result);
		return result;
	}

	LNM operator/(LNM const& obj)
	{
		LNM result;
		return result;
	}

	friend std::ostream &operator << (std::ostream &out, const LNM &obj)
	{
		if (obj.sub_negative)
			std::cout << '-';

		if (obj.integer.size() > 0)
		{
			for (int i = 0; i < obj.integer.size(); i++)
			{
				std::cout << obj.integer[i];
			}
		}
		else
			std::cout << "0";
		
		if (obj.decimals.size() > 0)
		{
			std::cout << ".";
			for (int i = 0; i < obj.decimals.size(); i++)
			{
				std::cout << obj.decimals[i];
			}
		}
		return out;
	}

	void operator = (const LNM &obj)
	{
		integer.clear();
		decimals.clear();
		if (obj.integer.size() > 0)
			for (int i = 0; i < obj.integer.size(); i++)
				integer.push_back(obj.integer[i]);

		if (obj.decimals.size() > 0)
			for (int i = 0; i < obj.decimals.size(); i++)
				decimals.push_back(obj.decimals[i]);

		if (obj.sub_negative)
			sub_negative = true;
		else
			sub_negative = false;
	}

	bool operator < (const LNM& obj)
	{
		return isLessThan(obj, true);
	}

	bool operator > (const LNM& obj)
	{
		return isLessThan(obj, false);
	}

	bool operator >= (const LNM& d)
	{
		return false;
	}

	bool operator == (const LNM& obj)
	{
		return isEqualTo(obj);
	}

	bool operator != (const LNM& obj)
	{
		return !isEqualTo(obj);
	}
};

