#include "Client.h"

// Constructors

Client::Client() { }

Client::Client(string n) : ID(proxID), name(n)
{
	updateProxID(++proxID);
}

Client::Client(int i, string n) : ID(i), name(n) { }

Client::Client(int i, string n, vector<int> p) : ID(i), name(n), projects(p) { }

// Member-functions

int Client::proxID = 0;

void Client::updateProxID(int pID)
{
	proxID = pID;
}

int Client::getProxID()
{
	return proxID;
}

int Client::getID() const
{
	return ID;
}

string Client::getName() const
{
	return name;
}

vector<int> Client::getProjects() const
{
	return projects;
}

void Client::addProject(int projectID)
{
	projects.push_back(projectID);
}

void Client::removeProject(int projectID)
{
	size_t i = 0;
	while (i < projects.size() && projectID != projects[i])
		i++;
	if (i != projects.size())
		projects.erase(projects.begin() + i);
}