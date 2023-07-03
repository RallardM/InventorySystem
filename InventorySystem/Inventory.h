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
	void AddItem(
		E_itemType itemType, 
		string itemName, 
		unsigned short int itemCost = 0, 
		unsigned short int itemStacks = 1, 
		unsigned short int currentDurability = 0, 
		unsigned short int maxDurability = 0, 
		E_equimentSlots equipmentSlot = E_equimentSlots::Count,
		bool hasStack = false);

	void UpdateIterator();
	void RemoveItem();

	void AddBasicObject();
	void AddConsumable();
	void AddEquipment();

	void DisplayCurrentMenu();
	void DisplayNavigationMenu();
	void DisplayEditionMenu();
	void DisplayCurrentObject();
	void DisplayInventory();

	void MoveCursorToLocation(COORD position);
	void DestroyAllInventoryObjects();
	void ChangeStackSize(bool isIncreasing);

	void SetStackSizeFromObjectId();

	COORD GetConsoleCursorPosition();
	E_inputMode GetCurrentInputMode();
	E_equimentSlots GetCurrentEquipmentSlot();
	string GetEnumString(E_equimentSlots* equipmentSlot);

	void SetCurrentInputMode(E_equimentSlots currentEquipmentSlot);
	void SetCurrentInputMode(E_inputMode currentInputMode);

	void CleanIfLogMessagePrinted();
	void ClearConsolePreviousLine();
	void ClearInventoryList();
	void CleanIfNewStackLogMessage();
	void CleanInventory();
	void ResetPrintedInventoryValues();

	bool GetInventoryToggle();
	void SetInventoryToggle(bool isInventoryDisplayed);

	bool IsInventoryPrinted();
	void SetIsInventoryPrinted(bool isInventoryPrinted);

private:
	void CleanNumberOfcolumnChars(size_t numberOfColToClean);
	bool IsCurrentSelectionPrinted();
	void DisplayStackSize();
	void OnEmptyStack();
	void FindOtherStack();
	void CheckIfLastStack();
	bool IsInventoryEmpty();
	
//Member variables
public:
	// Source : https://stackoverflow.com/questions/19762755/creating-a-list-in-c-with-initial-capacity
	list<InventoryObject*> m_inventoryObjectsList;// = list<InventoryObject*>{ MAX_INVENTORY_OBJECTS };
	list<InventoryObject*>::iterator m_inventoryPtrIterator;

	//In order to have a string pointer it can only be a const char* with "".
	const char* FILE_PATH = "saved_files/InventorySaveFile.txt";

private:
	const char* UNIFORM_TAB = "    "; // "\t" is not working properly. It is not tabulating the same way for every string.
	const char* ENTER_NAME = "Enter item name: ";
	const char* ENTER_COST = "Enter item cost: ";
	const char* SELECTED_OBJECT = "Selected objec: ";
	const char* STACK_SIZE = "Stack size: ";
	const char* QUIT = "Q. Quit";
	const char* CHANGE_STACK = "+/- Change Stack";
	const char* STACK_CREATED = "New stack created";

	COORD m_printedInvetoryLastCursorPosition;
	COORD m_cursorPositionBeforeInventory;

	size_t m_printedInventoryRows = 0;
	
	E_equimentSlots m_currentEquipmentSlot = E_equimentSlots::Head;
	E_inputMode m_currentInputMode = E_inputMode::Navigation;
	bool m_isLogMessagePrinted = false;
	bool m_isNewStackLogMessagePrinted = false;
	bool m_inventoryToggle = false;
	bool m_isInventoryPrinted = false;
};