/**
* @file User.h
*
* @brief Header file for class User*/

/**
* @file User.cpp
*
* @brief Code for class User*/

#ifndef _USER
#define _USER

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>

#include "Associate.h"
#include "Client.h"
#include "Project.h"
#include "Task.h"
#include "Application.h"
#include "BST.h"

using namespace std;

/**
* @brief Struct with the hash function for the the old associates hash table
*
*/
struct hAssociate
{
	int operator()(const Associate* a) const
	{
		return a->getID();
	}

	bool operator()(const Associate* a1, const Associate* a2) const
	{
		return (a1->getID() == a2->getID());
	}
};

typedef tr1::unordered_set<Associate*, hAssociate, hAssociate> hashAssociate;

/**
* @brief User class
* 
* Class where the application info is stored
*/

class User
{
	vector<Associate *> associates; /*!< Vector with the company's associates*/
	hashAssociate oldAssociates; /*!< Hash table with the company's old associates*/
	vector<Client> clients; /*!< Vector with the company's clients*/
	BST<Client> clients_bst; /*!< BST with the company's clients*/
	vector<Project> projects; /*!< Vector with the company's projects*/
	vector<Task> tasks; /*!< Vector with the project's tasks*/
	priority_queue<Application> applications;  /*!< Priority queue with the company's applications*/
	Associate* associate; /*!< Associate currently loged in*/
	bool manager; /*!< "true" if the associate is a project manager*/
public:
	/**
	* @brief Default constructor for class User
	*/
	User();

	/**
	* @brief Destructor for class User
	*/
	~User() {};

	/**
	* @brief Loads associates from the file to the vector
	*
	* @param filename Associates filename
	*/
	void loadAssociates(string filename);

	/**
	* @brief Loads old associates from the file to the hash table
	*
	* @param filename Old associates filename
	*/
	void loadOldAssociates(string filename);

	/**
	* @brief Loads clients from the file to the vector
	*
	* @param filename Clients filename
	*/
	void loadClients(string filename);

	/**
	* @brief Loads projects from the file to the vector
	*
	* @param filename Projects filename
	*/
	void loadProjects(string filename);

	/**
	* @brief Loads applications from the file to the priority queue
	*
	* @param filename Applications filename
	*/
	void loadApplications(string filename);

	/**
	* @brief Loads tasks from the file to the vector
	*
	* @param filename Tasks filename
	*/
	void loadTasks(string filename);

	/**
	* @brief Saves associates vector to file
	*
	* @param filename Associates filename
	*/
	void saveAssociates(string filename);

	/**
	* @brief Saves old associates hash table to file
	*
	* @param filename Associates filename
	*/
	void saveOldAssociates(string filename);

	/**
	* @brief Saves clients vector to file
	*
	* @param filename Clients filename
	*/
	void saveClients(string filename);

	/**
	* @brief Saves projects vector to file
	*
	*@param filename Projects filename
	*/
	void saveProjects(string filename);

	/**
	* @brief Saves tasks vector to file
	*
	* @param filename Tasks filename
	*/
	void saveTasks(string filename);

	/**
	* @brief Saves applications priority queue to file
	*
	* @param filename Applications filename
	*/
	void saveApplications(string filename);

	/**
	* @brief Get company's projects
	*
	*@return Returns a vector of projects with the company's projects
	*/
	vector<Project> getProjects();

	/**
	* @brief Get company's clients
	*
	* @return Returns a BST of clients with the company's clients
	*/
	BST<Client> getClients();

	/**
	* @brief Get current user's projects
	*
	* @return Returns a vector of projects with the current user's projects
	*/
	vector<Project> getUserProjects();

	/**
	* @brief Get company's associates
	*
	* @return Returns a vector of pointers to associates with the company's assocites
	*/
	vector<Associate*> getAssociates();

	/**
	* @brief Get company's old associates
	*
	* @return Returns a hash table of pointers to associates with the company's old associates
	*/
	hashAssociate getOldAssociates();

	/**
	* @brief Get company's application
	*
	* @return Returns a priority queue with the company's applications
	*/
	priority_queue<Application> getApplications();

	/**
	* @brief Get the associate's project tasks
	*
	* @param project Project to check
	* @param associateID The id of the associate
	* @return Returns a vector of tasks with the associates project tasks
	*/
	vector<Task> getAssociatesProjectTasks(Project& project, int associateID);

	/**
	* @brief Get project's tasks
	*
	* @param project Project to check
	* @return Returns a vector of tasks with the project's tasks
	*/
	vector<Task> getProjectTasks(Project& project);

	/**
	* @brief Get an associate's available time
	*
	* @param associate Associate to check
	* @return Returns the associate's available time
	*/
	float getAssociatesAvailableTime(Associate* associate);

	/**
	* @brief Get available associates for a task
	*
	* @param taskTime Estimated time to the conclusion of the task
	* @return Returns a vector of pointers to associates with the available associates for the given task
	*/
	vector<Associate*> getAvailableAssociates(float taskTime);

	/**
	* @brief Get project's cost
	*
	* The total cost is based on the number of associates and how much they cost
	*
	* @param project Project to check
	* @return Returns the total cost of a project
	*/
	float getProjectCost(Project& project);

	/**
	* @brief Add project to the vector of projects
	*
	* @param project Project to add
	*/
	void addProject(Project project);

	/**
	* @brief Add task to the vector of tasks
	*
	* @param task Task to add
	*/
	void addTask(Task task);

