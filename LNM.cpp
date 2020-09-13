#include "LNM.h"
#include <string>
#include <vector>

LNM::LNM()
{
	num = "0";
}

LNM::LNM(std::string val)
{
	num = val;
}


bool CheckForChar(std::string s, char c)
{
	for (int i = 0; i < s.length(); i++)
		if (s[i] == c)
			return true;

	return false;
}






/*-------------------
| Addition Function |
-------------------*/
std::string LNM::Add(std::string first, std::string second)
{
	bool isNegative = false;
	if (first[0] == '-' && second[0] == '-')
	{
		isNegative = true;
		first.erase(0, 1);
		second.erase(0, 1);
	}
	else if (first[0] == '-' && second[0] != '-')
	{
		first.erase(0, 1);
		return Subtract(second, first);
	}
	else if (first[0] != '-' && second[0] == '-')
	{
		second.erase(0, 1);
		return Subtract(first, second);
	}

	// Count number of decimals for the first
	int numOfDec_f = 0;
	int numOfInts_f = 0;
	int index = 0;
	bool decPointStart = false;
	while (index < first.length())
	{
		if (decPointStart)
		{
			numOfDec_f++;
			index++;
		}
		else if (first[index] == '.')
		{
			decPointStart = true;
			first.erase(index, 1);
		}
		else
		{
			numOfInts_f++;
			index++;
		}
	}

	// Count number of decimals for the second
	int numOfDec_s = 0;
	int numOfInts_s = 0;
	index = 0;
	decPointStart = false;
	while (index < second.length())
	{
		if (decPointStart)
		{
			numOfDec_s++;
			index++;
		}
		else if (second[index] == '.')
		{
			decPointStart = true;
			second.erase(index, 1);
		}
		else
		{
			numOfInts_s++;
			index++;
		}
	}

	int finNumOfDecs = 0;
	if (numOfDec_f > numOfDec_s)
		finNumOfDecs = numOfDec_f;
	else if (numOfDec_f < numOfDec_s)
		finNumOfDecs = numOfDec_s;
	else
		finNumOfDecs = numOfDec_f;

	std::string f = first;
	std::string s = second;
	std::string result = "";

	int len;
	if (numOfInts_f > numOfInts_s)
	{
		len = numOfInts_f - numOfInts_s;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		s = str + s;
	}
	else if (numOfInts_f < numOfInts_s)
	{
		len = numOfInts_s - numOfInts_f;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		f = str + f;
	}

	if (numOfDec_f > numOfDec_s)
	{
		len = numOfDec_f - numOfDec_s;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		s = s + str;
	}
	else if (numOfDec_f < numOfDec_s)
	{
		len = numOfDec_s - numOfDec_f;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		f = f + str;
	}

	len = f.length();
	
	int carry = 0;
	int i = 0;
	while (i < len)
	{
		int v1 = f[f.length() - 1 - i] - '0';
		int v2 = s[s.length() - 1 - i] - '0';
		int vf = v1 + v2 + carry;
		std::string vs = std::to_string(vf);

		if (vs.length() > 1)
			carry = vs[0] - '0';
		else
			carry = 0;

		if (i == finNumOfDecs && finNumOfDecs > 0)
			result += '.';

		result += vs[vs.length() - 1];

		i++;
	}

	if (carry > 0)
		result += std::to_string(carry);

	std::string RESULT = "";

	if (isNegative)
		RESULT += '-';

	len = result.length();
	for (i = len; i > 0; i--)
	{
		RESULT += result[i - 1];
	}

	return RESULT;
}







