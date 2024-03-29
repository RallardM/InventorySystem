#include <iostream>

#include "ConsumableObject.h"

using namespace std;

const unsigned short int ConsumableObject::MAX_CONSUMABLE_STACKS = 20;

ConsumableObject::ConsumableObject(
	string name,
	unsigned short int cost,
	E_itemType type /* = E_itemType::Consumable */,
	unsigned short int stacks/* = 1 */,
	bool hasStack /* = false */)
{
	cout << endl << "ConsumableObject constructor called!";
	m_type = new E_itemType(type);
	m_name = new string(name);
	m_cost = new unsigned short int(cost);
	m_stackSize = new unsigned short int(stacks);
	InstantiateId();
}

void ConsumableObject::DeleteAttributes()
{
	cout << endl << "ConsumableObject DeleteAttributes called!";
	delete m_name;
	delete m_type;
	delete m_cost;
	delete m_stackSize;
}

void ConsumableObject::InstantiateId()
{
	m_id = GetNextId();
	SetNextId(GetNextId() + 1);
}
