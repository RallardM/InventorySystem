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
	void AddItem(E_itemType itemType, string itemName, unsigned short int itemCost = 0, unsigned short int itemStacks = 1, unsigned short int currentDurability = 0, unsigned short int maxDurability = 0, E_equimentSlots equipmentSlot = E_equimentSlots::Count);
	void UpdateIterator();
	void RemoveItem();
	void AddBasicObject();
	void AddConsumable();
	void AddEquipment();
	void DisplayCurrentMenu();
	bool IsCurrentSelectionPrinted();
	void DisplayNavigationMenu();
	void DisplayEditionMenu();
	void DisplayCurrentObject();
	void DisplayStackSize();
	void DestroyAllInventoryObjects();
	string GetEnumString(E_equimentSlots* equipmentSlot);
	void ChangeStackSize(bool isIncreasing);
	E_inputMode GetCurrentInputMode();
	E_equimentSlots GetCurrentEquipmentSlot();
	void SetCurrentInputMode(E_equimentSlots currentEquipmentSlot);
	void SetCurrentInputMode(E_inputMode currentInputMode);
	void ClearConsolePreviousLine();
	void MoveCursorToLocation(COORD position);
	bool IsInventoryEmpty();
	void ClearInventoryList();
	void CleanIfLogMessagePrinted();
	// TODO : Remi : Move and test functions to private

private:
	//void CheckIfStackable();

//Member variables
public:
	// Source : https://stackoverflow.com/questions/19762755/creating-a-list-in-c-with-initial-capacity
	list<InventoryObject*> m_inventoryObjectsList;// = list<InventoryObject*>{ MAX_INVENTORY_OBJECTS };
	list<InventoryObject*>::iterator m_inventoryPtrIterator;

	//In order to have a string pointer it can only be a const char* with "".
	const char* FILE_PATH = "saved_files/InventorySaveFile.txt";

private:
	//InventoryObject* m_currentItem = nullptr;
	const char* UNIFORM_TAB = "    "; // "\t" is not working properly. It is not tabulating the same way for every string.
	const char* ENTER_NAME = "Enter item name: ";
	const char* ENTER_COST = "Enter item cost: ";
	const char* SELECTED_OBJECT = "Selected objec: ";
	const char* STACK_SIZE = "Stack size: ";
	const char* QUIT = "Q. Quit";

	//const unsigned short int MAX_INVENTORY_OBJECTS = 20;
	E_equimentSlots m_currentEquipmentSlot = E_equimentSlots::Head;
	E_inputMode m_currentInputMode = E_inputMode::Navigation;
	bool m_isLogMessagePrinted = false;
};