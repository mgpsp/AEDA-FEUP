#include "Project.h"

// Overloaded operator < for struct Date

bool operator<(Date& d1, Date& d2)
{
	if (d1.year < d2.year)
		return true;
	else if (d1.year > d2.year)
		return false;
	else if (d1.month < d2.month)
		return true;
	else if (d1.month > d2.month)
		return false;
	else if (d1.day < d2.day)
		return true;
	else return false;
}

// Constructors

Project::Project() { }

Project::Project(string n, Date dD, string t, vector<int> ts, unsigned int c) : ID(proxID), name(n), dueDate(dD), type(t), tasks(ts), clientID(c)
{
	updateProxID(++proxID);
}

Project::Project(int i, string n, Date dD, string t, vector<int> ts, unsigned int c) : ID(i), name(n), dueDate(dD), type(t), tasks(ts), clientID(c) { }

// Member-functions

int Project::proxID = 0;

void Project::updateProxID(int pID)
{
	proxID = pID;
}

int Project::getProxID()
{
	return proxID;
}

unsigned int Project::getID() const
{
	return ID;
}

string Project::getName() const
{
	return name;
}

Date Project::getDueDate() const
{
	return dueDate;
}

vector<int> Project::getTasks() const
{
	return tasks;
}

string Project::getType() const
{
	return type;
}

unsigned int Project::getClientID() const
{
	return clientID;
}

void Project::sortProjectsByDueDate(vector<Project>& projects)
{
	Project tmp;
	for (size_t i = 0; i < (projects.size() - 1); i++)
	{
		for (size_t j = (i + 1); j < projects.size(); j++)
		{
			if (projects[j].dueDate < projects[i].dueDate)
			{
				tmp = projects[i];
				projects[i] = projects[j];
				projects[j] = tmp;
			}
		}
	}
}

ostream& operator<<(ostream& out, const Project& project)
{
	out << project.name << " (" << project.dueDate.day << "/" << project.dueDate.month << "/" << project.dueDate.year << ")";
	return out;
}

void Project::removeTask(int taskID)
{
	size_t i = 0;

	while ((i < tasks.size()) && (taskID != tasks[i]))
		i++;

	if (i != tasks.size()) tasks.erase(tasks.begin() + i);
}

void Project::addTask(int taskID)
{
	tasks.push_back(taskID);
}