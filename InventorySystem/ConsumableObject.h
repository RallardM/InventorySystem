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
	string* GetName() const { return m_name; }
	size_t GetNameLenght() const { return m_name->length(); }
	E_itemType* GetType() const { return m_type; }
	unsigned short int* GetCost() const { return m_cost; }
	unsigned short int* GetStackSize() const // TODO : Remi : collapse after debug
	{
		return m_stackSize; 
	}
	void SetStackSize(unsigned short int new_size) // TODO : Remi : collapse after debug
	{ 
		*m_stackSize = new_size;
	}
	unsigned short int GetMaxStackSize() const { return MAX_CONSUMABLE_STACKS; }
	const bool IsStackable() const { return IS_STACKABLE; }
	bool HasMultipleStacks() const { return m_hasMultipleStacks; }
	void SetMultupleStacks(bool hasMultipleStacks) { m_hasMultipleStacks = hasMultipleStacks; }
	unsigned short int* GetId() { return m_id; }
	void InstantiateId();

private:

//Member variables
public:

private:
	string* m_name;
	E_itemType* m_type;
	unsigned short int* m_id;
	unsigned short int* m_cost;
	unsigned short int* m_stackSize;
	static const unsigned short int MAX_CONSUMABLE_STACKS;
	const bool IS_STACKABLE = true;
	bool m_hasMultipleStacks = false;
};