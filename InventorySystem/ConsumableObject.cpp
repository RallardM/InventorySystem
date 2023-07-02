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
	unsigned short int maxDurability/* = 0 */,
	E_equimentSlots slot/* = E_equimentSlots::COUNT */)
{
	cout << "InventoryObject constructor called!" << endl;
	m_type = new E_itemType(type);
	m_name = new string(name);
	m_cost = new unsigned short int(cost);
	m_stackSize = new unsigned short int(stacks);
	m_currentDurability = new unsigned short int(currentDurability);
	m_maxDurability = new unsigned short int(maxDurability);
	m_equipmentSlot = new E_equimentSlots(slot);
	//m_isEmpty = new bool(isEmpty);
}