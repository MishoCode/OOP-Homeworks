#include "Payer.h"

//unsigned int Payer::groupsCount = 0;

Payer::Payer()
	:targetGroupId(0), groupsCount(0)
{
}

Payer::Payer(const std::string& payerName, std::function<bool(unsigned int, unsigned int)> payerMemberRule,
	unsigned int targetGroupId)
	:groupsCount(0)
{
	this->payerName = payerName;
	this->payerMemberRule = payerMemberRule;
	this->targetGroupId = targetGroupId;
}

unsigned int Payer::getTargetGroupId() const
{
	return targetGroupId;
}

std::function<bool(unsigned int, unsigned int)> Payer::getPayerMemeberRule() const
{
	return payerMemberRule;
}

unsigned int Payer::associatedGroups() const
{
	if(this != nullptr)
		return groupsCount;
	return 0;
}

void Payer::incrementPayerGroupsCount()
{
	groupsCount++;
}

std::string Payer::getName() const
{
	return payerName;
}
