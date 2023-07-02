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
		bool hasStack = false);

	void DeleteAttributes();
	string* GetName() { return m_name; }
	size_t GetNameLenght() const { return m_name->length(); }
	E_itemType* GetType() { return m_type; }
	unsigned short int* GetCost() { return m_cost; }
	unsigned short int* GetStackSize() { return m_stackSize; }
	void SetStackSize(unsigned short int* new_size) { m_stackSize = new_size; }
	unsigned short int GetMaxStackSize() { return MAX_CONSUMABLE_STACKS; }
	const bool IsStackable() { return IS_STACKABLE; }
	bool HasMultipleStacks() { return m_hasMultipleStacks; }
	void SetMultupleStacks(bool hasMultipleStacks) { m_hasMultipleStacks = hasMultipleStacks; }

private:

//Member variables
public:

private:
	string* m_name;
	E_itemType* m_type;;
	unsigned short int* m_cost;
	unsigned short int* m_stackSize;
	static const unsigned short int MAX_CONSUMABLE_STACKS;
	const bool IS_STACKABLE = true;
	bool m_hasMultipleStacks = false;
};