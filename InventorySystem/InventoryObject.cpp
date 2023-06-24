#include "InventoryObject.h"

InventoryObject::InventoryObject(
	string type,
	string name,
	unsigned short int cost,
	unsigned short int currentDurability,
	unsigned short int maxDurability,
	E_equimentSlots slot
	/*currentDurability = 0,
	maxDurability = 0,
	slot = E_equimentSlots::COUNT */)
{
	m_type = type;
	m_name = name;
	m_cost = cost;
	m_currentDurability = currentDurability;
	m_maxDurability = maxDurability;
	m_equipmentSlot = slot;
}

string InventoryObject::ToString()
{
	string returnValue = "";
	returnValue += "\nItem name: " + m_name + "\nItem cost: " + to_string(m_cost);

	return returnValue;
}
