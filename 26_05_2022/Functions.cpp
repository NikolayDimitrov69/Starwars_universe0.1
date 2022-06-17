#include "Functions.h"

const bool& isNumber(const std::string& str)
{
	unsigned t = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '.')
		{
			t++;
		}
		if (!isdigit(str[i]) && (str[0] == '.' || str[str.size() - 1] == '.' || t > 1))
		{
			return false;
		}
	}
	return true;
}

unsigned biggestNumInArray(unsigned * arr, unsigned size)
{
	unsigned currentbiggest = 0;
	unsigned position = 0;
	for (unsigned i = 0; i < size; i++)
	{
		if (arr[i] > currentbiggest)
		{
			currentbiggest = arr[i];
			position = i;
		}
	}
	return position;
}

std::string alpha_sort(std::string str1, std::string str2) {
	unsigned smallerword = 0;
	str1.size() <= str2.size() ? smallerword = str1.size() : smallerword = str2.size();
	for (unsigned i = 0; i < smallerword; i++)
	{
		if (str1[i] == str2[i])
		{
			continue;
		}
		if (str1[i] < str2[i])
		{
			return str1;
		}
		if (str2[i] < str1[i])
		{
			return str2;
		}
	}
	return str1.size() < str2.size() ? str1 : str2;
}
