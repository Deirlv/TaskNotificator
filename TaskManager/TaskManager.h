#pragma once
#include <iostream>
#include <vector>
#include "Task.h"

class TaskManager
{
	std::vector<Task*> tasks;
	static TaskManager* instance;
	TaskManager() {}

public:

	~TaskManager();

	static TaskManager* getTaskManager();

	bool save(std::string file_name);

	bool load(std::string file_name);

	std::vector<Task*> get_tasks();

	void push_back(Task* t);

	void del(size_t index);

};

