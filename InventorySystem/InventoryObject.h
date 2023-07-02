#pragma once
#include <string>

#include "Enumerations.h"

using namespace std;

class InventoryObject
{
//Methods
public:
	InventoryObject(); 
	
	// TODO : Remi : Check if removable
	//InventoryObject(
	//	E_itemType type,
	//	string name,
	//	unsigned short int cost,
	//	unsigned short int stacks = 1,
	//	unsigned short int currentDurability = 0,
	//	unsigned short int maxDurability = 0,
	//	E_equimentSlots slot = E_equimentSlots::Count);// ,
	////bool isEmpty = true);

	virtual void DeleteAttributes();
	virtual string* GetName() { return m_name; }
	virtual size_t GetNameLenght() const { return m_name->length(); }
	virtual E_itemType* GetType() { return m_type; }
	virtual E_equimentSlots* GetEquipmentSlot() { return m_equipmentSlot; }
	virtual unsigned short int* GetCost() { return m_cost; }
	virtual unsigned short int* GetStackSize() { return m_stackSize; }
	virtual void SetStackSize(unsigned short int* new_size) { m_stackSize = new_size; }
	virtual unsigned short int* GetCurrentDurability() { return m_currentDurability; }
	virtual unsigned short int* GetMaxDurability() { return m_maxDurability; }
	virtual unsigned short int GetMaxStackSize() { return MAX_STACK; }
	virtual const bool IsStackable() { return IS_STACKABLE; }
	virtual bool HasMultipleStacks() { return m_hasMultipleStacks; }
	virtual void SetMultupleStacks(bool hasMultipleStacks) { m_hasMultipleStacks = hasMultipleStacks; }

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
	const bool IS_STACKABLE = false;
	bool m_hasMultipleStacks = false;
};