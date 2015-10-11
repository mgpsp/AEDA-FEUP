#include "User.h"

// Constructor

User::User() { }

// Member-functions

void User::loadAssociates(string filename)
{
	ifstream fin;
	string name, password, type;
	int projectID, id, proxID;
	vector<int> projects;

	// open file
	fin.open(filename.c_str());
	if (fin.fail())
	{
		Associate::updateProxID(0);
		return;
	}
		

	// reads prox ID
	fin >> proxID;
	fin.ignore(100, '\n');
	Associate::updateProxID(proxID);

	// read file and load associates to vector
	while (!fin.eof())
	{
		fin >> id;
		fin.ignore(100, '\n');
		getline(fin, name);
		getline(fin, password);
		getline(fin, type);
		do
		{
			fin >> projectID;
			projects.push_back(projectID);
			if (projectID != -1) fin.ignore(100, ' ');
		} while (projectID != -1);
		fin.ignore(100, '\n');
		projects.pop_back();   // remove -1

		if (type == "Programmer")
			associates.push_back(new Programmer(id, name, password, projects));
		else if (type == "Designer")
			associates.push_back(new Designer(id, name, password, projects));
		else if (type == "Manager")
			associates.push_back(new Manager(id, name, password, projects));
		else
			associates.push_back(new Tester(id, name, password, projects));

		projects.clear();
	}

	fin.close();
}

void User::loadClients(string filename)
{
	ifstream fin;
	string name;
	int projectID, id, proxID;
	vector<int> projects;

	// open file
	fin.open(filename.c_str());
	if (fin.fail())
	{
		Client::updateProxID(0);
		return;
	}

	// reads prox ID
	fin >> proxID;
	fin.ignore(100, '\n');
	Client::updateProxID(proxID);

	// read file and load clients to vector
	while (!fin.eof())
	{
		fin >> id;
		fin.ignore(100, '\n');
		getline(fin, name);
		do
		{
			fin >> projectID;
			projects.push_back(projectID);
			if (projectID != -1) fin.ignore(100, ' ');
		} while (projectID != -1);
		fin.ignore(100, '\n');
		projects.pop_back();   // remove -1

		Client client(id, name, projects);
		clients.push_back(client);
		projects.clear();
	}

	fin.close();
}

void User::loadProjects(string filename)
{
	ifstream fin;
	string name, type;
	int clientID, taskID, day, month, year, id, proxID;
	vector<int> tasksID;
	Date dueDate;

	// open file
	fin.open(filename.c_str());
	if (fin.fail())
	{
		Project::updateProxID(0);
		return;
	}

	// reads prox ID
	fin >> proxID;
	fin.ignore(100, '\n');
	Project::updateProxID(proxID);

	// reads file and load projects to vector
	while (!fin.eof())
	{
		fin >> id;
		fin.ignore(100, '\n');
		getline(fin, name);
		fin >> day;
		fin.ignore(100, '/');
		fin >> month;
		fin.ignore(100, '/');
		fin >> year;
		fin.ignore(100, '\n');
		dueDate.day = day;
		dueDate.month = month;
		dueDate.year = year;
		do
		{
			fin >> taskID;
			tasksID.push_back(taskID);
			if (taskID != -1) fin.ignore(100, ' ');
		} while (taskID != -1);
		fin.ignore(100, '\n');
		tasksID.pop_back();   // remove -1
		getline(fin, type);
		fin >> clientID;
		fin.ignore(100, '\n');

		Project project(id, name, dueDate, type, tasksID, clientID);
		projects.push_back(project);
		tasksID.clear();
	}

	fin.close();
}

void User::loadTasks(string filename)
{
	ifstream fin;
	string description;
	int associateID, taskID, id, proxID;
	float estimatedTime;
	bool done;
	vector<int> associates, dependencies;

	// open file
	fin.open(filename.c_str());
	if (fin.fail())
	{
		Task::updateProxID(0);
		return;
	}

	// reads prox ID
	fin >> proxID;
	fin.ignore(100, '\n');
	Task::updateProxID(proxID);

	// read file and load tasks to vector
	while (!fin.eof())
	{
		fin >> id;
		fin.ignore(100, '\n');
		getline(fin, description);
		fin >> estimatedTime;
		fin.ignore(100, '\n');
		do
		{
			fin >> associateID;
			associates.push_back(associateID);
			if (associateID != -1) fin.ignore(100, ' ');
		} while (associateID != -1);
		fin.ignore(100, '\n');
		associates.pop_back();   // remove -1
		do
		{
			fin >> taskID;
			dependencies.push_back(taskID);
			if (taskID != -1) fin.ignore(100, ' ');
		} while (taskID != -1);
		fin.ignore(100, '\n');
		dependencies.pop_back();   // remove -1
		fin >> done;
		fin.ignore(100, '\n');

		Task task(id, description, estimatedTime, associates, dependencies, done);
		tasks.push_back(task);
		associates.clear();
		dependencies.clear();
	}

	fin.close();
}

