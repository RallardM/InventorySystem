#include <iostream>
#include "InventoryObject.h"

using namespace std;

InventoryObject::InventoryObject(
	string type,
	string name,
	unsigned short int cost,
	unsigned short int stacks/* = 1 */,
	unsigned short int currentDurability/* = 0 */,
	unsigned short int maxDurability/* = 0 */,
	E_equimentSlots slot/* = E_equimentSlots::COUNT */)//,
	//bool isEmpty /* = true */)
{
	cout << "InventoryObject constructor called!" << endl;
	m_type = new string(type);
	m_name = new string(name);
	m_cost = new unsigned short int(cost);
	m_stackSize = new unsigned short int(stacks);
	m_currentDurability = new unsigned short int(currentDurability);
	m_maxDurability = new unsigned short int(maxDurability);
	m_equipmentSlot = new E_equimentSlots(slot);
	//m_isEmpty = new bool(isEmpty);
}

string InventoryObject::ToString()
{
	string returnValue = "";
	returnValue += "\nItem name: " + *m_name + "\nItem cost: " + to_string(*m_cost);

	return returnValue;
}

void InventoryObject::DeleteAttributes()
{
	cout << "InventoryObject destructor called!" << endl;
	delete m_name;
	delete m_type;
	delete m_equipmentSlot;
	delete m_cost;
	delete m_stackSize;
	delete m_currentDurability;
	delete m_maxDurability;
}