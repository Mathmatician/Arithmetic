#include "LNM.h"

std::string LNM::Pi = "3.1415926535897932384626433832795028841971693993751058";

LNM::LNM(){ }

LNM::LNM(std::string val)
{
	if (val[0] == '-')
	{
		sub_negative = true;
		val.erase(0, 1);
	}
	else
		sub_negative = false;

	int i = 0;
	while (i < val.length())
	{
		if (val[i] == '.')
			break;

		integer.push_back(val[i] - '0');

		i++;
	}

	if (val[i] == '.')
		i++;

	while (i < val.length())
	{
		decimals.push_back(val[i] - '0');
		i++;
	}

	while (decimals.size() > 0 && decimals[decimals.size() - 1] == 0)
		decimals.pop_back();

	while (integer.size() > 0 && integer[0] == 0)
		integer.erase(integer.begin(), integer.begin() + 1);
}


void LNM::FlipSign()
{
	if (!sub_negative)
		sub_negative = true;
	else
		sub_negative = false;
}




// Alternative Addition Function
void LNM::Alt_Add(std::vector<int> first, std::vector<int> second, bool isDec)
{
	if (isDec)
	{
		if (decimals.size() > 0)
			decimals.clear();

		if (first.size() > second.size())
		{
			while (first.size() > second.size())
				second.push_back(0);
		}
		else if (first.size() < second.size())
		{
			while (first.size() < second.size())
				first.push_back(0);
		}
	}
	else if (integer.size() > 0)
			integer.clear();

	int len = 0;
	if (first.size() > second.size())
		len = first.size();
	else
		len = second.size();


	int carry = 0;
	if (integer_carry > 0)
		carry = integer_carry;

	for (int i = 0; i < len; i++)
	{
		int v = 0;
		if (i < first.size() && i < second.size())
			v = first[first.size() - 1 - i] + second[second.size() - 1 - i] + carry;
		else if (i < first.size())
			v = first[first.size() - 1 - i] + carry;
		else if (i < second.size())
			v = second[second.size() - 1 - i] + carry;

		if (v > 9)
		{
			v -= 10;
			carry = 1;
		}
		else
			carry = 0;

		if (isDec)
			decimals.push_back(v);
		else
			integer.push_back(v);
	}

	if (carry > 0)
	{
		if (!isDec)
			integer.push_back(carry);
		else
			integer_carry = carry;
	}

	if (!isDec)
	{
		while (integer.size() > 0 && integer[integer.size() - 1] == 0)
			integer.pop_back();
	}

	if (isDec)
		std::reverse(decimals.begin(), decimals.end());
	else
		std::reverse(integer.begin(), integer.end());

	if (isDec)
	{
		while (decimals.size() > 0 && decimals[decimals.size() - 1] == 0)
			decimals.pop_back();
	}
}







// Alternative Subtraction Function
void LNM::Alt_Subtract(std::vector<int> first, std::vector<int> second, bool isDec)
{
	if (first.size() > 0 || second.size() > 0)
	{
		if (isDec)
		{
			if (second.size() > first.size())
				while (second.size() > first.size())
					first.push_back(0);
			else if (second.size() < first.size())
				while (second.size() < first.size())
					second.push_back(0);
		}

		if (isDec)
		{
			if (decimals.size() > 0)
				decimals.clear();
		}
		else if (integer.size() > 0)
			integer.clear();

		int len = 0;
		if (first.size() > second.size())
		{
			len = first.size();
			if (isDec)
			{
				while (second.size() < first.size())
					second.push_back(0);
			}
		}
		else
			len = second.size();

		int carry = 0;
		if (integer_carry > 0)
			carry = integer_carry;

		if (first.at(0) < 0 && !isDec)
		{
			first.at(0) *= -1;
			sub_negative = true;
		}

		for (int i = 0; i < len; i++)
		{
			int v = 0;
			if (i < first.size() && i < second.size())
				v = first[first.size() - 1 - i] - second[second.size() - 1 - i] - carry;
			else if (i < first.size())
				v = first[first.size() - 1 - i] - carry;
			else if (i < second.size())
				v = second[second.size() - 1 - i] - carry;


			if (v < 0)
			{
				v += 10;
				carry = 1;
			}
			else
				carry = 0;


			if (isDec)
				decimals.push_back(v);
			else
				integer.push_back(v);
		}


		if (carry > 0)
		{
			if (isDec)
			{
				integer_carry = carry;
			}
		}


		if (!isDec)
		{
			while (integer.size() > 0 && integer[integer.size() - 1] == 0)
				integer.pop_back();
		}
		if (isDec)
			std::reverse(decimals.begin(), decimals.end());
		else
			std::reverse(integer.begin(), integer.end());

		if (isDec)
		{
			while (decimals.size() > 0 && decimals[decimals.size() - 1] == 0)
				decimals.pop_back();
		}
	}
}






