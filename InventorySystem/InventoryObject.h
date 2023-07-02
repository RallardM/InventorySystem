#pragma once
#include <string>

#include "Enumerations.h"

using namespace std;

class InventoryObject
{
//Methods
public:
	InventoryObject();
	InventoryObject(
		E_itemType type,
		string name,
		unsigned short int cost,
		unsigned short int stacks = 1,
		unsigned short int currentDurability = 0,
		unsigned short int maxDurability = 0,
		E_equimentSlots slot = E_equimentSlots::Count);// ,
	//bool isEmpty = true);

	string ToString();
	void DeleteAttributes();
	string* GetName() { return m_name; }
	size_t GetNameLenght() const { return m_name->length(); }
	E_itemType* GetType() { return m_type; }
	E_equimentSlots* GetEquipmentSlot() { return m_equipmentSlot; }
	unsigned short int* GetCost() { return m_cost; }
	unsigned short int* GetStackSize() { return m_stackSize; }
	unsigned short int* GetCurrentDurability() { return m_currentDurability; }
	unsigned short int* GetMaxDurability() { return m_maxDurability; }
	virtual unsigned short int GetMaxStackSize() { return MAX_STACK; }
	//bool* IsEmpty() { return m_isEmpty; }

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
	static const unsigned short int MAX_STACK;
	//bool* m_isEmpty;
};