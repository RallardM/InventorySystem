#pragma once
#include "InventoryObject.h"
#include <list>

using namespace std;

class Inventory
{
//Methods
public:
	void AddItem(string itemType, string itemName, int itemCost = 0);
	void DisplaySelectedItem();
private:

//Member variables
public:
	list<InventoryObject> m_inventoryObjectsList;
private:
	InventoryObject* m_currentItem = NULL;
};