/*----------------------
| Subtraction Function |
----------------------*/
std::string LNM::Subtract(std::string first, std::string second)
{
	if (first[0] == '-' && second[0] == '-')
	{
		first.erase(0, 1);
		second.erase(0, 1);

		// swap
		std::string tmp = first;
		first = second;
		second = tmp;
	}
	else if (first[0] == '-' && second[0] != '-')
	{
		return Add(first, "-" + second);
	}
	else if (first[0] != '-' && second[0] == '-')
	{
		second.erase(0, 1);
		return Add(first, second);
	}



	// Count number of decimals for the first
	int numOfDec_f = 0;
	int numOfInts_f = 0;
	int index = 0;
	bool decPointStart = false;
	while (index < first.length())
	{
		if (decPointStart)
		{
			numOfDec_f++;
			index++;
		}
		else if (first[index] == '.')
		{
			decPointStart = true;
			first.erase(index, 1);
		}
		else
		{
			numOfInts_f++;
			index++;
		}
	}

	// Count number of decimals for the second
	int numOfDec_s = 0;
	int numOfInts_s = 0;
	index = 0;
	decPointStart = false;
	while (index < second.length())
	{
		if (decPointStart)
		{
			numOfDec_s++;
			index++;
		}
		else if (second[index] == '.')
		{
			decPointStart = true;
			second.erase(index, 1);
		}
		else
		{
			numOfInts_s++;
			index++;
		}
	}

	int finNumOfDecs = 0;
	if (numOfDec_f > numOfDec_s)
		finNumOfDecs = numOfDec_f;
	else if (numOfDec_f < numOfDec_s)
		finNumOfDecs = numOfDec_s;
	else
		finNumOfDecs = numOfDec_f;



	std::string f;
	std::string s;
	std::string result = "";
	bool sIsBigger = false;

	int len;
	if (numOfInts_f > numOfInts_s)
	{
		f = first;
		s = second;

		len = numOfInts_f - numOfInts_s;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		s = str + s;
	}
	else if (numOfInts_f < numOfInts_s)
	{
		f = second;
		s = first;

		// swap
		int tmp = numOfDec_f;
		numOfDec_f = numOfDec_s;
		numOfDec_s = tmp;

		tmp = numOfInts_f;
		numOfInts_f = numOfInts_s;
		numOfInts_s = tmp;

		sIsBigger = true;
		len = numOfInts_f - numOfInts_s;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		s = str + s;
	}
	else if (isGreaterThan(second, first))
	{
		f = second;
		s = first;

		// swap
		int tmp = numOfDec_f;
		numOfDec_f = numOfDec_s;
		numOfDec_s = tmp;

		tmp = numOfInts_f;
		numOfInts_f = numOfInts_s;
		numOfInts_s = tmp;

		sIsBigger = true;
	}
	else
	{
		f = first;
		s = second;
	}


	if (numOfDec_f > numOfDec_s)
	{
		len = numOfDec_f - numOfDec_s;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		s = s + str;
	}
	else if (numOfDec_f < numOfDec_s)
	{
		len = numOfDec_s - numOfDec_f;
		std::string str = "";

		for (int i = 0; i < len; i++)
		{
			str += '0';
		}
		f = f + str;
	}

	len = f.length();

	int carry = 0;
	int i = 0;
	while (i < len)
	{
		int v1 = f[f.length() - 1 - i] - '0';
		int v2 = s[s.length() - 1 - i] - '0';
		int vf = v1 - v2 + carry;

		if (vf < 0)
		{
			carry = -1;
			vf += 10;
		}
		else
			carry = 0;

		std::string vs = std::to_string(vf);

		if (i == finNumOfDecs)
			result += '.';
		
		result += vs[vs.length() - 1];

		i++;
	}

	std::string RESULT = "";
	if (sIsBigger)
		RESULT += "-";

	len = result.length();
	for (i = len; i > 0; i--)
	{
		RESULT += result[i - 1];
	}

	len = RESULT.length();
	i = 0;
	while (i < len)
	{
		if (RESULT[i] != '0' && RESULT[i] != '-')
			break;
		else if (RESULT[i] == '0')
		{
			RESULT.erase(i, 1);
			i = 0;
		}
		else
			i++;
	}

	if (RESULT == "")
		return "0";

	return RESULT;
}






