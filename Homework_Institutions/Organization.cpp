#include "Organization.h"
#include<iostream>

bool Organization::hasMember(const Person& person) const
{
	for (auto i : institutionList)
	{
		if (i->hasMember(person))
			return true;
	}
	return false;
}

Payer* Organization::payer() const
{
	if (institutionList.empty())
	{
		return nullptr;
	}
		
	Payer* currentPayer = institutionList[0]->payer();
	for (auto i : institutionList)
	{
		if ( (i->getType() == InstitutionType::GROUP) &&
			(i->payer()->associatedGroups() > currentPayer->associatedGroups()) )
		{
			currentPayer = i->payer();
		}
	}
	return currentPayer;
}

bool Organization::valid() const
{
	bool groupFound = false;
	for (auto i : institutionList)
	{
		if (i->getType() == InstitutionType::GROUP)
		{
			groupFound = true;
			break;
		}
	}
	return groupFound;
}

void Organization::setType()
{
	type = InstitutionType::ORGANIZATION;
}

InstitutionType Organization::getType() const
{
	return this->type;
}

unsigned int Organization::getClients(const std::vector<Person>& clients) const
{
	unsigned int counter = 0;
	for (auto i : clients)
	{
		if (this->hasMember(i))
			counter++;
	}
	return counter;
}

void Organization::addInstitution(Institution* institution, bool forceAdding)
{
	if (forceAdding)
		institutionList.push_back(institution);
	else
	{
		if (!institutionList.empty() && !institution->valid())
		{
			std::cout << "Attempt to add invalid institution!" << std::endl;
			return;
		}

		if (!institutionList.empty() &&
			!(institution->getType() == InstitutionType::GROUP) && !(institution->payer() == this->payer()))
		{
			std::cout << "Attempt to add  incompatible institution!" << std::endl;
			return;
		}

		institutionList.push_back(institution);
	}
}

Institution* Organization::clone()
{
	return new Organization(*this);
}

std::string Organization::getInstitutionId() const
{
	return std::to_string(institutionId) + '_' + this->organizationAddress;
}

std::vector<Institution*> Organization::getInstitutionList() const
{
	return institutionList;
}

Organization::Organization(const std::vector<Institution*>& institutionList, const std::string& organizationAddress)
{
	this->setType();
	this->organizationAddress = organizationAddress;
	institutionId++;
	this->institutionList = institutionList;
}
