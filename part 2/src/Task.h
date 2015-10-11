/**
* @file Task.h
*
* @brief Header file for class Task*/

/**
* @file Task.cpp
*
* @brief Code for class Task*/

#ifndef _TASK
#define _TASK

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
* @brief Task class
*
*/
class Task
{
	static int proxID;  /*!< ID of the next task to be created*/
	unsigned int ID;  /*!< ID of the task*/
	string description;  /*!< Description of the task*/
	float estimatedTime;  // in days  /*!< Estimated time to the conclusion of the task*/
	vector<int> associates; /*!< Vector of associates working on the task*/
	vector<int> dependencies;  /*!< Vector of tasks of which the task depends*/
	bool done;  /*!< "true" if the task is done */
public:
	/**
	* @brief Default constructor for class Task
	*/
	Task();

	/**
	* @brief Destructor for class Task
	*/
	~Task() { };

	/**
	* @brief Constructor for class Task
	*
	* @param d Task description
	* @param eT Estimated time to the conclusion of the task
	* @param a Vector of associates working on the task
	* @param dP Vector of tasks of which the task depends
	*/
	Task(string d, float eT, vector<int> a, vector<int> dP);

	/**
	* @brief Constructor for class Task
	*
	* @param i ID of the task
	* @param d Task description
	* @param eT Estimated time to the conclusion of the task
	* @param a Vector of associates working on the task
	* @param dP Vector of tasks of which the task depends
	*/
	Task(int i, string d, float eT, vector<int> a, vector<int> dP);

	/**
	* @brief Constructor for class Task
	*
	* @param i ID of the task
	* @param d Task description
	* @param eT Estimated time to the conclusion of the task
	* @param a Vector of associates working on the task
	* @param dP Vector of tasks of which the task depends
	* @param dn "true" if the task is done
	*/
	Task(int i, string d, float eT, vector<int> a, vector<int> dP, bool dn);

	/**
	* @brief Updates de next ID static member
	*
	* @param pID ID of the next task to be created
	*/
	static void updateProxID(int pID);

	/**
	* @brief Get ID of the next task to be created
	*
	* @return Returns the ID of the next task to be created
	*/
	static int getProxID();

	/**
	* @brief Get ID of the task
	*
	* @return Returns the ID of the task
	*/
	int getID() const;

	/**
	* @brief Get description of the task
	*
	* @return Returns the description of the task
	*/
	string getDescription() const;

	/**
	* @brief Get estimated time to the conclusion of the task
	*
	* @return Returns the estimated time to the conclusion of the task
	*/
	float getEstimatedTime() const;

	/**
	* @brief Get vector of associates working on the task
	*
	* @return Returns the vector of associates working on the task
	*/
	vector<int> getAssociates() const;

	/**
	* @brief Get vector of tasks of which the task depends
	*
	* @return Returns the vector of tasks of which the task depends
	*/
	vector<int> getDependencies() const;

	/**
	* @brief Get the status of the task (done or not done)
	*
	* @return Returns the status of the task
	*/
	bool getStatus() const;

	/**
	* @brief Set the status of the task (done or not done)
	*
	* @param status Status to set
	*/
	void setDone(bool status);

	/**
	* @brief Sort a vector of tasks by the estimated time to the conclusion of the task
	*
	* @param tasks Vector of tasks to sort
	*/
	static void sortTasksByEstimatedTime(vector<Task>& tasks);

	/**
	* @brief Removes the associate with the given ID from the task
	*
	* @param associateID ID of the associate to remove
	*/
	void removeAssociate(int associateID);

	/**
	* @brief Overload of the operator <<
	*
	* @param out Out stream
	* @param task Task to print
	*/
	friend ostream& operator<<(ostream& out, const Task& task);
};

#endif