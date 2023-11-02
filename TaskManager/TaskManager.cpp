#include"Task.h"
#include "TaskManager.h"
#include <Windows.h>
#include <fstream>

TaskManager::~TaskManager()
{
	delete instance;
}

TaskManager* TaskManager::getTaskManager()
{
	if (instance == nullptr)
	{
		instance = new TaskManager();
	}
	return instance;
}

bool TaskManager::save(std::string file_name)
{
	return false;
}

bool TaskManager::load(std::string file_name)
{
	std::string name;
	std::vector<std::string> names;
	std::ifstream fin(file_name);

	if (!fin.is_open())
	{
		return false;
	}

	while (std::getline(fin, name))
	{
		names.push_back(name);
	}

	fin.close();
	for (auto name : names)
	{
		std::string t_name;
		std::string task;
		int day, month, year;
		std::string tag;
		int priority;

		std::ifstream task_fin(name + ".txt");
		if (!task_fin.is_open())
		{
			return false;
		}

		std::getline(task_fin, t_name);
		std::getline(task_fin, task);

		task_fin >> day >> month >> year;
		task_fin.ignore();

		std::getline(task_fin, tag);
		task_fin >> priority;

		int date[3] = { day,month,year };
		Task* new_task = new Task(t_name, task, date, tag, (Priority)priority);
		tasks.push_back(new_task);

		task_fin.close();

	}

	return true;
}

std::vector<Task*> TaskManager::get_tasks()
{
	return tasks;
}

void TaskManager::push_back(Task* t)
{
	tasks.push_back(t);
}

void TaskManager::del(size_t index)
{
	tasks.erase(tasks.begin() + index);
}


TaskManager* TaskManager::instance = nullptr;