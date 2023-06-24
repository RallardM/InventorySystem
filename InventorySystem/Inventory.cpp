#include "Inventory.h"
#include <iostream>

void Inventory::AddItem(string itemType, string itemName, int itemCost /* = 0 */)
{
	m_inventoryObjectsList.push_back(InventoryObject(itemType, itemName, itemCost));
	if (m_inventoryObjectsList.size() == 1)
	{
		m_currentItem = &m_inventoryObjectsList.front();
	}
}

void Inventory::DisplaySelectedItem()
{
	system("CLS");
	if (!m_currentItem)
	{
		cout << endl << "There is no item in this inventory!";
		return;
	}
	cout << endl << "Current item: " << endl << m_currentItem->ToString();
}