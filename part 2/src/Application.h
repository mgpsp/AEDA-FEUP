/**
* @file Application.h
*
* @brief Header file for class Application*/

/**
* @file Application.cpp
*
* @brief Code for class Application*/

#include <iostream>
#include <vector>

using namespace std;

/**
* @brief  Application class
*
*/
class Application
{
	static int proxID;
	int ID; /*!< ID of the application*/
	string name;  /*!< Name of the applicant*/
	int workingTime;  /*!< Experience of the applicant in years*/
	int skills; /*!< Number of skills of the applicant*/
	bool pastAssociate; /*!< True if applicant was an associate of the company in the past*/
public:
	/**
	* @brief Default constructor for class Application
	*/
	Application() {};

	/**
	* @brief Destructor for class Application
	*/
	~Application() {};

	/**
	* @brief Constructor for class Application
	*
	* @param n Name of the applicant
	* @param wt Experience of the applicant
	* @param s Number of skills of the applicant
	* @param pa True if applicant was an associate of the company in the past
	*/
	Application(string n, int wt, int s, bool pa) : ID(proxID), name(n), workingTime(wt), skills(s), pastAssociate(pa) { updateProxID(++proxID); };

	/**
	* @brief Constructor for class Application
	*
	* @param ID ID of the application
	* @param n Name of the applicant
	* @param wt Experience of the applicant
	* @param s Number of skills of the applicant
	* @param pa True if applicant was an associate of the company in the past
	*/
	Application(int ID, string n, int wt, int s, bool pa) : ID(ID), name(n), workingTime(wt), skills(s), pastAssociate(pa) { };

	/**
	* @brief Updates de next ID static member
	*
	* @param pID ID of the next application to be created
	*/
	static void updateProxID(int pID) { proxID = pID; };

	/**
	* @brief Get ID of the next application to be created
	*
	* @return Returns the ID of the next application to be created
	*/
	static int getProxID() { return proxID; };

	/**
	* @brief Get ID of the application
	*
	* @return Returns the ID of the application
	*/
	int getID() const { return ID; };

	/**
	* @brief Get name of the applicant
	*
	* @return Returns the name of the applicant
	*/
	string getName() const { return name; };

	/**
	* @brief Get experience of the applicant
	*
	* @return Returns the experience of the applicant
	*/
	int getWorkingTime() const { return workingTime; };

	/**
	* @brief Get skills of the applicant
	*
	* @return Returns the number of skills of the applicant
	*/
	int getSkills() const { return skills; };

	/**
	* @brief Get past associate of the applicant
	*
	* @return Returns true if applicant was an associate of the company in the past
	*/
	bool getPastAssociate() const { return pastAssociate; };

	/**
	* @brief Overload of the operator <
	*
	* Based on the years of experience, number of skills and if the associate was hired by the company in the past
	*
	* @return Returns true if the given application is greater
	*/
	bool operator<(const Application& a) const;
};