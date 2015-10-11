#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>

#include "User.h"

using namespace std;

int mainMenu();
int manageApp();
int associateMenu(int associateID);

User user;
string appPassword;

string enterPassword()
{
	bool show_asterisk = true;
	const char RETURN = 13;
	const char BACKSPACE = 8;
	unsigned char c;
	string pw;

	while ((c = _getch()) != RETURN)
	{
		if (c == BACKSPACE)
		{
			if (pw.size() != 0)
			{
				if (show_asterisk)
				{
					cout << "\b \b";
					pw.resize(pw.size() - 1);
				}
			}
		}
		else if (c == 0 || c == 224)
		{
			_getch();
			continue;
		}
		else if (isalnum(c))
		{
			pw += c;
			if (show_asterisk)
				cout << '*';
		}
	}

	return pw;
}

int listTasks(vector<Task>& tasks, int associateID)
{
	bool exception = false, done;
	for (size_t i = 0; i < tasks.size(); i++)
		cout << "\t\t" << (i + 1) << ". " << tasks[i] << endl;

	// Set task as finished
	char op;
	cout << "\n\tDo you want to change a task status? (y/n) ";
	cin >> op;
	while ((toupper(op) != 'Y') && (toupper(op) != 'N'))
	{
		cout << "\n\t   > ";
		cin >> op;
	}
	if (toupper(op) == 'Y')
	{
		cout << "\n\tTask number: ";
		int tIndex;
		cin >> tIndex;
		// Wait for valid task index
		while ((tIndex <= 0) || (tIndex > tasks.size()))
		{
			cout << "\n\t   > ";
			cin >> tIndex;
		}
		done = tasks[tIndex - 1].getStatus();
		if (done = false)
		{
			try
			{
				user.setTaskAsFinished(tasks[tIndex - 1]);
			}
			catch (TaskDepends &e)
			{
				exception = true;
				cout << "\n\t";
				e.what();
				cout << "\n";
			}
			if (!exception)
				done = true;
		}
		else
			done = false;

		Task task(tasks[tIndex - 1].getID(), tasks[tIndex - 1].getDescription(), tasks[tIndex - 1].getEstimatedTime(), tasks[tIndex - 1].getAssociates(), tasks[tIndex - 1].getDependencies(), done);
		user.updateTask(task);
		user.saveTasks("tasks.txt");

	}
	associateMenu(associateID);
	return 0;
}

int addTasksToProject(Project& project)
{
	string description, line;
	float estimatedTime;
	int aIndex, tIndex;
	stringstream ss;
	vector<int> associates;
	vector<int> dependencies;
	bool newTask, invalid;
	char c;

	do
	{
		cout << "\n\tDescription: ";
		cin.ignore(100, '\n');
		getline(cin, description);
		do
		{
			cout << "\tEstimated time (in days): ";
			getline(cin, line);
			ss << line;
			ss >> estimatedTime;
			if (estimatedTime <= 0)
			{
				cout << "\tInvalid time";
				invalid = true;
			}
			else
				invalid = false;
			ss.str("");
			ss.clear();
		} while (invalid);

		vector<Associate*> availableAssociates = user.getAvailableAssociates(estimatedTime);
		if (availableAssociates.size() > 0)
		{
			cout << "\n\tAvailable associates:\n ";
			for (size_t i = 0; i < availableAssociates.size(); i++)
				cout << "\n\t\t" << (i + 1) << ". " << availableAssociates[i]->getName() << " (" << availableAssociates[i]->getType() << ")";

			do
			{
				cout << "\n\n\t> ";
				ss.str("");
				ss.clear();
				getline(cin, line);
				ss << line;
				while (!ss.eof())
				{
					ss >> aIndex;
					if ((aIndex >= 1) && (aIndex <= availableAssociates.size()))
					{
						Associate* associate;
						associates.push_back(availableAssociates[aIndex - 1]->getID());
						associate = user.searchAssociateByID(availableAssociates[aIndex - 1]->getID());
						associate->addProject(project.getID());
					}

				}
			} while (associates.size() == 0);

			vector<Task> projectTasks = user.getProjectTasks(project);
			if (projectTasks.size() > 0)
			{
				cout << "\n\tDoes this task depend from other tasks? (y/n) ";
				cin >> c;
				cin.clear();
				while ((toupper(c) != 'Y') && (toupper(c) != 'N'))
				{
					cout << "\n\t   > ";
					cin >> c;
				}
				if (toupper(c) == 'Y')
				{
					cout << "\n\tProject tasks:\n\n";
					for (size_t i = 0; i < projectTasks.size(); i++)
						cout << "\t\t" << (i + 1) << ". " << projectTasks[i] << endl;

					cout << "\n\t> ";
					cin.ignore(100, '\n');
					getline(cin, line);
					ss.str("");
					ss.clear();
					ss << line;
					while (!ss.eof())
					{
						ss >> tIndex;
						if ((tIndex >= 1) && (tIndex <= projectTasks.size()))
							dependencies.push_back(projectTasks[tIndex - 1].getID());
					}
				}
			}
			Task task(description, estimatedTime, associates, dependencies);
			user.addTask(task);
			user.saveTasks("tasks.txt");
			user.saveAssociates("associates.txt");
			project.addTask(task.getID());
		}
		else
			cout << "\n\tThere are no available associates.\n";

		cout << "\n\tAdd another task? (y/n) ";
		cin >> c;
		cin.clear();
		while ((toupper(c) != 'Y') && (toupper(c) != 'N'))
		{
			cout << "\n\t   > ";
			cin >> c;
		}
		if (toupper(c) == 'Y')
			newTask = true;
		else
			newTask = false;
	} while (newTask);

	return 0;
}

