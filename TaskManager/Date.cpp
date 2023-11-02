#include "Date.h"

Date::Date(size_t day, size_t month, size_t year) : day(day), month(month), year(year) {}

void Date::setDay(size_t day)
{
	this->day = day;
}

void Date::setMonth(size_t month)
{
	this->month = month;
}

void Date::setYear(size_t year)
{
	this->year = year;
}

size_t Date::getDay()
{
	return this->day;
}

size_t Date::getMonth()
{
	return this->month;
}

size_t Date::getYear()
{
	return this->year;
}

std::string Date::getDate()
{
	return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}

bool Date::equal(Date d)
{
	if (day == d.day and month == d.month and year == d.year)
	{
		return true;
	}
	else
	{
		return false;
	}
}
