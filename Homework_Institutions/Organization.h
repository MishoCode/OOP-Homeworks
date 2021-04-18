#pragma once
#include"Institution.h"
#include<vector>
class Organization : public Institution
{
public:
	bool hasMember(const Person& person) const override;
	Payer* payer() const override;
	bool valid()const  override;
	void setType() override;
	InstitutionType getType()const override;
	unsigned int getClients(const std::vector<Person>& clients)const override;
	void addInstitution(Institution* institution, bool forceAdding = false);
	Institution* clone() override;
	std::string getInstitutionId() const override;
	std::vector<Institution*> getInstitutionList()const;
	
	Organization(const std::vector<Institution*>& institutionList, const std::string& organizationAddress);
private:
	std::vector<Institution*> institutionList;
	std::string organizationAddress;
};

