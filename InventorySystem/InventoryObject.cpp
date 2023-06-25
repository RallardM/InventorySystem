#include "InventoryObject.h"

InventoryObject::InventoryObject(
	string& type,
	string& name,
	unsigned short int& cost,
	unsigned short int stacks/* = 1 */,
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

void InventoryObject::DeleteAttributes()
{
	delete m_name;
	delete m_type;
	delete m_equipmentSlot;
	delete m_cost;
	delete m_stackSize;
	delete m_currentDurability;
	delete m_maxDurability;
}