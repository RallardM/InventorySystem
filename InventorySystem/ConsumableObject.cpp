#include <iostream>

#include "ConsumableObject.h"

using namespace std;

const unsigned short int ConsumableObject::MAX_CONSUMABLE_STACKS = 20;

ConsumableObject::ConsumableObject(
	string name,
	unsigned short int cost,
	E_itemType type /* = E_itemType::Consumable */,
	unsigned short int stacks/* = 1 */,
	unsigned short int currentDurability/* = 0 */,
	unsigned short int maxDurability/* = 0 */)
{
	cout << "ConsumableObject constructor called!" << endl;
	m_type = new E_itemType(type);
	m_name = new string(name);
	m_cost = new unsigned short int(cost);
	m_stackSize = new unsigned short int(stacks);
}

void ConsumableObject::DeleteAttributes()
{
	cout << "ConsumableObject DeleteAttributes called!" << endl;
	delete m_name;
	delete m_type;
	delete m_cost;
	delete m_stackSize;
}
