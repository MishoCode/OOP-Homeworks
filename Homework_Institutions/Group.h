#pragma once
#include"Institution.h"
class Group : public Institution
{
public:
	bool hasMember(const Person& person)const  override;
	Payer* payer()const  override;
	bool valid() const override;
	void setType() override;
	InstitutionType getType()const override;
	unsigned int getClients(const std::vector<Person>& clients)const override;
	Institution* clone() override;
	std::string getInstitutionId() const override;

	Group(unsigned int groupId);
	void setPayer(Payer* groupPayer);

private:
	unsigned int groupId;
	Payer* groupPayer;
};