void User::saveAssociates(string filename)
{
	ofstream fout;

	// open file
	fout.open(filename.c_str());
	if (fout.fail())
		throw (FileNotOpened(filename));

	fout << Associate::getProxID() << endl;

	// reads vector and loads to file
	for (int i = 0; i < associates.size(); i++){

		fout << associates[i]->getID() << endl;
		fout << associates[i]->getName() << endl;
		fout << associates[i]->getPassword() << endl;
		fout << associates[i]->getType() << endl;
		for (int j = 0; j < associates[i]->getProjects().size(); j++)
		{
			fout << associates[i]->getProjects()[j] << " ";
		}
		if (i == associates.size() - 1){
			fout << -1;
		}
		else fout << -1 << endl;
	}

	fout.close();
}

void User::saveClients(string filename)
{
	ofstream fout;

	// open file
	fout.open(filename.c_str());
	if (fout.fail())
		throw (FileNotOpened(filename));

	fout << Client::getProxID() << endl;

	// reads vector and loads to file
	for (int i = 0; i< clients.size(); i++){

		fout << clients[i].getID() << endl;
		fout << clients[i].getName() << endl;
		for (int j = 0; j < clients[i].getProjects().size(); j++)
		{
			fout << clients[i].getProjects()[j] << " ";
		}
		if (i == clients.size() - 1){
			fout << -1;
		}
		else fout << -1 << endl;
	}

	fout.close();
}

void User::saveProjects(string filename)
{
	ofstream fout;

	// open file
	fout.open(filename.c_str());
	if (fout.fail())
		throw (FileNotOpened(filename));

	fout << Project::getProxID() << endl;

	// reads vector and loads to file
	for (int i = 0; i< projects.size(); i++){

		fout << projects[i].getID() << endl;
		fout << projects[i].getName() << endl;
		fout << projects[i].getDueDate().day << "/" << projects[i].getDueDate().month << "/" << projects[i].getDueDate().year << endl;
		for (int j = 0; j < projects[i].getTasks().size(); j++)
		{
			fout << projects[i].getTasks()[j] << " ";
		}
		fout << -1 << endl;
		fout << projects[i].getType() << endl;
		if (i == projects.size() - 1){
			fout << projects[i].getClientID();
		}
		else fout << projects[i].getClientID() << endl;
	}

	fout.close();
}

void User::saveTasks(string filename)
{
	ofstream fout;

	// open file
	fout.open(filename.c_str());
	if (fout.fail())
		throw (FileNotOpened(filename));

	fout << Task::getProxID() << endl;

	// reads vector and loads to file
	for (int i = 0; i< tasks.size(); i++){

		fout << tasks[i].getID() << endl;
		fout << tasks[i].getDescription() << endl;
		fout << tasks[i].getEstimatedTime() << endl;
		for (int j = 0; j < tasks[i].getAssociates().size(); j++)
		{
			fout << tasks[i].getAssociates()[j] << " ";
		}
		fout << -1 << endl;
		for (int j = 0; j < tasks[i].getDependencies().size(); j++)
		{
			fout << tasks[i].getDependencies()[j] << " ";
		}
		fout << -1 << endl;
		if (i == tasks.size() - 1)
		{
			if (tasks[i].getStatus())
				fout << 1;
			else
				fout << 0;
		}
		else
		{
			if (tasks[i].getStatus())
				fout << 1 << endl;
			else
				fout << 0 << endl;
		}

	}

	fout.close();
}


vector<Project> User::getProjects()
{
	return projects;
}

vector<Client> User::getClients()
{
	return clients;
}

vector<Project> User::getUserProjects()
{
	vector<int> pID = associate->getProjects();
	vector<Project> associateProjects;
	Project project;
	bool exception = false;

	for (size_t i = 0; i < pID.size(); i++)
	{

		try
		{
			project = searchProjectByID(pID[i]);
		}
		catch (NotFound &e)
		{
			exception = true;
			associate->removeProject(pID[i]);
		}

		if (!exception)
			associateProjects.push_back(project);
	}
	updateAssociate(associate);
	saveAssociates("associates.txt");
	if (associateProjects.size() != 0)
	{
		Project::sortProjectsByDueDate(associateProjects);
	}
	
	return associateProjects;
}

