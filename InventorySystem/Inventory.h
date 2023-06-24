#pragma once
#include <list>

#include "InventoryObject.h"
#include "Enumerations.h"

using namespace std;

class Inventory
{
//Methods
public:
	void AddItem(string& itemType, string& itemName, E_equimentSlots equipmentSlot = E_equimentSlots::COUNT, unsigned short int itemCost = 0, unsigned short int currentDurability = 0, unsigned short int maxDurability = 0);
	void DisplaySelectedItem();
	void DestroyAllInventoryObjects();
private:

//Member variables
public:
	list<InventoryObject*> m_inventoryObjectsList;
private:
	InventoryObject* m_currentItem = NULL;
};