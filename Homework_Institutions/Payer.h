#pragma once
#include<string>
#include<functional>

class Payer
{
public:
	Payer();
	Payer(const std::string& payerName, std::function<bool(unsigned int, unsigned int)> payerMemberRule,
		unsigned int targetGroupId);
	unsigned int getTargetGroupId()const;
	std::function<bool(unsigned int, unsigned int)> getPayerMemeberRule()const;
	unsigned int associatedGroups()const;
	void incrementPayerGroupsCount();
	std::string getName()const;
private:
	std::string payerName;
	std::function<bool(unsigned int, unsigned int)> payerMemberRule;
	unsigned int targetGroupId;
	unsigned int groupsCount;
};

