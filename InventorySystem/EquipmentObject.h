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
	string* GetName() const { return m_name; }
	size_t GetNameLenght() const { return m_name->length(); }
	E_itemType* GetType() const { return m_type; }
	E_equimentSlots* GetEquipmentSlot() const { return m_equipmentSlot; }
	unsigned short int* GetCost() const { return m_cost; }
	unsigned short int* GetCurrentDurability() const { return m_currentDurability; }
	unsigned short int* GetMaxDurability() const { return m_maxDurability; }
	const bool IsStackable() const { return IS_STACKABLE; }
	unsigned short int* GetId() { return m_id; }
	void InstantiateId();

private:

//Member variables
public:

private:
	string* m_name;
	E_itemType* m_type;
	E_equimentSlots* m_equipmentSlot;
	unsigned short int* m_id;
	unsigned short int* m_cost;
	unsigned short int* m_currentDurability;
	unsigned short int* m_maxDurability;
	const bool IS_STACKABLE = false;
};

