#include<iostream>
#include<map>
#include<vector>
#include"Payer.h"
#include"Group.h"
#include"Organization.h"

Institution* findMostPopular(const std::vector<Institution*>& institutions, const std::vector<Person>& clients)
{
	if (institutions.empty() || clients.empty())
		return nullptr;

	std::map<Institution*,unsigned int> counter;
	for (auto i : institutions)
	{
		unsigned int currentCount = i->getClients(clients);
		counter.insert({ i,currentCount });
	}

	std::pair<Institution*, unsigned int> mostPopular = { nullptr,0 };
	for (auto i : counter)
	{
		if (i.second > mostPopular.second)
			mostPopular = i;
	}

	return mostPopular.first;
}
std::vector<Institution*> clearInstitutions(const std::vector<Institution*>& institutions)
{
	std::vector<Institution*> result;
	for (auto i : institutions)
	{
		if (i->valid())
		{
			result.push_back(i);
		}
	}
	return result;
}

int main()
{	
	Payer p1("payer1", [](unsigned int personId, unsigned int groupId) { return personId % 100 == groupId % 100; }, 7878);
	Payer p2("payer2", [](unsigned int personId, unsigned int groupId) {return personId + groupId < 100; }, 45);

	Person person1("person1", 78);
	Person person2("person2", 45);
	Person person3("person3", 778);
	Person person4("person4", 578);

	Group g1(7878);
	g1.setPayer(&p1);
	
	Group g2(45);
	
	Group g3(45);
	g3.setPayer(&p2);

	Group g4(7878);

	//g1 -> person1 ,person3, person4
	//g3 -> person2

	std::vector<Institution*> list1;
	list1.push_back(&g1);
	list1.push_back(&g3);
	
	Organization o1(list1, "address1");
	//o1.addInstitution(&g4); //invalid institution, g4 has no associated payer
	o1.addInstitution(&g4, true);// force the adding
	std::cout << o1.getInstitutionList().size() << std::endl;//3 -> g1, g3, g4
	std::vector<Institution*> cleared = clearInstitutions(o1.getInstitutionList());
	std::cout << cleared.size() << std::endl; // 2 -> g1, g3

	std::vector<Institution*> list2;
	Organization o2(list2, "address2");

	std::vector<Institution*> list;
	list.push_back(&o1);
	list.push_back(&o2);
	list.push_back(&g1);
	list.push_back(&g3);

	std::vector<Person> clients;
	clients.push_back(person1);
	clients.push_back(person2);
	clients.push_back(person3);
	clients.push_back(person4);

	std::cout << findMostPopular(list, clients)->getInstitutionId()<< std::endl;//6_address1
	//6 ->this is the number of all institutions created up to now
	//address1 -> this is the address of the current institution(in our case this is the most famous institution)

	std::cout << clearInstitutions(list).size() << std::endl;//3 -> o1, g1, g3

	return 0;
}