/*-------------------------
| Multiplication Function |
-------------------------*/
std::string LNM::Multiply(std::string first, std::string second)
{
	bool isNegative = false;
	if (first[0] == '-' && second[0] != '-')
	{
		isNegative = true;
		first.erase(0, 1);
	}
	else if (first[0] != '-' && second[0] == '-')
	{
		isNegative = true;
		second.erase(0, 1);
	}
	else if (first[0] == '-' && second[0] == '-')
	{
		first.erase(0, 1);
		second.erase(0, 1);
	}

	// Count number of decimals for the first
	int numOfDec_f = 0;
	int numOfInts_f = 0;
	int index = 0;
	bool decPointStart = false;
	while (index < first.length())
	{
		if (decPointStart)
		{
			numOfDec_f++;
			index++;
		}
		else if (first[index] == '.')
		{
			decPointStart = true;
			first.erase(index, 1);
		}
		else
		{
			numOfInts_f++;
			index++;
		}
	}

	// Count number of decimals for the second
	int numOfDec_s = 0;
	int numOfInts_s = 0;
	index = 0;
	decPointStart = false;
	while (index < second.length())
	{
		if (decPointStart)
		{
			numOfDec_s++;
			index++;
		}
		else if (second[index] == '.')
		{
			decPointStart = true;
			second.erase(index, 1);
		}
		else
		{
			numOfInts_s++;
			index++;
		}
	}

	int totNumOfDecs = numOfDec_f + numOfDec_s;


	if (first.length() < second.length())
	{
		std::string tmp = first;
		first = second;
		second = tmp;
	}

	std::vector<std::string> nums;


	int carry = 0;
	for (int i = 0; i < second.length(); i++)
	{
		std::string n_num = "";
		for (int j = 0; j < first.length(); j++)
		{
			int v1 = first[first.length() - 1 - j] - '0';
			int v2 = second[second.length() - 1 - i] - '0';
			int vf = (v1 * v2) + carry;
			std::string vs = std::to_string(vf);

			if (vs.length() > 1)
			{
				carry = vs[0] - '0';
				n_num += vs[1];
			}
			else
			{
				carry = 0;
				n_num += vs;
			}
		}

		if (carry > 0)
		{
			n_num += std::to_string(carry);
			carry = 0;
		}

		std::string N_NUM = "";

		int len = n_num.length();
		for (int k = len; k > 0; k--)
		{
			N_NUM += n_num[k - 1];
		}

		// tack on zeros
		for (int k = 0; k < i; k++)
		{
			N_NUM += '0';
		}

		nums.push_back(N_NUM);
	}

	// Add all numbers in nums vector
	std::string final_num = nums.back();
	nums.pop_back();
	while (nums.size() > 0)
	{
		final_num = Add(final_num, nums.back());
		nums.pop_back();
	}

	std::string flip_result = "";
	int i = 0;
	bool decimalAdded = false;
	while (i < final_num.length())
	{
		if (i == totNumOfDecs && !decimalAdded)
		{
			flip_result += '.';
			decimalAdded = true;
		}
		else
		{
			flip_result += final_num[final_num.length() - i - 1];
			i++;
		}
	}

	std::string result = "";
	for (i = flip_result.length(); i > 0; i--)
		result += flip_result[i - 1];

	if (isNegative)
		return '-' + result;

	return result;
}






/*-------------------
| Division Function |
-------------------*/
std::string LNM::Divide(std::string first, std::string second)
{
	bool isNegative = false;
	if (first[0] == '-' && second[0] != '-')
	{
		isNegative = true;
		first.erase(0, 1);
	}
	else if (first[0] != '-' && second[0] == '-')
	{
		isNegative = true;
		second.erase(0, 1);
	}
	else if (first[0] == '-' && second[0] == '-')
	{
		first.erase(0, 1);
		second.erase(0, 1);
	}

	std::string result = "";

	if (isNegative)
		result = '-';
	
	bool isDecimal = false;
	std::string precCount = "0";

	if (second.length() > first.length())
	{
		result += "0.";
		isDecimal = true;
		while (first.length() < second.length())
		{
			first += '0';
		}
	}

	std::string in_val = "";
	int i = 0;

	while (in_val.length() < second.length() - 1)
	{
		in_val += first[i];
		i++;
	}

	while (i < first.length())
	{
		in_val += first[i];

		int count = 0;
		std::string tmp = in_val;
		while (isGreaterThan(tmp, "0"))
		{
			tmp = Subtract(tmp, second);
			count++;
		}
		if (isGreaterThan("0", tmp))
			count--;

		std::string str_count = std::to_string(count);
		result += str_count;

		in_val = Subtract(in_val, Multiply(str_count, second));

		i++;

		if (in_val != "0" && !(i < first.length()) && isGreaterThan(Subtract(precision, "1"), precCount))
		{
			first += '0';
			if (!isDecimal)
			{
				result += ".";
				isDecimal = true;
			}
			else
				precCount = Add(precCount, "1");
		}
	}

	// Removes all zeros in front of number
	int len = result.length();
	i = 0;
	while (i < len)
	{
		if (result[i] != '0' && result[i] != '-')
			break;
		else if (result[i] == '0' && result[i + 1] != '.')
		{
			result.erase(i, 1);
			i = 0;
		}
		else if (result[i + 1] != '.')
			break;
		else
			i++;
	}

	return result;
}




