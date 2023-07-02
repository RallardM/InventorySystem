#pragma once
#include "InventoryObject.h"

class EquipmentObject :
    public InventoryObject
{
//Methods
public:
	EquipmentObject(
		string name,
		unsigned short int cost,
		E_itemType type = E_itemType::Equipment,
		unsigned short int currentDurability = 0,
		unsigned short int maxDurability = 0,
		E_equimentSlots slot = E_equimentSlots::Count);

	void DeleteAttributes();
	string* GetName() { return m_name; }
	size_t GetNameLenght() const { return m_name->length(); }
	E_itemType* GetType() { return m_type; }
	E_equimentSlots* GetEquipmentSlot() { return m_equipmentSlot; }
	unsigned short int* GetCost() { return m_cost; }
	unsigned short int* GetCurrentDurability() { return m_currentDurability; }
	unsigned short int* GetMaxDurability() { return m_maxDurability; }
	const bool IsStackable() { return IS_STACKABLE; }

private:

//Member variables
public:

private:
	string* m_name;
	E_itemType* m_type;
	E_equimentSlots* m_equipmentSlot;
	unsigned short int* m_cost;
	unsigned short int* m_currentDurability;
	unsigned short int* m_maxDurability;
	const bool IS_STACKABLE = false;
};

