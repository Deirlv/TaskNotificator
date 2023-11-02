#pragma once
#include <iostream>
#include <string>

class Date
{
	size_t day;
	size_t month;
	size_t year;

public:

	Date(size_t day = 0, size_t month = 0, size_t year = 0);

	void setDay(size_t day);

	void setMonth(size_t month);

	void setYear(size_t year);

	size_t getDay();

	size_t getMonth();

	size_t getYear();

	std::string getDate();

	bool equal(Date d);

};