int editProjectsTasks(Project& project, vector<Task>& tasks)
{
	string description, line;
	float estimatedTime;
	int aIndex, tIndex, index;
	stringstream ss;
	Associate* associate;
	vector<Task> associatesTasks;
	vector<int> taskAssociates;
	vector<int> associates;
	vector<int> dependencies;
	char c;
	bool editTask, invalid, exception = false, done;

	for (size_t i = 0; i < tasks.size(); i++)
		cout << "\t\t" << (i + 1) << ". " << tasks[i] << endl;

	do
	{
		cout << "\n\t> ";
		cin >> index;
		cin.clear();
		while (index < 1 || index > tasks.size())
		{
			cout << "\n\t> ";
			cin >> index;
			cin.clear();
		}

		done = tasks[index - 1].getStatus();
		cout << "\n\tChange task status? (y/n) ";
		cin >> c;
		cin.clear();
		while ((toupper(c) != 'Y') && (toupper(c) != 'N'))
		{
			cout << "\n\t   > ";
			cin >> c;
		}
		if (toupper(c) == 'Y')
		{
			if (done = false)
			{
				try
				{
					user.setTaskAsFinished(tasks[tIndex - 1]);
				}
				catch (TaskDepends &e)
				{
					exception = true;
					cout << "\n\t";
					e.what();
					cout << "\n";
				}
				if (!exception)
					done = true;
			}
			else
				done = false;
		}
			

		cout << "\n\tDescription: ";
		cin.ignore(100, '\n');
		getline(cin, description);
		if (description == "")
			description = tasks[index - 1].getDescription();
		do
		{
			cout << "\tEstimated time (in days): ";
			getline(cin, line);
			ss << line;
			if (!(ss >> estimatedTime))
			{
				estimatedTime = tasks[index - 1].getEstimatedTime();
				break;
			}
			ss >> estimatedTime;
			if (estimatedTime <= 0)
			{
				cout << "\tInvalid time\n";
				invalid = true;
			}
			else
				invalid = false;
			ss.str("");
			ss.clear();
		} while (invalid);
		Task task(tasks[index - 1].getID(), tasks[index - 1].getDescription(), estimatedTime, tasks[index - 1].getAssociates(), tasks[index - 1].getDependencies());
		user.updateTask(task);

		taskAssociates = tasks[index - 1].getAssociates();
		for (size_t i = 0; i < taskAssociates.size(); i++)
		{
			associate = user.searchAssociateByID(taskAssociates[i]);
			associatesTasks = user.getAssociatesProjectTasks(project, taskAssociates[i]);
			if (associatesTasks.size() == 1)
			{
				associate->removeProject(project.getID());
				user.updateAssociate(associate);
			}

		}

		vector<Associate*> availableAssociates = user.getAvailableAssociates(estimatedTime);
		if (availableAssociates.size() > 0)
		{
			cout << "\n\tAvailable associates:\n ";
			for (size_t i = 0; i < availableAssociates.size(); i++)
				cout << "\n\t\t" << (i + 1) << ". " << availableAssociates[i]->getName() << " (" << availableAssociates[i]->getType() << ")";

			do
			{
				cout << "\n\n\t> ";
				getline(cin, line);
				ss.str("");
				ss.clear();
				ss << line;
				while (!ss.eof())
				{
					ss >> aIndex;
					if ((aIndex >= 1) && (aIndex <= availableAssociates.size()))
					{
						Associate* associate;
						associates.push_back(availableAssociates[aIndex - 1]->getID());
						associate = user.searchAssociateByID(availableAssociates[aIndex - 1]->getID());
						associate->addProject(project.getID());
					}

				}
			} while (associates.size() == 0);
			

			vector<Task> projectTasks = user.getProjectTasks(project);
			if (projectTasks.size() > 0)
			{
				cout << "\n\tDoes this task depend from other tasks? (y/n) ";
				cin >> c;
				cin.clear();
				while ((toupper(c) != 'Y') && (toupper(c) != 'N'))
				{
					cout << "\n\t   > ";
					cin >> c;
				}
				if (toupper(c) == 'Y')
				{
					cout << "\n\tProject tasks:\n\n";
					for (size_t i = 0; i < projectTasks.size(); i++)
						cout << "\t\t" << (i + 1) << ". " << projectTasks[i] << endl;

					cout << "\n\t> ";
					cin.ignore(100, '\n');
					getline(cin, line);
					if (line == "")
						dependencies = tasks[index - 1].getDependencies();
					ss.str("");
					ss.clear();
					ss << line;
					while (!ss.eof())
					{
						ss >> tIndex;
						if ((tIndex >= 1) && (tIndex <= projectTasks.size()))
							dependencies.push_back(projectTasks[tIndex - 1].getID());
					}
				}
			}
			Task task(tasks[index - 1].getID(), description, estimatedTime, associates, dependencies, done);
			user.updateTask(task);
			user.saveTasks("tasks.txt");
			user.saveAssociates("associates.txt");
		}
		else
			cout << "\n\tThere are no available associates.\n";

		cout << "\n\tEdit another task? (y/n) ";
		cin >> c;
		cin.clear();
		while ((toupper(c) != 'Y') && (toupper(c) != 'N'))
		{
			cout << "\n\t   > ";
			cin >> c;
		}
		if (toupper(c) == 'Y')
			editTask = true;
		else
			editTask = false;
	} while (editTask);
	return 0;
}