	/**
	* @brief Add associate to the vector of associates
	*
	* @param associate Associate to add
	*/
	void addAssociate(Associate* associate);

	/**
	* @brief Add old associate to the hash table of old associates
	*
	* @param associate Associate to add
	*/
	void addOldAssociate(Associate* associate);

	/**
	* @brief Add client to the BST of clients
	*
	* @param client Client to add
	*/
	void addClient(Client client);

	/**
	* @brief Add application to the priority queue of applications
	*
	* @param application Application to add
	*/
	void addApplication(Application application);

	/**
	* @brief Set a task as finished
	*
	* @param task Task to set as finished
	*/
	void setTaskAsFinished(Task task);

	/**
	* @brief Update project
	*
	* Search for the project id and replace the project
	*
	* @param project Project to update
	*/
	void updateProject(Project project);

	/**
	* @brief Update task
	*
	* Search for the task id and replace the task
	*
	* @param task Task to update
	*/
	void updateTask(Task task);

	/**
	* @brief Update associate
	*
	* Search for the associate id and replace the associate
	*
	* @param associate Associate to update
	*/
	void updateAssociate(Associate* associate);

	/**
	* @brief Update old associate
	*
	* Search for the associate id and replace the associate
	*
	* @param associate Associate to update
	*/
	void updateOldAssociate(Associate* associate);

	/**
	* @brief Update client
	*
	* Search for the client id and replace the client
	*
	* @param client Client to update
	*/
	void updateClient(Client client);

	/**
	* @brief Update application
	*
	* Search for the application id and replace the application
	*
	* @param application Application to update
	*/
	void updateApplication(Application application);

	/**
	* @brief Remove project
	*
	* Remove project with the given id
	*
	* @param projectID ID of the project to remove
	*/
	void removeProject(int projectID);

	/**
	* @brief Remove client
	*
	* Remove the given client
	*
	* @param client Client to remove
	*/
	void removeClient(Client client);

	/**
	* @brief Remove associate
	*
	* Remove associate with the given id
	*
	* @param associateID ID of the associate to remove
	*/
	void removeAssociate(int associateID);

	/**
	* @brief Remove old associate
	*
	* Remove associate with the given id
	*
	* @param associate Associate to remove
	*/
	void removeOldAssociate(Associate* associate);

	/**
	* @brief Remove task
	*
	* Remove task with the given id
	*
	* @param taskID ID of the task to remove
	*/
	void removeTask(int taskID);

	/**
	* @brief Remove application
	*
	* Remove application with the given id
	*
	* @param applicationID ID of the application to remove
	*/
	void removeApplication(int applicationID);

	/**
	* @brief Search project by the project id
	*
	* @param projectID ID of the project to search
	* @return Returns a reference to the project
	*/
	Project& searchProjectByID(int projectID);

	/**
	* @brief Search client by the client id
	*
	* @param clientID ID of the client to search
	* @return Returns a reference to the client
	*/
	Client& searchClientByID(int clientID);

	/**
	* @brief Search associate by the associate id
	*
	* @param associateID ID of the associate to search
	* @return Returns a reference to the associate
	*/
	Associate* searchAssociateByID(int associateID);

	/**
	* @brief Search task by the task id
	*
	* @param taskID ID of the task to search
	* @return Returns a reference to the task
	*/
	Task& searchTaskByID(int taskID);

	/**
	* @brief Validate login
	*
	* Checks if the associate exists and if the password is correct
	*
	* @param id ID of the associate
	* @param password Password of the associate
	* @return Returns true if the associate exists and if the password is correct
	*/
	bool validateLogin(unsigned int id, string password);

	/**
	* @brief Checks if a given associate is a project manager
	*
	* @return Returns true if the associate is a project manager
	*/
	bool isManager() const;

	/**
	* @brief Checks if a given task is set as done
	*
	* @param taskID ID of the task to check
	* @return Returns true if the task is set as done
	*/
	bool tasksIsDone(int taskID);

	/**
	* @brief Lists the company's projects
	*
	*/
	void listProjects();

	/**
	* @brief Lists the company's associates
	*
	*/
	void listAssociates();

	/**
	* @brief Lists the company's old associates
	*
	*/
	void listOldAssociates();

	/**
	* @brief Lists the company's clients
	*
	* @return Returns number of clients listed
	*/
	int listClients();

	/**
	* @brief Lists the company's applications
	*/
	void listApplications();

	/**
	* @brief Sort a vector of associates by available time
	*
	*/
	void sortByAvailableTime(vector<Associate *> associatesToSort);
};

// Exceptions

/**
* @brief Exception for file not opened
*
* Thrown when fout.open fails
*/

class FileNotOpened
{
	string filename; /*!< Name of the file*/
public:
	/**
	* @brief Constructor
	*
	* @param fn Filename
	*/
	FileNotOpened(string fn);

	/**
	* @brief Destructor
	*
	*/
	~FileNotOpened() { };

	/**
	* @brief Explanation of the exception
	*
	*/
	void what() const;
};


/**
* @brief Exception for id's not found
*
* Thrown when the id isn't found in the vector
*/
class NotFound
{
	string name;
public:
	NotFound(string n);
	~NotFound() { };
	void what() const;
};

/**
* @brief Exception for task dependencies
*
* Thrown when a task that depends from tasks that are not yet finished is set as done
*/
class TaskDepends
{
	int taskID;
public:
	TaskDepends(int tID);
	~TaskDepends() { };
	void what() const;
};

#endif