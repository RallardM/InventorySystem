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
		bool equipped = false,
		E_itemType type = E_itemType::Equipment,
		unsigned short int currentDurability = 0,
		unsigned short int maxDurability = 0,
		E_equimentSlots slot = E_equimentSlots::Count);

	void DeleteAttributes();
	string* GetName() const override { return m_name; }
	size_t GetNameLenght() const override { return m_name->length(); }
	E_itemType* GetType() const override { return m_type; }
	E_equimentSlots* GetEquipmentSlot() const override { return m_equipmentSlot; }
	unsigned short int* GetCost() const override { return m_cost; }
	unsigned short int* GetCurrentDurability() const override { return m_currentDurability; }
	unsigned short int* GetMaxDurability() const override { return m_maxDurability; }
	const bool IsStackable() const override { return IS_STACKABLE; }
	bool IsEquiped() const override { return m_isEquipped; }
	void SetIsEquiped(bool isEquiped) override { m_isEquipped = isEquiped; }
	unsigned short int* GetId() const { return m_id; }
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
	bool m_isEquipped = false;
	const bool IS_STACKABLE = false;
};