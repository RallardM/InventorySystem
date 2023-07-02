#include <iostream>

#include "BaseObject.h"

using namespace std;

BaseObject::BaseObject(
	string name,
	unsigned short int cost,
	E_itemType type /* = E_itemType::BaseObject */)
{
	cout << "BaseObject constructor called!" << endl;
	m_type = new E_itemType(type);
	m_name = new string(name);
	m_cost = new unsigned short int(cost);
	InstantiateId();
}

void BaseObject::DeleteAttributes()
{
	cout << "BaseObject DeleteAttributes called!" << endl;
	delete m_name;
	delete m_type;
	delete m_cost;
}

void BaseObject::InstantiateId()
{
	m_id = GetNextId();
	SetNextId(GetNextId() + 1);
}