int removeTasksFromProject(Project& project, vector<Task>& tasks)
{
	bool removeTask;
	int index;
	char c;
	vector<int> taskAssociates;
	vector<Task> associatesTasks;
	Associate* associate;
	cout << "\n\tProject tasks:\n";
	for (size_t i = 0; i < tasks.size(); i++)
		cout << "\t\t" << (i + 1) << ". " << tasks[i] << endl;

	do
	{
		cout << "\n\t> ";
		cin >> index;
		cin.clear();
		while (index < 1 || index > tasks.size())
		{
			cout << "\n\t> ";
			cin >> index;
			cin.clear();
		}
		taskAssociates = tasks[index - 1].getAssociates();
		for (size_t i = 0; i < taskAssociates.size(); i++)
		{
			associate = user.searchAssociateByID(taskAssociates[i]);
			associatesTasks = user.getAssociatesProjectTasks(project, taskAssociates[i]);
			if (associatesTasks.size() == 1)
			{
				associate->removeProject(project.getID());
				user.updateAssociate(associate);
			}

		}
		user.removeTask(tasks[index - 1].getID());
		user.saveTasks("tasks.txt");
		user.saveAssociates("associates.txt");
		project.removeTask(tasks[index - 1].getID());
		user.removeTask(tasks[index - 1].getID());
		cout << "\n\tRemove another task? (y/n) ";
		cin >> c;
		cin.clear();
		while ((toupper(c) != 'Y') && (toupper(c) != 'N'))
		{
			cout << "\n\t   > ";
			cin >> c;
		}
		if (toupper(c) == 'Y')
			removeTask = true;
		else
			removeTask = false;
	} while (removeTask);
	return 0;
}

