#include "InventoryObject.h"

InventoryObject::InventoryObject(
	string type,
	string name,
	unsigned short int cost,
	unsigned short int currentDurability,
	unsigned short int maxDurability,
	E_equimentSlots slot)
{
	m_type = type;
	m_name = name;
	m_cost = cost;
}

string InventoryObject::ToString()
{
	string returnValue = "";
	returnValue += "\nItem name: " + m_name + "\nItem cost: " + to_string(m_cost);

	return returnValue;
}
