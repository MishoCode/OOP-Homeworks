#include "Person.h"

Person::Person(const std::string& personName, unsigned int insuranceId)
{
	this->personName = personName;
	this->insuranceId = insuranceId;
}

unsigned int Person::getInsuranceId() const
{
	return insuranceId;
}
