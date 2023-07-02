#pragma once
#include "InventoryObject.h"

// This is a placeholder until Paulo implements the Consumable class

class ConsumableObject :
    public InventoryObject
{
//Methods
public:
	ConsumableObject(
		string name,
		unsigned short int cost,
		E_itemType type = E_itemType::Consumable,
		unsigned short int stacks = 1,
		unsigned short int currentDurability = 0,
		unsigned short int maxDurability = 0,
		E_equimentSlots slot = E_equimentSlots::Count);

	unsigned short int GetMaxStackSize() { return MAX_CONSUMABLE_STACKS; }

private:

//Member variables
public:

private:
	string* m_name;
	E_itemType* m_type;
	E_equimentSlots* m_equipmentSlot;
	unsigned short int* m_cost;
	unsigned short int* m_stackSize;
	unsigned short int* m_currentDurability;
	unsigned short int* m_maxDurability;
	static const unsigned short int MAX_CONSUMABLE_STACKS;
};