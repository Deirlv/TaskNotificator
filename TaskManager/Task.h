#pragma once
#include <iostream>
#include "Date.h"

enum class Priority
{
	not_important = 1, important, very_important
};

class Task
{
	std::string name;
	std::string task;
	Date date;
	std::string tag;
	Priority priority;

public:

	Task(std::string name, std::string task, int date[3], std::string tag, Priority priority);
	
	std::string getName();

	std::string getTask();

	Date getDate();

	std::string getTag();

	Priority getPriority();

	std::string str_priority();

	bool save();

};
