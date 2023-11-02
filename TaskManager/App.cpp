#define _CRT_SECURE_NO_WARNINGS
#include "App.h"
#include "Task.h"
#include "TaskManager.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void Application::start()
{
	TaskManager* task_manager = TaskManager::getTaskManager();
	bool status = task_manager->load("names.txt");
	if (!status)
	{
		MessageBox(0, (LPCWSTR)L"Error with the files. Try again", (LPCWSTR)L"Warning", MB_ICONWARNING);
		exit(0);
	}

	while (true)
	{
		system("cls");
		int first_menu = Menu::select_vertical({ "Create Task", "Delete Task", "All Tasks", "Find Task" }, HorizontalAlignment::Center);
		switch (first_menu)
		{
		case -1:
		{
			exit(0);
		}
		case 0:
		{
			std::string name;
			std::string task;
			int d = 0, m = 0, y = 0;
			std::string tag;
			int priority = 0;

			while (true)
			{
				render::gotoxy(16, 9);
				std::cout << "                                                ";
				render::gotoxy(16, 9);
				std::cout << "Name of Task: ";
				std::getline(std::cin, name);

				if (name.length() < 1)
				{
					MessageBox(0, (LPCWSTR)L"Error. The name is empty. Create a name that is, at least, 1 character long", (LPCWSTR)L"Warning", MB_ICONWARNING);
					continue;
				}

				std::ifstream fin(name + ".txt");
				if (fin.is_open())
				{
					MessageBox(0, (LPCWSTR)L"Error. This name already exists. Create a unique name", (LPCWSTR)L"Warning", MB_ICONWARNING);
					fin.close();
					continue;
				}
				else
				{
					break;
				}
			}

			while (true)
			{
				render::gotoxy(16, 10);
				std::cout << "                                                ";
				render::gotoxy(16, 10);
				std::cout << "Describe task: ";
				std::getline(std::cin, task);

				if (task.length() < 1)
				{
					MessageBox(0, (LPCWSTR)L"Error. The task is empty. Describe the task that is, at least, 1 character long", (LPCWSTR)L"Warning", MB_ICONWARNING);
					continue;
				}
				else
				{
					break;
				}
			}
			

			std::time_t currentTime = std::time(nullptr);
			std::tm* localTime = std::localtime(&currentTime);

			int currentYear = localTime->tm_year + 1900;

			while (d <= 0 or d >= 32 or m <= 0 or m >= 13 or y < currentYear)
			{
				render::gotoxy(16, 11);
				std::cout << "Enter date with spaces (example - 01 11 2023): ";
				std::cin >> d;
				std::cin >> m;
				std::cin >> y;

				if (d <= 0 or d >= 32 or m <= 0 or m >= 13 or y < currentYear)
				{
					MessageBox(0, (LPCWSTR)L"Error. The date is expired. Try again", (LPCWSTR)L"Warning", MB_ICONWARNING);
				}

			}
			std::cin.ignore();
			render::gotoxy(16, 12);
			std::cout << "Enter tag: ";
			std::getline(std::cin, tag);

			render::gotoxy(16, 13);
			std::cout << "Enter priority";

			while (priority < 1 or priority > 3)
			{
				render::gotoxy(16, 14);
				std::cout << "(1 - Not Important, 2 - Important, 3 - Very Important): ";
				std::cin >> priority;

				if (priority < 1 or priority > 3)
				{
					MessageBox(0, (LPCWSTR)L"Error. Wrong number. Try again", (LPCWSTR)L"Warning", MB_ICONWARNING);
				}
			}			

			int date[3] = { d,m,y };
			Task* new_task = new Task(name, task, date, tag, (Priority)priority);

			task_manager->push_back(new_task);

			std::ofstream fout("names.txt", std::ios::app);
			if (fout.is_open())
			{
				fout << name << std::endl;
			}
			else
			{
				MessageBox(0, (LPCWSTR)L"Error with the files. Try again", (LPCWSTR)L"Warning", MB_ICONWARNING);
				break;
			}
			fout.close();

			std::ofstream fname(name + ".txt");
			if (fname.is_open())
			{
				fname << name << std::endl;
				fname << task << std::endl;
				fname << d << " " << m << " " << y << std::endl;
				fname << tag << std::endl;
				fname << priority << std::endl;
			}
			else
			{
				MessageBox(0, (LPCWSTR)L"Error with the files. Try again", (LPCWSTR)L"Warning", MB_ICONWARNING);
				break;
			}
			fname.close();
			MessageBox(0, (LPCWSTR)L"Your notification was successfully created", (LPCWSTR)L"Info", MB_ICONINFORMATION);
			break;
		}
		case 1:
		{
			std::vector<std::string> names;
			for (auto t : task_manager->get_tasks())
			{
				names.push_back(t->getName());
			}
			int delete_index = Menu::select_vertical(names, HorizontalAlignment::Center);
			if (delete_index == -1)
			{
				break;
			}
			fs::remove(names[delete_index] + ".txt");
			names.erase(names.begin() + delete_index);
			task_manager->del(delete_index);
			std::ofstream fout("names.txt");
			if (fout.is_open())
			{
				for (auto name : names)
				{
					fout << name << std::endl;
				}
			}
			else
			{
				MessageBox(0, (LPCWSTR)L"Error with the files. Try again", (LPCWSTR)L"Warning", MB_ICONWARNING);
				break;
			}
			fout.close();
			MessageBox(0, (LPCWSTR)L"Your notification was successfully deleted", (LPCWSTR)L"Info", MB_ICONINFORMATION);
			break;
		}
		case 2:
		{
			for (auto t : task_manager->get_tasks())
			{
				std::cout << t->getName() << std::endl << t->getTask() << std::endl << t->getDate().getDate() << std::endl << "Tags: " << t->getTag() << std::endl << t->str_priority() << std::endl << std::endl;
			}
			system("pause");
			break;
		}
		case 3:
		{
			int find = Menu::select_vertical({ "Find by Name", "Find by Task", "Find by Date", "Find by Tag", "Find by Priority"}, HorizontalAlignment::Center);
			switch (find)
			{
				case -1:
				{
					break;
				}
				case 0:
				{
					std::string name;
					render::gotoxy(16, 9);
					std::cout << "Name of Task: ";
					std::getline(std::cin, name);
					bool is_found = false;
					for (auto t : task_manager->get_tasks())
					{
						if (t->getName() == name)
						{
							if (is_found == false)
							{
								is_found = true;
							}
							std::cout << t->getName() << std::endl << t->getTask() << std::endl << t->getDate().getDate() << std::endl << "Tags: " << t->getTag() << std::endl << t->str_priority() << std::endl << std::endl;
						}
					}

					if (!is_found)
					{
						std::wstring wideStr = L"No notifications with name \"";
						std::wstring wide_buff;
						wide_buff.assign(name.begin(), name.end());
						wideStr += wide_buff;
						wideStr += L"\" were found";

						const wchar_t* wideCStr = wideStr.c_str();

						MessageBox(0, wideCStr, (LPCWSTR)L"Info", MB_ICONINFORMATION);

						break;
					}
					system("pause");
					break;
				}
				case 1:
				{
					std::string task;
					render::gotoxy(16, 9);
					std::cout << "Description of Task: ";
					std::getline(std::cin, task);
					bool is_found = false;
					for (auto t : task_manager->get_tasks())
					{
						if (t->getTask() == task)
						{
							if (is_found == false)
							{
								is_found = true;
							}
							std::cout << t->getName() << std::endl << t->getTask() << std::endl << t->getDate().getDate() << std::endl << "Tags: " << t->getTag() << std::endl << t->str_priority() << std::endl << std::endl;
						}
					}

					if (!is_found)
					{
						std::wstring wideStr = L"No notifications with description \"";
						std::wstring wide_buff;
						wide_buff.assign(task.begin(), task.end());
						wideStr += wide_buff;
						wideStr += L"\" were found";

						const wchar_t* wideCStr = wideStr.c_str();

						MessageBox(0, wideCStr, (LPCWSTR)L"Info", MB_ICONINFORMATION);

						break;
					}
					system("pause");
					break;
				}
				case 2:
				{
					int d, m, y;
					render::gotoxy(16, 9);
					std::cout << "Enter date with spaces (example - 01 11 2023): ";
					std::cin >> d;
					std::cin >> m;
					std::cin >> y;

					bool is_found = false;
					Date date(d, m, y);
					for (auto t : task_manager->get_tasks())
					{
						if (t->getDate().equal(date) == true)
						{
							if (is_found == false)
							{
								is_found = true;
							}
							std::cout << t->getName() << std::endl << t->getTask() << std::endl << t->getDate().getDate() << std::endl << "Tags: " << t->getTag() << std::endl << t->str_priority() << std::endl << std::endl;
						}
					}

					if (!is_found)
					{
						std::wstring wideStr = L"No notifications with date \"";
						std::string str_date = date.getDate();
						std::wstring wide_buff;
						wide_buff.assign(str_date.begin(), str_date.end());
						wideStr += wide_buff;
						wideStr += L"\" were found";

						const wchar_t* wideCStr = wideStr.c_str();

						MessageBox(0, wideCStr, (LPCWSTR)L"Info", MB_ICONINFORMATION);

						break;
					}
					system("pause");
					break;
				}
				case 3:
				{
					std::string tag;
					render::gotoxy(16, 9);
					std::cout << "Tag of Task: ";
					std::getline(std::cin, tag);
					bool is_found = false;
					for (auto t : task_manager->get_tasks())
					{
						if (t->getTag() == tag)
						{
							if (is_found == false)
							{
								is_found = true;
							}
							std::cout << t->getName() << std::endl << t->getTask() << std::endl << t->getDate().getDate() << std::endl << "Tags: " << t->getTag() << std::endl << t->str_priority() << std::endl << std::endl;
						}
					}

					if (!is_found)
					{
						std::wstring wideStr = L"No notifications with tag \"";
						std::wstring wide_buff;
						wide_buff.assign(tag.begin(), tag.end());
						wideStr += wide_buff;
						wideStr += L"\" were found";

						const wchar_t* wideCStr = wideStr.c_str();

						MessageBox(0, wideCStr, (LPCWSTR)L"Info", MB_ICONINFORMATION);

						break;
					}
					system("pause");
					break;
				}
				case 4:
				{
					int priority = 0;
					
					render::gotoxy(16, 9);
					std::cout << "Enter priority";

					while (priority < 1 or priority > 3)
					{
						render::gotoxy(16, 10);
						std::cout << "(1 - Not Important, 2 - Important, 3 - Very Important): ";
						std::cin >> priority;

						if (priority < 1 or priority > 3)
						{
							MessageBox(0, (LPCWSTR)L"Error. Wrong number. Try again", (LPCWSTR)L"Warning", MB_ICONWARNING);
						}
					}

					std::string str_priority;
					if (priority == 1)
					{
						str_priority = "Not Important";
					}
					else if (priority == 2)
					{
						str_priority = "Important";
					}
					else if (priority == 3)
					{
						str_priority = "Very Important";
					}

					bool is_found = false;
					for (auto t : task_manager->get_tasks())
					{
						if (t->getPriority() == (Priority)priority)
						{
							if (is_found == false)
							{
								is_found = true;
							}
							std::cout << t->getName() << std::endl << t->getTask() << std::endl << t->getDate().getDate() << std::endl << "Tags: " << t->getTag() << std::endl << t->str_priority() << std::endl << std::endl;
						}
					}

					if (!is_found)
					{
						std::wstring wideStr = L"No notifications with priority \"";
						std::wstring wide_buff;
						wide_buff.assign(str_priority.begin(), str_priority.end());
						wideStr += wide_buff;
						wideStr += L"\" were found";

						const wchar_t* wideCStr = wideStr.c_str();

						MessageBox(0, wideCStr, (LPCWSTR)L"Info", MB_ICONINFORMATION);

						break;
					}
					system("pause");
					break;
				}
			}
			break;
		}
		}
	}
}
