#include "Associate.h"

// Constructors

Associate::Associate() { }

Associate::Associate(int i, string n, string p, vector<int> v) : ID(i), name(n), password(p), projects(v) { }

Associate::Associate(string n, string p) : ID(proxID), name(n), password(p)
{
	updateProxID(++proxID);
}

Programmer::Programmer(int i, string n, string p, vector<int> v) : Associate(i, n, p, v) {}

Designer::Designer(int i, string n, string p, vector<int> v) : Associate(i, n, p, v) {}

Manager::Manager(int i, string n, string p, vector<int> v) : Associate(i, n, p, v) {}

Tester::Tester(int i, string n, string p, vector<int> v) : Associate(i, n, p, v) {}

Programmer::Programmer(string n, string p) : Associate(n, p) {}

Designer::Designer(string n, string p) : Associate(n, p) {}

Manager::Manager(string n, string p) : Associate(n, p) {}

Tester::Tester(string n, string p) : Associate(n, p) {}

// Member-functions

int Associate::proxID = 0;

void Associate::updateProxID(int pID)
{
	proxID = pID;
}

int Associate::getProxID()
{
	return proxID;
}

unsigned int Associate::getID() const
{
	return ID;
}

string Associate::getName() const
{
	return name;
}

string Associate::getPassword() const
{
	return password;
}

vector<int> Associate::getProjects() const
{
	return projects;
}

void Associate::addProject(int projectID)
{
	size_t i = 0;
	while ((i < projects.size() && (projects[i] != projectID)))
		i++;

	if (i == projects.size())
		projects.push_back(projectID);
}

void Associate::removeProject(int projectID)
{
	size_t i = 0;

	while (i < projects.size() && projects[i] != projectID)
		i++;

	if (i != projects.size())
		projects.erase(projects.begin() + i);
}