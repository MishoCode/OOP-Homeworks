#pragma once
#include<string>

class Person
{
public:
	Person(const std::string& personName, unsigned int insuranceId);
	unsigned int getInsuranceId()const;
private:
	std::string personName;
	unsigned int insuranceId;
};

