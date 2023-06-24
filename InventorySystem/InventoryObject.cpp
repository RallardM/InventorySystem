#include "InventoryObject.h"

InventoryObject::InventoryObject(
	string& type,
	string& name,
	unsigned short int& cost,
	unsigned short int currentDurability/* = 0 */,
	unsigned short int maxDurability/* = 0 */,
	E_equimentSlots slot/* = E_equimentSlots::COUNT */)
{
	m_type = new string(type);
	m_name = new string(name);
	m_cost = new unsigned short int(cost);
	m_currentDurability = new unsigned short int(currentDurability);
	m_maxDurability = new unsigned short int(maxDurability);
	m_equipmentSlot = new E_equimentSlots(slot);
}

string InventoryObject::ToString()
{
	string returnValue = "";
	returnValue += "\nItem name: " + *m_name + "\nItem cost: " + to_string(*m_cost);

	return returnValue;
}