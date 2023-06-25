#pragma once
#include <list>

#include "InventoryObject.h"
#include "Enumerations.h"

using namespace std;

class Inventory
{
//Methods
public:
	void AddItem(string& itemType, string& itemName, E_equimentSlots equipmentSlot = E_equimentSlots::Count, unsigned short int itemCost = 0, unsigned short int itemStacks = 1, unsigned short int currentDurability = 0, unsigned short int maxDurability = 0);
	void DisplaySelectedItem();
	void DestroyAllInventoryObjects();

private:

//Member variables
public:
	// Source : https://stackoverflow.com/questions/19762755/creating-a-list-in-c-with-initial-capacity
	list<InventoryObject*> m_inventoryObjectsList = list<InventoryObject*>{ MAX_INVENTORY_OBJECTS };
private:
	InventoryObject* m_currentItem = NULL;
	const unsigned short int MAX_INVENTORY_OBJECTS = 20;
};