#pragma once
#include <string>

#include "Enumerations.h"

using namespace std;

class InventoryObject
{
//Methods
public:
	virtual void DeleteAttributes() {};
	virtual string* GetName() const { return nullptr; }
	virtual size_t GetNameLenght() const { return NULL; }
	virtual E_itemType* GetType() const { return nullptr; }
	virtual E_equimentSlots* GetEquipmentSlot() const { return nullptr; }
	virtual unsigned short int* GetCost() const { return nullptr; }
	virtual unsigned short int* GetStackSize() const { return nullptr; }
	virtual void SetStackSize(unsigned short int new_size) // TODO : Remi : Collapse after debug
	{  
		return;
	}
	virtual unsigned short int* GetCurrentDurability() const { return nullptr; }
	virtual unsigned short int* GetMaxDurability() const { return nullptr; }
	virtual unsigned short int GetMaxStackSize() const { return NULL; }
	virtual const bool IsStackable() const { return NULL; }
	virtual bool HasMultipleStacks() const { return NULL; }
	virtual void SetMultupleStacks(bool hasMultipleStacks) {  }
	virtual unsigned short int* GetId() { return NULL; }
	virtual void InstantiateId() {};
	
protected:

	static unsigned short int* GetNextId() { return s_nextId; }
	static void SetNextId(unsigned short int* new_id) { s_nextId = new_id; }

private:
	

//Member variables
public:

private:

protected:
	static unsigned short int* s_nextId;
	
};