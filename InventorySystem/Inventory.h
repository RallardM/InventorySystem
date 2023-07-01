#pragma once
#include <list>
#include <iterator>
#include <windows.h>

#include "InventoryObject.h"
#include "Enumerations.h"

class Inventory
{
//Methods
public:
	Inventory();
	void AddItem(string itemType, string itemName, unsigned short int itemCost = 0, unsigned short int itemStacks = 1, unsigned short int currentDurability = 0, unsigned short int maxDurability = 0, E_equimentSlots equipmentSlot = E_equimentSlots::Count);//, bool isPopulated = false);
	void AddBasicObject();
	void AddConsumable();
	void AddEquipment();
	void DisplaySelectedItem();
	void DisplayCurrentMenu();
	void DisplayCurrentSelection();
	bool IsCurrentSelectionPrinted();
	void DisplayNavigationMenu();
	void DisplayEditionMenu();
	void DisplayCurrentObject();
	void DestroyAllInventoryObjects();
	string GetEnumString(E_equimentSlots* equipmentSlot);
	E_inputMode GetCurrentInputMode();
	E_equimentSlots GetCurrentEquipmentSlot();
	void SetCurrentInputMode(E_equimentSlots currentEquipmentSlot);
	void SetCurrentInputMode(E_inputMode currentInputMode);
	void ClearConsolePreviousLine();
	void MoveCursorToLocation(COORD position);
	bool IsInventoryEmpty();
	void ClearInventoryList();

private:

//Member variables
public:
	// Source : https://stackoverflow.com/questions/19762755/creating-a-list-in-c-with-initial-capacity
	list<InventoryObject*> m_inventoryObjectsList = list<InventoryObject*>{ MAX_INVENTORY_OBJECTS };
	list<InventoryObject*>::iterator m_inventoryPtrIterator;

	//In order to have a string pointer it can only be a const char* with "".
	const char* FILE_PATH = "saved_files/InventorySaveFile.txt";

private:
	//InventoryObject* m_currentItem = nullptr;
	const unsigned short int MAX_INVENTORY_OBJECTS = 20;
	E_equimentSlots m_currentEquipmentSlot = E_equimentSlots::Head;
	E_inputMode m_currentInputMode = E_inputMode::Navigation;
};