int associateMenu(int associateID)
{
	system("cls");
	int op;
	vector<Project> userProjects;
	Project project;
	Date dD;
	vector<Task> projectTasks;
	cout << "\n";
	cout << "\n\t1. View my projects\n\t2. Go back\n\n\t> ";
	cin >> op;
	switch (op)
	{
	case 1:
		// List user projects
		userProjects = user.getUserProjects();

		if (userProjects.size() != 0)
		{
			cout << "\n\tMy projects:\n\n";
			for (size_t i = 0; i < userProjects.size(); i++)
				cout << "\t\t" << (i + 1) << ". " << userProjects[i] << endl;
		}
		else
		{
			cout << "\n\tNo projects found";
			associateMenu(associateID);
		}
			
		// Choose project
		int pIndex;
		cout << "\n\t> ";
		cin >> pIndex;
		// Wait for valid project index
		while ((pIndex <= 0) || (pIndex > userProjects.size()))
		{
			cout << "\n\t> ";
			cin >> pIndex;
		}
		cout << "\n";

		// Print project info
		project = userProjects[pIndex - 1];
		cout << "\n\tProject name: " << project.getName();
		dD = project.getDueDate();
		cout << "\n\tDue date: " << dD.day << "/" << dD.month << "/" << dD.year;

		projectTasks = user.getProjectTasks(project);

		if (user.isManager())
		{
			int op;
			cout << "\n\n\t1. View tasks\n\t2. Add task\n\t3. Edit task\n\t4. Remove task\n\n\t> ";
			cin >> op;
			while (op < 1 || op > 4)
			{
				cout << "\t> ";
				cin >> op;
			}
			switch (op)
			{
			case 1:
				if (projectTasks.size() != 0)
				{
					cout << "\n\tTasks:\n\n";
					listTasks(projectTasks, associateID);
				}
				else
					cout << "\n\tNo tasks found\n";
				associateMenu(associateID);
				break;
			case 2:
				addTasksToProject(project);
				user.updateProject(project);
				user.saveProjects("projects.txt");
				associateMenu(associateID);
				break;
			case 3:
				if (projectTasks.size() == 0)
				{
					cout << "\n\tNo tasks found\n";
					associateMenu(associateID);
				}
					
				editProjectsTasks(project, projectTasks);
				user.updateProject(project);
				user.saveProjects("projects.txt");
				associateMenu(associateID);
				break;
			case 4:
				if (projectTasks.size() == 0)
				{
					cout << "\n\tNo tasks found\n";
					associateMenu(associateID);
				}
				removeTasksFromProject(project, projectTasks);
				user.updateProject(project);
				user.saveProjects("projects.txt");
				associateMenu(associateID);
				break;
			default:
				break;
			}

		}
		else
		{
			// List associates tasks
			vector<Task> associatesTasks = user.getAssociatesProjectTasks(project, associateID);

			cout << "\n\n\tMy tasks:\n\n";
			listTasks(associatesTasks, associateID);
		}
		break;
	case 2:
		mainMenu();
		break;
	}
	return 0;
}

int logIn()
{
	system("cls");

	// Get log in info
	unsigned int id;
	string password;
	cout << "\n\tAssociate ID: ";
	cin >> id;
	cout << "\tPassword: ";
	password = enterPassword();

	if (user.validateLogin(id, password))
		associateMenu(id);
	else
	{
		cout << "\n\tWrong ID or password.\n";
		mainMenu();
	}

	return 0;
}