bool LNM::isGreaterThan(std::string first, std::string second)
{
	bool firstIsNegative = false;
	bool secondIsNegative = false;
	std::string intOfFirst = "";
	std::string intOfSecond = "";
	std::string decOfFirst = "";
	std::string decOfSecond = "";

	if (first[0] == '-')
	{
		firstIsNegative = true;
		first.erase(0, 1);
	}

	if (second[0] == '-')
	{
		secondIsNegative = true;
		second.erase(0, 1);
	}

	// Check for decimals


	// Remove front zeros from first number
	int len = first.length();
	int i = 0;
	while (i < len)
	{
		if (first[i] != '0' && first[i] != '-')
			break;
		else if (first[i] == '0' && first[i + 1] != '.')
		{
			first.erase(i, 1);
			i = 0;
		}
		else if (first[i + 1] != '.')
			break;
		else
			i++;
	}

	// Remove front zeros from second number
	len = second.length();
	i = 0;
	while (i < len)
	{
		if (second[i] != '0' && second[i] != '-')
			break;
		else if (second[i] == '0' && second[i + 1] != '.')
		{
			second.erase(i, 1);
			i = 0;
		}
		else if (second[i + 1] != '.')
			break;
		else
			i++;
	}

	// Split the integer and decimal of first
	len = first.length();
	i = 0;
	while (i < len)
	{
		if (first[i] == '.')
		{
			intOfFirst = first;
			decOfFirst = first;
			intOfFirst.erase(i, first.length());
			decOfFirst.erase(0, i);
		}
		i++;
	}

	if (decOfFirst == "")
		intOfFirst = first;

	// Split the integer and decimal of second
	len = second.length();
	i = 0;
	while (i < len)
	{
		if (second[i] == '.')
		{
			intOfSecond = second;
			decOfSecond = second;
			intOfSecond.erase(i, second.length());
			decOfSecond.erase(0, i);
		}
		i++;
	}

	if (decOfSecond == "")
		intOfSecond = second;


	// Check the integers
	if (intOfFirst.length() > intOfSecond.length() && !firstIsNegative)
		return true;

	if (intOfFirst.length() > intOfSecond.length() && firstIsNegative)
		return false;

	if (intOfFirst.length() < intOfSecond.length() && !secondIsNegative)
		return false;

	if (intOfFirst.length() < intOfSecond.length() && secondIsNegative)
		return true;

	len = intOfFirst.length();
	for (i = 0; i < len; i++)
	{
		int v1 = intOfFirst[i] - '0';
		int v2 = intOfSecond[i] - '0';

		if (v1 > v2 && !firstIsNegative)
			return true;
		if (v1 > v2 && firstIsNegative)
			return false;
		if (v1 < v2 && !secondIsNegative)
			return false;
		if (v1 < v2 && secondIsNegative)
			return true;
	}


	// Check the decimals
	if (decOfFirst == "" && decOfSecond == "")
		return false;

	// Remove zeros from back of decimal for first number
	while (decOfFirst[decOfFirst.length() - 1] == '0')
	{
		decOfFirst.erase(decOfFirst.length() - 1);
	}

	while (decOfSecond[decOfSecond.length() - 1] == '0')
	{
		decOfSecond.erase(decOfSecond.length() - 1);
	}

	if (decOfFirst.length() > decOfSecond.length() && !firstIsNegative)
		return true;

	if (decOfFirst.length() > decOfSecond.length() && firstIsNegative)
		return false;

	if (decOfFirst.length() < decOfSecond.length() && !secondIsNegative)
		return false;

	if (decOfFirst.length() < decOfSecond.length() && secondIsNegative)
		return true;

	len = decOfFirst.length();
	for (i = 0; i < len; i++)
	{
		int v1 = decOfFirst[i] - '0';
		int v2 = decOfSecond[i] - '0';

		if (v1 > v2 && !firstIsNegative)
			return true;
		if (v1 > v2 && firstIsNegative)
			return false;
		if (v1 < v2 && !secondIsNegative)
			return false;
		if (v1 < v2 && secondIsNegative)
			return true;
	}

	return false;

}


