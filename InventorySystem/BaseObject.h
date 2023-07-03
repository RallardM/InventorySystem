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
	string* GetName() const override { return m_name; }
	size_t GetNameLenght() const override { return m_name->length(); }
	E_itemType* GetType() const override { return m_type; }
	unsigned short int* GetCost() const override { return m_cost; }
	const bool IsStackable() const override { return IS_STACKABLE; }
	unsigned short int* GetId() const { return m_id; }
	void InstantiateId();

private:

	//Member variables
public:

private:
	string* m_name;
	E_itemType* m_type;
	unsigned short int* m_cost;
	unsigned short int* m_id;
	const bool IS_STACKABLE = false;
};