int generalInfo()
{
	system("cls");
	vector<Associate*> associates;
	vector<Project> projects;
	vector<Task> tasks;
	Task tTmp;
	Associate* aTmp;
	Project pTmp;
	int op, index;
	projects = user.getProjects();
	cout << "\n";
	cout << "\n\t1. List associates by available time\n\t2. List tasks by estimated conclusion time\n\t3. List projects by due date\n\t4. List projects by total cost\n\t5. Go back\n\n\t> ";
	cin >> op;
	while (op < 1 || op > 5)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\t> ";
		cin >> op;
	}
	switch (op)
	{
	case 1:
		associates = user.getAssociates();
		for (size_t i = 0; i < (associates.size() - 1); i++)
		{
			for (size_t j = (i + 1); j < associates.size(); j++)
			{
				if (user.getAssociatesAvailableTime(associates[i]) < user.getAssociatesAvailableTime(associates[j]))
				{
					aTmp = associates[i];
					associates[i] = associates[j];
					associates[j] = aTmp;
				}
			}
		}
		for (size_t i = 0; i < associates.size(); i++)
			cout << "\n\t\t" << associates[i]->getName() << " (" << associates[i]->getType() << ")";
		cin.ignore(100, '\n');
		cin.get();
		generalInfo();
		break;
	case 2:
		user.listProjects();
		cout << "\n\t> ";
		cin >> index;
		while (index < 1 || index > projects.size())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\t> ";
			cin >> index;
		}
		tasks = user.getProjectTasks(projects[index - 1]);
		if (tasks.size() == 0)
		{
			cout << "\n\tThis project doesn't have any tasks\n";
			cin.ignore(100, '\n');
			cin.get();
			generalInfo();
		}
		for (size_t i = 0; i < (tasks.size() - 1); i++)
		{
			for (size_t j = (i + 1); j < tasks.size(); j++)
			{
				if (tasks[i].getEstimatedTime() > tasks[j].getEstimatedTime())
				{
					tTmp = tasks[i];
					tasks[i] = tasks[j];
					tasks[j] = tTmp;
				}
			}
		}
		for (size_t i = 0; i < tasks.size(); i++)
			cout << "\t\t" << tasks[i] << endl;
		cin.ignore(100, '\n');
		cin.get();
		generalInfo();
		break;
	case 3:
		for (size_t i = 0; i < (projects.size() - 1); i++)
		{
			for (size_t j = (i + 1); j < projects.size(); j++)
			{
				if (projects[j].getDueDate() < projects[i].getDueDate())
				{
					pTmp = projects[i];
					projects[i] = projects[j];
					projects[j] = pTmp;
				}
			}
		}
		for (size_t i = 0; i < projects.size(); i++)
			cout << "\t\t" << projects[i] << endl;
		cin.ignore(100, '\n');
		cin.get();
		generalInfo();
		break;
	case 4:
		for (size_t i = 0; i < (projects.size() - 1); i++)
		{
			for (size_t j = (i + 1); j < projects.size(); j++)
			{
				if (user.getProjectCost(projects[i]) > user.getProjectCost(projects[j]))
				{
					pTmp = projects[i];
					projects[i] = projects[j];
					projects[j] = pTmp;
				}
			}
		}
		for (size_t i = 0; i < projects.size(); i++)
			cout << "\t\t" << projects[i] << endl;
		cin.ignore(100, '\n');
		cin.get();
		generalInfo();
		break;
	case 5:
		manageApp();
		break;
	default:
		break;
	}
	cin.ignore(100, '\n');
	cin.get();
	return 0;
}

