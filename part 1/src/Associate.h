/**
* @file Associate.h
*
* @brief Header file for class Associate*/

/**
* @file Associate.cpp
*
* @brief Code for class Associate*/

#ifndef _ASSOCIATE
#define _ASSOCIATE

#define PROGRAMMER_COST 2
#define DESIGNER_COST 1.5
#define MANAGER_COST 3
#define TESTER_COST 1

#include <iostream>
#include <vector>

using namespace std;

/**
* @brief Associate class
*
*/
class Associate
{
	static int proxID;  /*!< ID of the next associate to be created*/
	unsigned int ID;  /*!< ID of the associate*/
	string name;  /*!< Name of the associate*/
	string password; /*!< Password of the associate*/
	vector<int> projects;  /*!< Vector with the associate's projects*/
public:
	/**
	* @brief Default constructor for class Associate
	*/
	Associate();

	/**
	* @brief Destructor for class Associate
	*/
	~Associate() { };

	/**
	* @brief Constructor for class Associate
	*
	* @param i ID of the associate
	* @param n Name of the associate
	* @param p Password of the associate
	* @param v Vector with the associate's projects
	*/
	Associate(int i, string n, string p, vector<int> v);

	/**
	* @brief Constructor for class Associate
	*
	* @param n Name of the associate
	* @param p Password of the associate
	*/
	Associate(string n, string p);

	/**
	* @brief Updates de next ID static member
	*
	* @param pID ID of the next associate to be created
	*/
	static void updateProxID(int pID);

	/**
	* @brief Get ID of the next associate to be created
	*
	* @return Returns the ID of the next associate to be created
	*/
	static int getProxID();

	/**
	* @brief Get ID of the associate
	*
	* @return Returns the ID of the associate
	*/
	unsigned int getID() const;

	/**
	* @brief Get name of the associate
	*
	* @return Returns the name of the associate
	*/
	string getName() const;

	/**
	* @brief Get password of the associate
	*
	* @return Returns the password of the associate
	*/
	string getPassword() const;

	/**
	* @brief Get type of the associate
	*
	* @return Returns the type of the associate
	*/
	virtual string getType() const = 0;

	/**
	* @brief Get cost of the associate
	*
	* @return Returns the cost of the associate
	*/
	virtual float getCost() const = 0;

	/**
	* @brief Get vector with the associate's projects
	*
	* @return Returns the vector with the associate's projects
	*/
	vector<int> getProjects() const;

	/**
	* @brief Add project to the vector of the associate's projects
	*
	* @param projectID ID of the project to add
	*/
	void addProject(int projectID);

	/**
	* @brief Remove project from the vector of the associate's projects
	*
	* @param projectID ID of the project to remove
	*/
	void removeProject(int projectID);
};

/**
* @brief Programmer class
*
*/
class Programmer : public Associate
{
public:
	/**
	* @brief Constructor for class Programmer
	*
	* @param i ID of the associate
	* @param n Name of the associate
	* @param p Password of the associate
	* @param v Vector with the associate's projects
	*/
	Programmer(int i, string n, string p, vector<int> v);

	/**
	* @brief Constructor for class Programmer
	*
	* @param n Name of the associate
	* @param p Password of the associate
	*/
	Programmer(string n, string p);

	/**
	* @brief Get type of the associate
	*
	* @return Returns the type of the associate
	*/
	string getType() const { return "Programmer"; };

	/**
	* @brief Get cost of the associate
	*
	* @return Returns the cost of the associate
	*/
	float getCost() const  { return PROGRAMMER_COST; };
};

/**
* @brief Designer class
*
*/
class Designer : public Associate
{
public:
	/**
	* @brief Constructor for class Designer
	*
	* @param i ID of the associate
	* @param n Name of the associate
	* @param p Password of the associate
	* @param v Vector with the associate's projects
	*/
	Designer(int i, string n, string p, vector<int> v);

	/**
	* @brief Constructor for class Designer
	*
	* @param n Name of the associate
	* @param p Password of the associate
	*/
	Designer(string n, string p);

	/**
	* @brief Get type of the associate
	*
	* @return Returns the type of the associate
	*/
	string getType() const { return "Designer"; };
	float getCost() const { return DESIGNER_COST; };
};

/**
* @brief Manager class
*
*/
class Manager : public Associate
{
public:
	/**
	* @brief Constructor for class Manager
	*
	* @param i ID of the associate
	* @param n Name of the associate
	* @param p Password of the associate
	* @param v Vector with the associate's projects
	*/
	Manager(int i, string n, string p, vector<int> v);

	/**
	* @brief Constructor for class Manager
	*
	* @param n Name of the associate
	* @param p Password of the associate
	*/
	Manager(string n, string p);

	/**
	* @brief Get type of the associate
	*
	* @return Returns the type of the associate
	*/
	string getType() const { return "Manager"; };

	/**
	* @brief Get cost of the associate
	*
	* @return Returns the cost of the associate
	*/
	float getCost() const { return MANAGER_COST; };
};

/**
* @brief Tester class
*
*/
class Tester : public Associate
{
public:
	/**
	* @brief Constructor for class Tester
	*
	* @param i ID of the associate
	* @param n Name of the associate
	* @param p Password of the associate
	* @param v Vector with the associate's projects
	*/
	Tester(int i, string n, string p, vector<int> v);

	/**
	* @brief Constructor for class Tester
	*
	* @param n Name of the associate
	* @param p Password of the associate
	*/
	Tester(string n, string p);
	/**
	* @brief Get type of the associate
	*
	* @return Returns the type of the associate
	*/
	string getType() const { return "Tester"; };

	/**
	* @brief Get cost of the associate
	*
	* @return Returns the cost of the associate
	*/
	float getCost() const { return TESTER_COST; };
};

#endif