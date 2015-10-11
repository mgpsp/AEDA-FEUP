#include "Application.h"

int Application::proxID = 0;

bool Application::operator<(const Application& a) const
{
	if (workingTime < a.getWorkingTime())
		return true;
	else if (workingTime > a.getWorkingTime())
		return false;
	else if (skills < a.getSkills())
		return true;
	else if (skills > a.getSkills())
		return false;
	else if (!pastAssociate && a.getPastAssociate())
		return true;
	else
		return false;
}