vector<Associate*> User::getAssociates()
{
	return associates;
}

vector<Task> User::getAssociatesProjectTasks(Project& project, int associateID)
{
	vector<int> tasksID = project.getTasks();
	vector <Task> associatesTasks;
	Task task;
	bool exception = false;

	for (size_t i = 0; i < tasksID.size(); i++)
	{
		try
		{
			task = searchTaskByID(tasksID[i]);
		}
		catch (NotFound &e)
		{
			exception = true;
			project.removeTask(tasksID[i]);
		}

		if (!exception)
		{
			vector<int> associatesID = task.getAssociates();

			size_t k = 0;

			while ((k < associatesID.size()) && (associateID != associatesID[k]))
				k++;

			if (k != associatesID.size())  // associate was given this task
				associatesTasks.push_back(task);
		}
	}
	updateProject(project);
	saveProjects("projects.txt");
	Task::sortTasksByEstimatedTime(associatesTasks);
	return associatesTasks;
}

vector<Task> User::getProjectTasks(Project& project)
{
	vector<int> tasksID = project.getTasks();
	vector <Task> projectTasks;
	Task task;
	bool exception = false;
	
	for (size_t i = 0; i < tasksID.size(); i++)
	{
		
		try
		{
			task = searchTaskByID(tasksID[i]);
		}
		catch (NotFound &e)
		{
			exception = true;
			project.removeTask(tasksID[i]);
		}

		if (!exception)
			projectTasks.push_back(task);
	}
	updateProject(project);
	saveProjects("projects.txt");
	Task::sortTasksByEstimatedTime(projectTasks);
	return projectTasks;
}

float User::getAssociatesAvailableTime(Associate* associate)
{
	float availableTime = 21;   // 21 days per month
	vector<int> associatesProjects = associate->getProjects();
	for (size_t j = 0; j < associatesProjects.size(); j++)
	{
		Project project;
		try
		{
			project = searchProjectByID(associatesProjects[j]);
		}
		catch (NotFound &e) { }
		vector<Task> associatesTasks = getAssociatesProjectTasks(project, associate->getID());
		for (size_t k = 0; k < associatesTasks.size(); k++)
		{
			availableTime -= associatesTasks[k].getEstimatedTime();
		}
	}
	return availableTime;
}

vector<Associate*> User::getAvailableAssociates(float taskTime)
{
	vector<Associate*> availableAssociates;
	float availableTime = 0;

	for (size_t i = 0; i < associates.size(); i++)
	{
		availableTime = getAssociatesAvailableTime(associates[i]);
		if (availableTime >= taskTime)
			availableAssociates.push_back(associates[i]);
	}
	//sortByAvailableTime(availableAssociates);
	return availableAssociates;
}

float User::getProjectCost(Project& project)
{
	vector<Task> pTasks = getProjectTasks(project);
	float cost = 0;
	for (size_t i = 0; i < pTasks.size(); i++)
	{
		vector<int> tAssociates = pTasks[i].getAssociates();
		for (size_t j = 0; j < tAssociates.size(); j++)
		{
			Associate* a;
			try
			{
				a = searchAssociateByID(tAssociates[j]);
			}
			catch (NotFound &e)
			{
				e.what();
				return -1;
			}
			cost += a->getCost() * 8 * pTasks[i].getEstimatedTime();
		}
		
	}
	return cost;
}


void User::addProject(Project project)
{
	projects.push_back(project);
}

void User::addTask(Task task)
{
	tasks.push_back(task);
}

void User::addAssociate(Associate* associate)
{
	associates.push_back(associate);
}

void User::addClient(Client client)
{
	clients.push_back(client);
}

void User::setTaskAsFinished(Task task)
{
	// check for task dependencies
	vector<int> dependencies = task.getDependencies();
	for (size_t i = 0; i < dependencies.size(); i++)
	{
		if (!tasksIsDone(dependencies[i]))
			throw (TaskDepends(task.getID()));
	}
}


void User::updateProject(Project project)
{
	size_t i = 0;
	while (i < projects.size() && project.getID() != projects[i].getID())
		i++;

	if (i != projects.size())
		projects[i] = project;
}

void User::updateTask(Task task)
{
	size_t i = 0;
	while (i < tasks.size() && task.getID() != tasks[i].getID())
		i++;

	if (i != tasks.size())
		tasks[i] = task;
}

void User::updateAssociate(Associate* associate)
{
	size_t i = 0;
	while (i < associates.size() && associate->getID() != associates[i]->getID())
		i++;

	if (i != associates.size())
		associates[i] = associate;
}

