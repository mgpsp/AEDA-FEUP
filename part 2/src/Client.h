/**
* @file Client.h
*
* @brief Header file for class Client*/

/**
* @file Client.cpp
*
* @brief Code for class Client*/

#ifndef _CLIENT
#define _CLIENT

#include <iostream>
#include <vector>

using namespace std;


/**
* @brief Client class
*
*/
class Client
{
	static int proxID;  /*!< ID of the next client to be created*/
	unsigned int ID; /*!< ID of the client*/
	string name;  /*!< Name of the client*/
	vector<int> projects; /*!< Vector with the client's projects*/
public:
	/**
	* @brief Default constructor for class Client
	*/
	Client();

	/**
	* @brief Destructor for class User
	*/
	~Client() { };

	/**
	* @brief Constructor for class Client
	*
	* @param n Name of the client
	*/
	Client(string n);

	/**
	* @brief Constructor for class Client
	*
	* @param i ID of the client
	* @param n Name of the client
	*/
	Client(int i, string n);

	/**
	* @brief Constructor for class Client
	*
	* @param i ID of the client
	* @param n Name of the client
	* @param p Vector with the client's projects
	*/
	Client(int i, string n, vector<int> p);

	/**
	* @brief Updates de next ID static member
	*
	* @param pID ID of the next client to be created
	*/
	static void updateProxID(int pID);

	/**
	* @brief Get ID of the next client to be created
	*
	* @return Returns the ID of the next client to be created
	*/
	static int getProxID();

	/**
	* @brief Get ID of the client
	*
	* @return Returns the ID of the client
	*/
	int getID() const;

	/**
	* @brief Get name of the client
	*
	* @return Returns the name of the client
	*/
	string getName() const;

	/**
	* @brief Get the client's projects
	*
	* @return Returns the client's projects
	*/
	vector<int> getProjects() const;

	/**
	* @brief Add project to the vector of the client's projects
	*
	* @param projectID ID of the project to add
	*/
	void addProject(int projectID);

	/**
	* @brief Remove project from the vector of the client's projects
	*
	* @param projectID ID of the project to remove
	*/
	void removeProject(int projectID);

	/**
	* @brief Overload of the operator <
	*
	* Based on the total amount paid by the client
	*
	* @param c1 Client to compare
	* @return Returns true if total amount paid by the given client is greater
	*/
	bool operator<(const Client& c1) const;

	/**
	* @brief Overload of the operator ==
	*
	* @param c1 Client to compare
	* @return Returns true if the id's match
	*/
	bool operator==(const Client& c1) const;
};

#endif