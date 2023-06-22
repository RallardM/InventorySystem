#include "InventoryObject.h"

InventoryObject::InventoryObject(string name, int cost)
{
	m_name = name;
	m_cost = cost;
}

string InventoryObject::ToString()
{
	string returnValue = "";
	returnValue += "\nItem name: " + m_name + "\nItem cost: " + to_string(m_cost);

	return returnValue;
}