void User::updateClient(Client client)
{
	size_t i = 0;
	while (i < clients.size() && client.getID() != clients[i].getID())
		i++;

	if (i != clients.size())
		clients[i] = client;
}


void User::removeProject(int projectID)
{
	size_t i = 0;
	while (i < projects.size() && projectID != projects[i].getID())
		i++;

	if (i != projects.size())
	{
		Client client = searchClientByID(projects[i].getClientID());
		updateClient(client);
		projects.erase(projects.begin() + i);
	}
}

void User::removeClient(int clientID)
{
	size_t i = 0;
	while (i < clients.size() && clientID != clients[i].getID())
		i++;

	if (i != clients.size())
		clients.erase(clients.begin() + i);
}

void User::removeAssociate(int associateID)
{
	size_t i = 0;
	while (i < associates.size() && associateID != associates[i]->getID())
		i++;

	if (i != associates.size())
		associates.erase(associates.begin() + i);
}

void User::removeTask(int taskID)
{
	size_t i = 0;
	while (i < tasks.size() && taskID != tasks[i].getID())
		i++;

	if (i != tasks.size())
		tasks.erase(tasks.begin() + i);
}


Project& User::searchProjectByID(int projectID)
{
	size_t i = 0;

	while ((i < projects.size()) && (projectID != projects[i].getID()))
		i++;

	if (i == projects.size())
		throw (NotFound("Project"));
	else return projects[i];
}

Client& User::searchClientByID(int clientID)
{
	size_t i = 0;

	while ((i < clients.size()) && (clientID != clients[i].getID()))
		i++;

	if (i == clients.size())
		throw (NotFound("Client"));
	else return clients[i];
}

Associate* User::searchAssociateByID(int associateID)
{
	size_t i = 0;

	while ((i < associates.size()) && (associateID != associates[i]->getID()))
		i++;

	if (i == associates.size())
		throw (NotFound("Associate"));
	else return associates[i];
}

Task& User::searchTaskByID(int taskID)
{
	size_t i = 0;

	while ((i < tasks.size()) && (taskID != tasks[i].getID()))
		i++;

	if (i == tasks.size())
		throw (NotFound("Task"));
	else return tasks[i];
}


bool User::validateLogin(unsigned int id, string password)
{
	unsigned int i = 0;

	// search for id in the associates vector
	while ((i < associates.size()) && (associates[i]->getID() != id))
		i++;

	if (i == associates.size())
		return false;
	else if (associates[i]->getPassword() == password)
	{
		associate = associates[i];
		if (associates[i]->getType() == "Manager") manager = true;
		else manager = false;
		return true;
	}
	else return false;
}

bool User::isManager() const
{
	return manager;
}

bool User::tasksIsDone(int taskID)
{
	size_t i = 0;
	bool exception = false;
	Task task;

	try
	{
		task = searchTaskByID(taskID);
	}
	catch (NotFound &e)
	{
		return true;
	}

	return task.getStatus();
}


void User::listProjects()
{
	for (size_t i = 0; i < projects.size(); i++)
		cout << "\t\t" << (i + 1) << ". " << projects[i] << endl;
}

void User::listAssociates()
{
	for (size_t i = 0; i < associates.size(); i++)
		cout << "\n\t\t" << (i + 1) << ". " << associates[i]->getName() << " (" << associates[i]->getType() << ")";
}

void User::listClients()
{
	for (size_t i = 0; i < clients.size(); i++)
		cout << "\t\t" << (i + 1) << ". " << clients[i].getName() << " (" << clients[i].getID() << ")" << endl;
}

void User::sortByAvailableTime(vector<Associate *> associatesToSort)
{
	float a1, a2;
	Associate* tmp;
	for (size_t i = 0; i < (associatesToSort.size() - 1); i++)
	{
		a1 = getAssociatesAvailableTime(associatesToSort[i]);
		for (size_t j = (i + 1); j < associatesToSort.size(); j++)
		{
			a2 = getAssociatesAvailableTime(associatesToSort[j]);
			if (a1 < a2)
			{
				tmp = associatesToSort[i];
				associatesToSort[i] = associatesToSort[j];
				associatesToSort[j] = tmp;
			}
		}
	}
}

// Exceptions

FileNotOpened::FileNotOpened(string fn) : filename(fn) { }

void FileNotOpened::what() const
{
	cout << "Error creating " << filename;
}

NotFound::NotFound(string n) : name(n) {}

void NotFound::what() const
{
	cout << name << " not found";
}

TaskDepends::TaskDepends(int tID) : taskID(tID) {}

void TaskDepends::what() const
{
	cout << "This task depends from tasks that are not finished";
}