/*-------------------
| Addition Function |
-------------------*/
void LNM::Add(LNM obj, LNM& result)
{
	if (obj.sub_negative && sub_negative)
	{
		result.FlipSign();
		result.Alt_Add(obj.decimals, decimals, true);
		result.Alt_Add(obj.integer, integer, false);
	}
	else if (obj.sub_negative && !sub_negative)
	{
		result.FlipSign();
		sub_negative = true;
		Subtract(obj, result);
	}
	else if (!obj.sub_negative && sub_negative)
	{
		obj.sub_negative = true;
		Subtract(obj, result);
	}
	else
	{
		result.Alt_Add(obj.decimals, decimals, true);
		result.Alt_Add(obj.integer, integer, false);
	}
}









/*----------------------
| Subtraction Function |
----------------------*/
void LNM::Subtract(LNM obj, LNM& result)
{
	if (sub_negative && obj.sub_negative)
		result.FlipSign();

	if (sub_negative && !obj.sub_negative)
	{
		obj.sub_negative = true;
		Add(obj, result);
	}
	else if (!sub_negative && obj.sub_negative)
	{
		obj.sub_negative = false;
		Add(obj, result);
	}
	else if (integer.size() > obj.integer.size())
	{
		result.Alt_Subtract(decimals, obj.decimals, true);
		result.Alt_Subtract(integer, obj.integer, false);
	}
	else if (integer.size() < obj.integer.size())
	{
		result.FlipSign();
		result.Alt_Subtract(obj.decimals, decimals, true);
		result.Alt_Subtract(obj.integer, integer, false);
	}
	else
	{
		bool firstIsBigger = false;
		bool secondIsBigger = false;
		for (int i = 0; i < integer.size(); i++)
		{
			if (integer[i] < obj.integer[i])
			{
				secondIsBigger = true;
				break;
			}
			else if (integer[i] > obj.integer[i])
			{
				firstIsBigger = true;
				break;
			}
		}

		if (!secondIsBigger && !firstIsBigger)
		{
			int len = 0;
			if (decimals.size() > obj.decimals.size())
				len = decimals.size();
			else
				len = obj.decimals.size();

			if (decimals.size() > obj.decimals.size())
				firstIsBigger = true;
			else if (decimals.size() < obj.decimals.size())
				secondIsBigger = true;
			else if (decimals.size() > 0 && obj.decimals.size() > 0)
			{
				for (int i = 0; i < len; i++)
				{
					if (decimals[i] < obj.decimals[i])
					{
						secondIsBigger = true;
						break;
					}
					else if (decimals[i] > obj.decimals[i])
					{
						firstIsBigger = true;
						break;
					}
				}
			}
		}

		if (firstIsBigger)
		{
			result.Alt_Subtract(decimals, obj.decimals, true);
			result.Alt_Subtract(integer, obj.integer, false);
		}
		else if (secondIsBigger)
		{
			result.FlipSign();
			result.Alt_Subtract(obj.decimals, decimals, true);
			result.Alt_Subtract(obj.integer, integer, false);
		}
	}
}






