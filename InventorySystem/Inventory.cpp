#include "Inventory.h"
#include <iostream>

void Inventory::AddItem(string& itemType, string& itemName, E_equimentSlots equipmentSlot/* = E_equimentSlots::COUNT */, unsigned short int itemCost/* = 0 */, unsigned short int currentDurability/* = 0 */, unsigned short int maxDurability /* = 0 */)
{
	//string* itemTypePtr = new string(itemType);
	//string* itemNamePtr = new string(itemName);
	//E_equimentSlots* equipmentSlotPtr = new E_equimentSlots(equipmentSlot);
	//unsigned short int* itemCostPtr = new unsigned short int(itemCost);
	//unsigned short int* currentDurabilityPtr = new unsigned short int(currentDurability);
	//unsigned short int* maxDurabilityPtr = new unsigned short int(maxDurability);

	InventoryObject* newObject = new InventoryObject(itemType, itemName, itemCost, currentDurability, maxDurability, equipmentSlot);
	m_inventoryObjectsList.push_back(newObject);

	if (m_inventoryObjectsList.size() == 1)
	{
		m_currentItem = m_inventoryObjectsList.front();
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

void Inventory::DestroyAllInventoryObjects() // TODO : Delete objects of objects before deleting the objects
{
	for (InventoryObject* object : m_inventoryObjectsList)
	{
		delete object;
	}
	m_inventoryObjectsList.clear();
}