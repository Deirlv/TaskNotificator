#include "Task.h"

Task::Task(std::string name, std::string task, int date[3], std::string tag, Priority priority) : name(name), task(task), date(date[0], date[1], date[2]), tag(tag), priority(priority) {}

std::string Task::getName()
{
	return name;
}

std::string Task::getTask()
{
	return task;
}

Date Task::getDate()
{
	return date;
}

std::string Task::getTag()
{
	return tag;
}

Priority Task::getPriority()
{
	return priority;
}

std::string Task::str_priority()
{
	if (priority == Priority::not_important)
	{
		return "Not Important";
	}
	else if (priority == Priority::important)
	{
		return "Important";
	}
	else if (priority == Priority::very_important)
	{
		return "Very Important";
	}
}

bool Task::save()
{
	return false;
}
