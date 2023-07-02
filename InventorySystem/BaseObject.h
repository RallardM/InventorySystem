#pragma once
#include "InventoryObject.h"

class BaseObject :
    public InventoryObject
{
	//Methods
public:
	BaseObject(
		string name,
		unsigned short int cost,
		E_itemType type = E_itemType::BaseObject);

	void DeleteAttributes();
	string* GetName() { return m_name; }
	size_t GetNameLenght() const { return m_name->length(); }
	E_itemType* GetType() { return m_type; }
	unsigned short int* GetCost() { return m_cost; }
	const bool IsStackable() { return IS_STACKABLE; }

private:

	//Member variables
public:

private:
	string* m_name;
	E_itemType* m_type;
	unsigned short int* m_cost;
	const bool IS_STACKABLE = false;
};

