#pragma once
#include"InstitutionType.h"
#include"Payer.h"
#include<string>
#include<vector>
#include"Person.h"

class Institution
{
public:
	virtual bool hasMember(const Person& person) const = 0;
	virtual Payer* payer() const = 0;
	virtual bool valid() const = 0;
	virtual void setType() = 0;
	virtual InstitutionType getType()const = 0;
	virtual unsigned int getClients(const std::vector<Person>& clients) const = 0;
	virtual Institution* clone() = 0;
	virtual std::string getInstitutionId() const = 0;
protected:
	std::string institutionName;
	static unsigned int institutionId;

	InstitutionType type;
};

