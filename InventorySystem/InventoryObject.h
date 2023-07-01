#pragma once
#include <string>

#include "Enumerations.h"

using namespace std;

class InventoryObject
{
	//Methods
public:
	InventoryObject(
	string& type, 
	string& name, 
	unsigned short int& cost, 
	unsigned short int stacks = 1, 
	unsigned short int currentDurability = 0, 
	unsigned short int maxDurability = 0, 
	E_equimentSlots slot = E_equimentSlots::Count);

	string ToString();
	void DeleteAttributes();
	string* GetName() { return m_name; }
	string* GetType() { return m_type; }
	E_equimentSlots* GetEquipmentSlot() { return m_equipmentSlot; }
	unsigned short int* GetCost() { return m_cost; }
	unsigned short int* GetStackSize() { return m_stackSize; }
	unsigned short int* GetCurrentDurability() { return m_currentDurability; }
	unsigned short int* GetMaxDurability() { return m_maxDurability; }

private:
	//Member variables
public:


private:
	string* m_name;
	string* m_type;
	E_equimentSlots* m_equipmentSlot;
	unsigned short int* m_cost;
	unsigned short int* m_stackSize;
	unsigned short int* m_currentDurability;
	unsigned short int* m_maxDurability;
};