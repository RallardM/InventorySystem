#pragma once
#include <list>

#include "InventoryObject.h"
#include "Enumerations.h"

using namespace std;

class Inventory
{
//Methods
public:
	void AddItem(string& itemType, string& itemName, unsigned short int itemCost = 0, unsigned short int itemStacks = 1, unsigned short int currentDurability = 0, unsigned short int maxDurability = 0, E_equimentSlots equipmentSlot = E_equimentSlots::Count);
	void AddBasicObject();
	void AddConsumable();
	void AddEquipment();
	void NavigateEquipmentSlots();
	void DisplaySelectedItem();
	void DisplaySelectedInventory();
	void DisplayCurrentMenu();
	void DisplayCurrentSelection();
	bool IsCurrentSelectionPrinted();
	void DisplayLoadingMenu();
	void DisplayNavigationMenu();
	void DisplayEditionMenu();
	void DestroyAllInventoryObjects();
	string GetEnumString(E_equimentSlots equipmentSlot);
	E_inputMode GetCurrentInputMode();
	void SetCurrentInputMode(E_inputMode currentInputMode);
	void ClearConsolePreviousLine();

private:

//Member variables
public:
	// Source : https://stackoverflow.com/questions/19762755/creating-a-list-in-c-with-initial-capacity
	list<InventoryObject*> m_inventoryObjectsList = list<InventoryObject*>{ MAX_INVENTORY_OBJECTS };

	//In order to have a string pointer it can only be a const char* with "".
	const char* FILES_PATH = "saved_files/";
	const char* LOAD_FILE_PATH = "saved_files/InventorySaveFile.txt";

private:
	InventoryObject* m_currentItem = nullptr;
	const unsigned short int MAX_INVENTORY_OBJECTS = 20;
	E_equimentSlots m_currentEquipmentSlot = E_equimentSlots::Head;
	E_inputMode m_currentInputMode = E_inputMode::Loading;
};