#include <iostream>

#include "EquipmentObject.h"

using namespace std;

const unsigned short int EquipmentObject::MAX_EQUIPMENT_OBJECT_STACKS = 1;

EquipmentObject::EquipmentObject(
	string name,
	unsigned short int cost,
	E_itemType type /* = E_itemType::Equipment */,
	unsigned short int stacks/* = 1 */,
	unsigned short int currentDurability/* = 0 */,
	unsigned short int maxDurability/* = 0 */,
	E_equimentSlots slot/* = E_equimentSlots::COUNT */)
{
	cout << "EquipmentObject constructor called!" << endl;
	m_type = new E_itemType(type);
	m_name = new string(name);
	m_cost = new unsigned short int(cost);
	m_stackSize = new unsigned short int(stacks);
	m_currentDurability = new unsigned short int(currentDurability);
	m_maxDurability = new unsigned short int(maxDurability);
	m_equipmentSlot = new E_equimentSlots(slot);
}

void EquipmentObject::DeleteAttributes()
{
	cout << "EquipmentObject DeleteAttributes called!" << endl;
	delete m_name;
	delete m_type;
	delete m_equipmentSlot;
	delete m_cost;
	delete m_stackSize;
	delete m_currentDurability;
	delete m_maxDurability;
}
