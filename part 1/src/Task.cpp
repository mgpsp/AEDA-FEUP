#include "Task.h"

// Constructors

Task::Task() { }

Task::Task(string d, float eT, vector<int> a, vector<int> dP) : ID(proxID), description(d), estimatedTime(eT), associates(a), dependencies(dP)
{ 
	updateProxID(++proxID);
	done = false;
}

Task::Task(int i, string d, float eT, vector<int> a, vector<int> dP) : ID(i), description(d), estimatedTime(eT), associates(a), dependencies(dP) { }

Task::Task(int i, string d, float eT, vector<int> a, vector<int> dP, bool dn) : ID(i), description(d), estimatedTime(eT), associates(a), dependencies(dP), done(dn) { }

// Memmber-functions

int Task::proxID = 0;

void Task::updateProxID(int pID)
{
	proxID = pID;
}
int Task::getProxID()
{
	return proxID;
}

int Task::getID() const
{
	return ID;
}

string Task::getDescription() const
{

	return description;
}

float Task::getEstimatedTime() const
{

	return estimatedTime;
}

vector<int> Task::getAssociates() const
{
	return associates;
}

vector<int> Task::getDependencies() const
{
	return dependencies;
}

bool Task::getStatus() const
{
	return done;
}

void Task::setDone(bool status)
{
	done = status;
}

void Task::sortTasksByEstimatedTime(vector<Task>& tasks)
{
	if (tasks.size() <= 1)
		return;

	Task tmp;
	for (size_t i = 0; i < (tasks.size() - 1); i++)
	{
		for (size_t j = (i + 1); j < tasks.size(); j++)
		{
			if (tasks[i].estimatedTime > tasks[j].estimatedTime)
			{
				tmp = tasks[i];
				tasks[i] = tasks[j];
				tasks[j] = tmp;
			}
		}
	}
}

ostream& operator<<(ostream& out, const Task& task)
{
	out << task.description << " (Estimated time: " << task.estimatedTime << ")";
	if (task.done)
		out << " [Done]";
	return out;
}