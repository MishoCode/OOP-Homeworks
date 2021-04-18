#include "Group.h"
#include<iostream>
#include<vector>

bool Group::hasMember(const Person& person) const
{
	std::function<bool(unsigned int, unsigned int)> rule = groupPayer->getPayerMemeberRule();
	return rule(person.getInsuranceId(), groupId);
}

Payer* Group::payer() const
{
	return groupPayer != nullptr ? groupPayer : nullptr;
}

bool Group::valid() const
{
	return groupPayer != nullptr;
}

void Group::setType()
{
	type = InstitutionType::GROUP;
}

InstitutionType Group::getType() const
{
	return this->type;
}

unsigned int Group::getClients(const std::vector<Person>& clients) const
{
	unsigned int counter = 0;
	for (auto i : clients)
	{
		if (this->hasMember(i))
			counter++;
	}
	return counter;
}

Institution* Group::clone()
{
	return new Group(*this);
}

std::string Group::getInstitutionId() const
{
	return std::to_string(institutionId) + '_' + std::to_string(groupId);
}

Group::Group(unsigned int groupId)
	:groupPayer(nullptr)
{
	this->setType();
	this->groupId = groupId;
	institutionId++;
}

void Group::setPayer(Payer* groupPayer)
{
	if (groupPayer->getTargetGroupId() == groupId)
	{
		this->groupPayer = groupPayer;
		groupPayer->incrementPayerGroupsCount();
	}
	else
	{
		std::cout << "This group payer cannot provide services to group with such an ID!" << std::endl;
	}
}
