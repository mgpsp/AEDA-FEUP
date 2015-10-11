/**
* @file Project.h
*
* @brief Header file for class Project*/

/**
* @file Project.cpp
*
* @brief Code for class Project*/

#ifndef _PROJECT
#define _PROJECT

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
* @brief Struct for the date
*
*/
struct Date
{
	unsigned int day, month, year;
};

/**
* @brief Overload of the operator <
*
* @param d1 First date
* @param d2 Seccond date
*
*/
bool operator<(Date& d1, Date& d2);

/**
* @brief Project class
*
*/
class Project
{
	static int proxID;  /*!< ID of the next project to be created*/
	unsigned int ID;  /*!< ID of the project*/
	string name; /*!< Name of the project*/
	Date dueDate;  /*!< Due date of the project*/
	vector<int> tasks;  /*!< Vector of the project's tasks*/
	string type;  /*!< Type of the project*/
	unsigned int clientID;  /*!< ID of the client that hired the company for this project*/
public:
	/**
	* @brief Default constructor for class Project
	*/
	Project();

	/**
	* @brief Destructor for class Project
	*/
	~Project() { };

	/**
	* @brief Constructor for class Task
	*
	* @param n Name of the project
	* @param dD Due date of the project
	* @param t Type of the project
	* @param ts Vector of the project's tasks
	* @param c ID of the client that hired the company for this project
	*/
	Project(string n, Date dD, string t, vector<int> ts, unsigned int c);

	/**
	* @brief Constructor for class Task
	*
	* @param i ID of the project
	* @param n Name of the project
	* @param dD Due date of the project
	* @param t Type of the project
	* @param ts Vector of the project's tasks
	* @param c ID of the client that hired the company for this project
	*/
	Project(int i, string n, Date dD, string t, vector<int> ts, unsigned int c);

	/**
	* @brief Updates de next ID static member
	*
	* @param pID ID of the next project to be created
	*/
	static void updateProxID(int pID);

	/**
	* @brief Get ID of the next project to be created
	*
	* @return Returns the ID of the next project to be created
	*/
	static int getProxID();

	/**
	* @brief Get ID of the project
	*
	* @return Returns the ID of the project
	*/
	unsigned int getID() const;

	/**
	* @brief Get name of the project
	*
	* @return Returns the name of the project
	*/
	string getName() const;

	/**
	* @brief Get due date of the project
	*
	* @return Returns the due date of the project
	*/
	Date getDueDate() const;

	/**
	* @brief Get vector of the project's tasks
	*
	* @return Returns the vector of the project's tasks
	*/
	vector<int> getTasks() const;

	/**
	* @brief Get type of the project
	*
	* @return Returns the type of the project
	*/
	string getType() const;

	/**
	* @brief Get ID of the client that hired the company for this project
	*
	* @return Returns the ID of the client that hired the company for this project
	*/
	unsigned int getClientID() const;

	/**
	* @brief Remove task from the vector of the projects's tasks
	*
	* @param taskID ID of the task to remove
	*/
	void removeTask(int taskID);

	/**
	* @brief Add task to the vector of the projects's tasks
	*
	* @param taskID ID of the task to add
	*/
	void addTask(int taskID);

	/**
	* @brief Sort a vector of projects by the due date of the project
	*
	* @param projects Vector of projects to sort
	*/
	static void sortProjectsByDueDate(vector<Project>& projects);

	/**
	* @brief Overload of the operator <<
	*
	* @param out Out stream
	* @param project Project to print
	*/
	friend ostream& operator<<(ostream& out, const Project& project);
};



#endif