/*-------------------------
| Multiplication Function |
-------------------------*/
void LNM::Multiply(LNM obj, LNM& result)
{
	if ( (!obj.sub_negative && sub_negative) || (obj.sub_negative && !sub_negative) )
		result.sub_negative = true;

	LNM num("0");
	LNM res("0");

	int carry = 0;
	int J = 0;
	int I = 0;

	for (int i = 0; i < obj.integer.size() + obj.decimals.size(); i++)
	{
		J = 0;
		std::vector<int> val;
		for (int j = 0; j < integer.size() + decimals.size(); j++)
		{
			int v1 = 0;
			int v2 = 0;

			if (j < decimals.size())
				v1 = decimals[decimals.size() - 1 - j];
			else
			{
 				v1 = integer[integer.size() - 1 - J];
				J++;
			}

			if (i < obj.decimals.size())
				v2 = obj.decimals[obj.decimals.size() - 1 - i];
			else
				v2 = obj.integer[obj.integer.size() - 1 - I];

			int v = v1 * v2 + carry;

			carry = 0;
			while (v > 9)
			{
				v -= 10;
				carry++;
			}

			val.push_back(v);
		}

		if (carry > 0)
		{
			val.push_back(carry);
			carry = 0;
		}

		while (val.size() > 0)
		{
			num.integer.push_back(val[val.size() - 1]);
			val.pop_back();
		}

		for (int k = 0; k < i; k++)
			num.integer.push_back(0);

		res = res + num;
		num.integer.clear();

		if (i >= obj.decimals.size())
			I++;
	}
	
	int totInts = res.integer.size() - (obj.decimals.size() + decimals.size());

	if (totInts > 0)
	{
		for (int i = 0; i < totInts; i++)
		{
			if (res.integer.size() > 0)
			{
				result.integer.push_back(res.integer[0]);
				res.integer.erase(res.integer.begin(), res.integer.begin() + 1);
			}
		}
	}
	else
	{
		for (int i = 0; i > totInts; i--)
			result.decimals.push_back(0);
	}

	while (res.integer.size() > 0)
	{
		result.decimals.push_back(res.integer[0]);
		res.integer.erase(res.integer.begin(), res.integer.begin() + 1);
	}

	while (result.decimals.size() > 0 && result.decimals[result.decimals.size() - 1] == 0)
		result.decimals.pop_back();
}






/*-------------------
| Division Function |
-------------------*/
void LNM::Divide(LNM obj, LNM& result)
{
	
}





bool LNM::isLessThan(LNM obj, bool init_bool)
{
	bool firstIsNegative = false;
	bool secondIsNegative = false;

	if (integer.size() < obj.integer.size())
	{
		if (!obj.sub_negative)
			return init_bool;

		return !init_bool;
	}
	else if (integer.size() > obj.integer.size())
	{
		if (!sub_negative)
			return !init_bool;

		return init_bool;
	}
	else
	{
		bool firstIsBigger = false;
		bool secondIsBigger = false;
		if (integer.size() > 0 && obj.integer.size() > 0)
		{
			for (int i = 0; i < integer.size(); i++)
			{
				if (integer[i] < obj.integer[i])
				{
					secondIsBigger = true;
					break;
				}
				else if (integer[i] > obj.integer[i])
				{
					firstIsBigger = true;
					break;
				}
			}

			if (firstIsBigger && !sub_negative)
				return !init_bool;
			if (firstIsBigger && sub_negative)
				return init_bool;
			if (secondIsBigger && !obj.sub_negative)
				return init_bool;
			if (secondIsBigger && obj.sub_negative)
				return !init_bool;

			if (decimals.size() == 0 && obj.decimals.size() > 0)
				return init_bool;
			if (obj.decimals.size() == 0 && decimals.size() > 0)
				return !init_bool;

			int len = 0;
			if (decimals.size() > obj.decimals.size())
				len = obj.decimals.size();
			else
				len = decimals.size();

			int i = 0;
			while (i < len)
			{
				if (decimals[i] > obj.decimals[i])
				{
					firstIsBigger = true;
					break;
				}
				if (decimals[i] < obj.decimals[i])
				{
					secondIsBigger = true;
					break;
				}
			}

			if (!firstIsBigger && !secondIsBigger)
			{
				if (decimals.size() > obj.decimals.size())
					firstIsBigger = true;
				else if (decimals.size() < obj.decimals.size())
					secondIsBigger = true;
			}

			if (firstIsBigger && !sub_negative)
				return !init_bool;
			if (firstIsBigger && sub_negative)
				return init_bool;
			if (secondIsBigger && !sub_negative)
				return init_bool;
			else if (secondIsBigger && sub_negative)
				return !init_bool;
		}
	}

	return false;
}








bool LNM::isEqualTo(LNM obj)
{
	if (integer.size() > obj.integer.size())
		return false;
	if (integer.size() < obj.integer.size())
		return false;
	if (sub_negative != obj.sub_negative)
		return false;
	if (decimals.size() > obj.decimals.size())
		return false;
	if (decimals.size() < obj.decimals.size())
		return false;

	for (int i = 0; i < integer.size(); i++)
	{
		if (integer[i] > obj.integer[i] || integer[i] < obj.integer[i])
			return false;
	}

	for (int i = 0; i < decimals.size(); i++)
	{
		if (decimals[i] > obj.decimals[i] || decimals[i] < obj.decimals[i])
			return false;
	}

	return true;
}