int manageProjects()
{
	system("cls");
	int op, op2, day, month, year, clientID, pIndex, k, i, f;
	string name, type, line;
	stringstream ss;
	Date dueDate;
	char c;
	Project project;
	vector<int> tasks, date;
	vector<Project> projects;
	vector<Task> pTasks;
	bool invalid = false;
	Client client;
	Date dD;
	tasks.clear();
	projects = user.getProjects();
	if (projects.size() != 0)
	{
		cout << "\n\tProjects:\n\n";
		user.listProjects();
	}
	
	cout << "\n\t1. View projects\n\t2. Add project\n\t3. Edit project\n\t4. Remove project\n\t5. Go back\n\n\t> ";
	cin >> op;
	while (op < 1 || op > 5)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\t> ";
		cin >> op;
	}
	switch (op)
	{
	case 1:
		if (projects.size() == 0)
		{
			cout << "\n\tNo projects found\n";
			manageProjects();
		}
		cout << "\n\t> ";
		cin >> pIndex;
		while ((pIndex <= 0) || (pIndex > projects.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> pIndex;
		}
		project = projects[pIndex - 1];
		cout << "\n\tProject name: " << project.getName();
		dD = project.getDueDate();
		cout << "\n\tDue date: " << dD.day << "/" << dD.month << "/" << dD.year;
		cout << "\n\tType: " << project.getType();
		cout << "\n\tCost: " << user.getProjectCost(project) << "$";
		client = user.searchClientByID(project.getClientID());
		cout << "\n\tClient: " << client.getName() << " (" << client.getID() << ")";
		pTasks = user.getProjectTasks(project);
		if (pTasks.size() > 0)
		{
			cout << "\n\tTasks:\n";
			for (size_t i = 0; i < pTasks.size(); i++)
				cout << "\t\t" << pTasks[i] << endl;
		}
		cin.ignore(100, '\n');
		cin.get();
		manageProjects();
		break;
	case 2:
		cout << "\n\tName: ";
		cin.ignore(100, '\n');
		getline(cin, name);
		do
		{
			cout << "\tDue date: ";
			getline(cin, line);
			ss << line;
			i = 0;
			k = 0;
			while (!ss.eof() && i != 3)
			{
				i++;
				ss >> k;
				if (k > 0)
					date.push_back(k);
			}
			if (date.size() < 3)
			{
				date.clear();
				cout << "\tInvalid date\n";
				invalid = true;
			}
			else
				invalid = false;
			ss.str("");
			ss.clear();
		} while (invalid);
		day = date[0];
		month = date[1];
		year = date[2];
		cout << "\tType: ";
		getline(cin, type);
		do
		{
			invalid = false;
			cout << "\tClient ID: ";
			getline(cin, line);
			ss << line;
			ss >> clientID;
			try
			{
				client = user.searchClientByID(clientID);
			}
			catch (NotFound &e)
			{
				invalid = true;
				cout << "\t";
				e.what();
				cout << "\n";
			}
			ss.str("");
			ss.clear();
		} while (invalid);
		dueDate.day = day;
		dueDate.month = month;
		dueDate.year = year;
		project = Project(name, dueDate, type, tasks, clientID);
		client.addProject(project.getID());
		user.updateClient(client);
		user.saveClients("clients.txt");
		cout << "\n\tDo you want to add tasks to this project? (y/n) ";
		cin >> c;
		cin.clear();
		while ((toupper(c) != 'Y') && (toupper(c) != 'N'))
		{
			cout << "\n\t   > ";
			cin >> c;
		}
		if (toupper(c) == 'Y')
			addTasksToProject(project);

		user.addProject(project);
		user.saveProjects("projects.txt");
		manageProjects();
		break;
	case 3:
		cout << "\n\t> ";
		cin >> pIndex;
		while ((pIndex <= 0) || (pIndex > projects.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> pIndex;
		}
		cout << "\n\tName: ";
		cin.ignore(100, '\n');
		getline(cin, name);
		if (name == "")
			name = projects[pIndex - 1].getName();
		f = 0;
		do
		{
			cout << "\tDue date: ";
			getline(cin, line);
			if (line == "")
				break;
			ss << line;
			i = 0;
			k = 0;
			f = 1;
			while (!ss.eof() && i != 3)
			{
				i++;
				ss >> k;
				if (k > 0)
					date.push_back(k);
			}
			if (date.size() < 3)
			{
				date.clear();
				cout << "\tInvalid date\n";
				invalid = true;
			}
			else
				invalid = false;
			ss.str("");
			ss.clear();
		} while (invalid);
		if (f == 1)
		{
			day = date[0];
			month = date[1];
			year = date[2];
			dueDate.day = day;
			dueDate.month = month;
			dueDate.year = year;
		}
		else
			dueDate = projects[pIndex - 1].getDueDate();
		cout << "\tType: ";
		getline(cin, type);
		if (type == "")
			type = projects[pIndex - 1].getType();
		do
		{
			cout << "\tClient ID: ";
			getline(cin, line);
			if (line == "")
				clientID = projects[pIndex - 1].getClientID();
			break;
			ss << line;
			invalid = false;
			ss >> clientID;
			try
			{
				user.searchClientByID(clientID);
			}
			catch (NotFound &e)
			{
				invalid = true;
				cout << "\t";
				e.what();
				cout << "\n";
			}
			ss.str("");
			ss.clear();
		} while (invalid);


		pTasks = user.getProjectTasks(projects[pIndex - 1]);
		for (size_t i = 0; i < pTasks.size(); i++)
			tasks.push_back(pTasks[i].getID());
		project = Project(projects[pIndex - 1].getID(), name, dueDate, type, tasks, clientID);

		cout << "\n\t1. Add task\n\t2. Edit task\n\t3. Remove task\n\t4. Go back\n\n\t> ";
		cin >> op2;
		while (op2 < 1 || op2 > 4)
		{
			cout << "\t> ";
			cin >> op2;
		}
		switch (op2)
		{
		case 1:
			addTasksToProject(project);
			break;
		case 2:
			if (pTasks.size() == 0)
			{
				cout << "\n\tNo tasks found\n";
				manageProjects();
			}

			editProjectsTasks(project, pTasks);
			break;
		case 3:
			if (pTasks.size() == 0)
			{
				cout << "\n\tNo tasks found\n";
				manageProjects();
			}
			removeTasksFromProject(project, pTasks);
			break;
		case 4:
			manageProjects();
			break;
		}

		user.updateProject(project);
		user.saveProjects("projects.txt");
		manageProjects();
		break;
	case 4:
		cout << "\n\t> ";
		cin >> pIndex;
		while ((pIndex <= 0) || (pIndex > projects.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> pIndex;
		}
		user.removeProject(projects[pIndex - 1].getID());
		user.saveProjects("projects.txt");
		user.saveClients("clients.txt");
		manageProjects();
		break;
	case 5:
		manageApp();
		break;
	default:
		if (!cin.eof())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		else cin.clear();
		break;
	}

	cin.ignore(100, '\n');
	cin.get();
	return 0;
}

int manageAssociates()
{
	system("cls");
	int op, aIndex, op2;
	vector<Associate*> associates;
	vector<int> aProjects;
	Project proj;
	string name, password;
	Associate *associate;
	associates = user.getAssociates();
	if (associates.size() != 0)
	{
		cout << "\n\tAssociates:\n";
		user.listAssociates();
	}

	cout << "\n\n\t1. View associates\n\t2. Add associates\n\t3. Edit associates\n\t4. Remove associates\n\t5. Go back\n\n\t> ";
	cin >> op;
	while (op < 1 || op > 5)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\t> ";
		cin >> op;
	}
	switch (op)
	{
	case 1:
		if (associates.size() == 0)
		{
			cout << "\n\tNo associates found:\n";
			manageAssociates();
		}
		cout << "\n\t> ";
		cin >> aIndex;
		while ((aIndex <= 0) || (aIndex > associates.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> aIndex;
		}
		cout << "\n\tAssociate ID: " << associates[aIndex - 1]->getID();
		cout << "\n\tName: " << associates[aIndex - 1]->getName();
		cout << "\n\tType: " << associates[aIndex - 1]->getType();
		aProjects = associates[aIndex - 1]->getProjects();
		if (aProjects.size() > 0)
		{
			cout << "\n\tProjects:\n";
			for (size_t i = 0; i < aProjects.size(); i++)
			{
				proj = user.searchProjectByID(aProjects[i]);
				cout << "\t\t" << proj << endl;
			}
		}
		cin.ignore(100, '\n');
		cin.get();
		manageAssociates();
		break;
	case 2:
		cout << "\n\tName: ";
		cin.ignore(100, '\n');
		getline(cin, name);
		cout << "\tPassword: ";
		getline(cin, password);
		cout << "\n\t1. Programmer\n\t2. Designer\n\t3. Manager\n\t4. Tester\n\n\t> ";
		cin >> op2;
		while (op2 < 1 || op2 > 4)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\t> ";
			cin >> op2;
		}
		switch (op2)
		{
		case 1:
			user.addAssociate(new Programmer(name, password));
			break;
		case 2:
			user.addAssociate(new Designer(name, password));
			break;
		case 3:
			user.addAssociate(new Manager(name, password));
			break;
		case 4:
			user.addAssociate(new Tester(name, password));
			break;
		}
		user.saveAssociates("associates.txt");
		manageAssociates();
		break;
	case 3:
		cout << "\n\t> ";
		cin >> aIndex;
		while ((aIndex <= 0) || (aIndex > associates.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> aIndex;
		}
		cout << "\n\tName: ";
		cin.ignore(100, '\n');
		getline(cin, name);
		if (name == "")
			name = associates[aIndex - 1]->getName();
		cout << "\tPassword: ";
		getline(cin, password);
		if (password == "")
			password = associates[aIndex - 1]->getPassword();

		if (associates[aIndex - 1]->getType() == "Programmer")
			user.updateAssociate(new Programmer(associates[aIndex - 1]->getID(), name, password, associates[aIndex - 1]->getProjects()));
		else if (associates[aIndex - 1]->getType() == "Designer")
			user.updateAssociate(new Designer(associates[aIndex - 1]->getID(), name, password, associates[aIndex - 1]->getProjects()));
		else if (associates[aIndex - 1]->getType() == "Manager")
			user.updateAssociate(new Manager(associates[aIndex - 1]->getID(), name, password, associates[aIndex - 1]->getProjects()));
		else if (associates[aIndex - 1]->getType() == "Tester")
			user.updateAssociate(new Tester(associates[aIndex - 1]->getID(), name, password, associates[aIndex - 1]->getProjects()));
			
		user.saveAssociates("associates.txt");
		manageAssociates();
		break;
	case 4:
		cout << "\n\t> ";
		cin >> aIndex;
		while ((aIndex <= 0) || (aIndex > associates.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> aIndex;
		}
		user.removeAssociate(associates[aIndex - 1]->getID());
		user.saveAssociates("associates.txt");
		manageAssociates();
		break;
	case 5:
		manageApp();
		break;
	default:
		if (!cin.eof())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		else cin.clear();
		break;
	}
	return 0;
}

int manageClients()
{
	system("cls");
	int op, cIndex;
	vector<Client> clients;
	vector<int> cProjects;
	Project project;
	Client client;
	string name;
	clients = user.getClients();
	if (clients.size() != 0)
	{
		cout << "\n\tClients:\n";
		user.listClients();
	}
	
	cout << "\n\t1. View clients\n\t2. Add clients\n\t3. Edit clients\n\t4. Remove clients\n\t5. Go back\n\n\t> ";
	cin >> op;
	while (op < 1 || op > 5)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\t> ";
		cin >> op;
	}
	switch (op)
	{
	case 1:
		if (clients.size() == 0)
		{
			cout << "\n\tNo clients found\n";
			manageClients();
		}
		cout << "\n\t> ";
		cin >> cIndex;
		while ((cIndex <= 0) || (cIndex > clients.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> cIndex;
		}
		cout << "\n\tClient ID: " << clients[cIndex - 1].getID();
		cout << "\n\tName: " << clients[cIndex - 1].getName();
		cProjects = clients[cIndex - 1].getProjects();
		if (cProjects.size() > 0)
		{
			cout << "\n\tProjects:\n";
			for (size_t i = 0; i < cProjects.size(); i++)
			{
				project = user.searchProjectByID(cProjects[i]);
				cout << "\t\t" << project << endl;
			}
		}
		cin.ignore(100, '\n');
		cin.get();
		manageClients();
		break;
	case 2:
		cout << "\n\tName: ";
		cin.ignore(100, '\n');
		getline(cin, name);
		client = Client(name);
		user.addClient(client);
		user.saveClients("clients.txt");
		manageClients();
		break;
	case 3:
		cout << "\n\t> ";
		cin >> cIndex;
		while ((cIndex <= 0) || (cIndex > clients.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> cIndex;
		}
		cout << "\n\tName: ";
		cin.ignore(100, '\n');
		getline(cin, name);
		if (name == "")
			name = clients[cIndex - 1].getName();
		client = Client(clients[cIndex - 1].getID(), name);
		user.updateClient(client);
		user.saveClients("clients.txt");
		manageClients();
		break;
	case 4:
		cout << "\n\t> ";
		cin >> cIndex;
		while ((cIndex <= 0) || (cIndex > clients.size()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\n\t> ";
			cin >> cIndex;
		}
		user.removeClient(clients[cIndex - 1].getID());
		user.saveClients("clients.txt");
		manageClients();
		break;
	case 5:
		manageApp();
		break;
	default:
		if (!cin.eof())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		else cin.clear();
		break;
	}
	return 0;
}

int manageApp()
{
	system("cls");
	int op;
	cout << "\n\t1. General information\n\t2. Projects\n\t3. Associates\n\t4. Clients\n\t5. Go back\n\n\t> ";
	cin >> op;
	while (op < 1 || op > 5)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\t> ";
		cin >> op;
	}
	switch (op)
	{
	case 1:
		generalInfo();
		break;
	case 2:
		manageProjects();
		break;
	case 3:
		manageAssociates();
		break;
	case 4:
		manageClients();
		break;
	case 5:
		mainMenu();
		break;
	default:
		if (!cin.eof())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		else cin.clear();
		break;
	}
	return 0;
}

int mainMenu()
{
	system("cls");
	int op;
	string password;
	cout << "\n\t1. Log in\n\t2. Manage app\n\t3. Exit\n\n\t> ";
	cin >> op;
	while (op < 1 || op > 3)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\t> ";
		cin >> op;
	}
	switch (op)
	{
	case 1:
		logIn();
		break;
	case 2:
		system("cls");
		cout << "\n\tPassword: ";
		password = enterPassword();
		if (password == appPassword)
			manageApp();
		else
		{
			cout << "\n\tWrong password\n";
			mainMenu();
		}
		break;
	case 3:
		exit(0);
		break;
	default:
		if (!cin.eof())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}
		else cin.clear();
		break;
	}
	return 0;
}

int main()
{
	// Load information to vectors
	try
	{
		user.loadAssociates("associates.txt");
		user.loadClients("clients.txt");
		user.loadProjects("projects.txt");
		user.loadTasks("tasks.txt");
	}
	catch (FileNotOpened &e)
	{
		cout << "\t";
		e.what();
		cin.get();
	}

	ifstream fin;
	fin.open("password.txt");
	getline(fin, appPassword);
	fin.close();
	
	mainMenu();
	return 0;
}