#include <string>
#include <iostream>
#include <conio.h>
#include <filesystem>
#include <Windows.h>

#include "Inventory.h"
#include "Input.h"
#include "ConsumableObject.h"
#include "EquipmentObject.h"
#include "BaseObject.h"

using namespace std;

Inventory::Inventory()
{
	cout << "Enters Inventory constructor" << endl;
	//for (size_t i = 0; i < MAX_INVENTORY_OBJECTS; i++)
	//{
	//	m_inventoryObjectsList.push_back(new InventoryObject("Typeless", "Nameless", 0, 0, 0, 0, E_equimentSlots::Count, true));
	//}

	m_inventoryPtrIterator = m_inventoryObjectsList.begin();
}

void Inventory::AddItem(E_itemType itemType, string itemName, unsigned short int itemCost/* = 0 */, unsigned short int itemStacks/* = 1 */, unsigned short int currentDurability/* = 0 */, unsigned short int maxDurability /* = 0 */, E_equimentSlots equipmentSlot/* = E_equimentSlots::Count */)//, bool isEmpty /* = false */)
{
	if (itemType == E_itemType::Consumable)
	{
		ConsumableObject* newConsumableObject;
		newConsumableObject = new ConsumableObject(itemName, itemCost, itemType, itemStacks, currentDurability, maxDurability, equipmentSlot);// , isEmpty);
		m_inventoryObjectsList.push_back(newConsumableObject);
	}
	else if (itemType == E_itemType::Equipment)
	{
		EquipmentObject* newEquipmentObject;
		newEquipmentObject = new EquipmentObject(itemName, itemCost, itemType, itemStacks, currentDurability, maxDurability, equipmentSlot);// , isEmpty);
		m_inventoryObjectsList.push_back(newEquipmentObject);
	}
	else if (itemType == E_itemType::BaseObject)
	{
		BaseObject* newBaseObject;
		newBaseObject = new BaseObject(itemName, itemCost, itemType, itemStacks, currentDurability, maxDurability, equipmentSlot);// , isEmpty);
		m_inventoryObjectsList.push_back(newBaseObject);
	}
	else
	{
		cout << "Error: Invalid item type." << endl;
	}

	UpdateIterator();
}

void Inventory::UpdateIterator()
{
	if (!m_inventoryObjectsList.empty())
	{
		// Source : https://www.geeksforgeeks.org/stdprev-in-cpp/
		// Put the penultimate element as the current iterator
		m_inventoryPtrIterator = prev(m_inventoryObjectsList.end());
	}
}

void Inventory::RemoveItem()
{
	string itemName = *(*m_inventoryPtrIterator)->GetName();
	m_inventoryObjectsList.erase(m_inventoryPtrIterator);
	m_inventoryPtrIterator = m_inventoryObjectsList.begin();
	DisplayCurrentObject();
	cout << endl << UNIFORM_TAB << itemName << " has been removed from the inventory." << endl;
	m_isLogMessagePrinted = true;
}

void Inventory::AddBasicObject()
{
	E_itemType itemType = E_itemType::BaseObject;
	string itemName;
	unsigned short int itemCost;

	cout << endl <<
		UNIFORM_TAB << ENTER_NAME;
	cin >> itemName; // TODO : Remi : Use getline to allow spaces in the name // TODO : Remi : Check for wrong inputs
	cout << endl <<
		UNIFORM_TAB << ENTER_COST;
	cin >> itemCost; // TODO : Remi : Check for wrong inputs

	AddItem(itemType, itemName, itemCost);
}

void Inventory::AddConsumable()
{
	E_itemType itemType = E_itemType::Consumable;
	string itemName;
	unsigned short int itemCost;
	unsigned short int itemStacks;

	cout << endl <<
		UNIFORM_TAB << ENTER_NAME;
	cin >> itemName; // TODO : Remi : Check for wrong inputs
	cout << endl <<
		UNIFORM_TAB << ENTER_COST;
	cin >> itemCost; // TODO : Remi : Check for wrong inputs
	cout << endl <<
		UNIFORM_TAB << "Enter item stacks: ";
	cin >> itemStacks;

	AddItem(itemType, itemName, itemCost, itemStacks);
}

void Inventory::AddEquipment()
{
	E_itemType itemType = E_itemType::Equipment;
	string itemName;
	unsigned short int itemCost;
	unsigned short int currentDurability;
	unsigned short int maxDurability;

	system("CLS"); // TODO : Remi : Check if wrong clear
	cout << endl <<
		UNIFORM_TAB << ENTER_NAME;
	cin >> itemName; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		UNIFORM_TAB << ENTER_COST;
	cin >> itemCost; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		UNIFORM_TAB << "Enter item current durability: ";
	cin >> currentDurability; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		UNIFORM_TAB << "Enter item max durability: ";
	cin >> maxDurability; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		UNIFORM_TAB << "A. Previous Slot" << UNIFORM_TAB << "D. Next Slot" << UNIFORM_TAB << "E. Select";
	cout << endl <<
		UNIFORM_TAB << "Select an item equipment slot: ";

	MoveCursorToLocation({ 35, 2 }); // TODO : Remi : Magic number
	cout << GetEnumString(&m_currentEquipmentSlot) << endl;

	// Access to Input class by creating an instance of it and assigning the current Inventory 
	// class object to give Input access to this new instance specifically.
	Input input;
	input.SetInventory(this);
	input.NavigateEquipmentSlots(m_currentEquipmentSlot);

	AddItem(itemType, itemName, itemCost, 1, currentDurability, maxDurability, m_currentEquipmentSlot);
}

void Inventory::DisplayCurrentMenu()
{
	switch (GetCurrentInputMode())
	{
	case E_inputMode::Navigation:
		DisplayNavigationMenu();
		break;

	case E_inputMode::Edition:
		DisplayEditionMenu();
		break;

	case E_inputMode::Count:
	default:
		// TODO : Remi Error message
		break;
	}
}

bool Inventory::IsCurrentSelectionPrinted() // TODO: To complete
{
	switch (m_currentInputMode)
	{
	case E_inputMode::Navigation:
		break;

	case E_inputMode::Edition:
		break;

	case E_inputMode::Count:
	default:
		// TODO : Remi Error message
		break;
	}
	return false;
}

void Inventory::DisplayNavigationMenu()
{
	system("CLS");
	cout << endl <<
		UNIFORM_TAB << "A. Previous Object" <<
		UNIFORM_TAB << "D. Next Object" <<
		UNIFORM_TAB << "R. Remove Selected" <<
		UNIFORM_TAB << "I. Edit Objects" << endl << endl <<
		UNIFORM_TAB << "L. Load Invetory" <<
		UNIFORM_TAB << "S. Save Invetory" <<
		UNIFORM_TAB << QUIT;

	cout << endl << endl;
}

void Inventory::DisplayEditionMenu()
{
	system("CLS");
	cout << endl <<
		UNIFORM_TAB << "B. Add Basic Object" <<
		UNIFORM_TAB << "C. Add Consumable" <<
		UNIFORM_TAB << "E. Add Equipment" << endl << endl <<
		UNIFORM_TAB << "N. Back To Navigation" <<
		UNIFORM_TAB << QUIT << endl << endl;
}

void Inventory::DisplayCurrentObject()
{
	if (IsInventoryEmpty())
	{
		return;
	}

	cout << endl;
	ClearConsolePreviousLine();
	cout << UNIFORM_TAB << SELECTED_OBJECT;
	cout << *(*m_inventoryPtrIterator)->GetName() + UNIFORM_TAB;

	if (*(*m_inventoryPtrIterator)->GetStackSize() > 1)
	{
		cout << STACK_SIZE;
		DisplayStackSize();
	}
}

void Inventory::DisplayStackSize()
{
	cout << *(*m_inventoryPtrIterator)->GetStackSize();
	cout << UNIFORM_TAB << "+/- Change Stack";
}

void Inventory::DestroyAllInventoryObjects() // TODO : Delete objects of objects before deleting the objects
{
	if (IsInventoryEmpty())
	{
		return;
	}
	for (InventoryObject* object : m_inventoryObjectsList) // TODO : Remi : Add new object classes
	{
		object->DeleteAttributes();
		delete object;
	}
	m_inventoryObjectsList.clear();
}

string Inventory::GetEnumString(E_equimentSlots* equipmentSlot)
{
	switch (*equipmentSlot)
	{
	case E_equimentSlots::Head:
		return "Head   ";
		break;

	case E_equimentSlots::Chest:
		return "Chest  ";
		break;

	case E_equimentSlots::Legs:
		return "Legs   ";
		break;

	case E_equimentSlots::Weapon1:
		return "Weapon1";
		break;

	case E_equimentSlots::Weapon2:
		return "Weapon2";
		break;

	default:
		// TODO : Remi : Error message : You have to enter an invalid input
		return "Error : wrong slot";
		break;
	}
	return "Error";
}


void Inventory::CheckIfConsumable()
{
	if (*(*m_inventoryPtrIterator)->GetType() != E_itemType::Consumable)
	{
		return;
	}
}

void Inventory::ChangeStackSize(bool isIncreasing)
{
	InventoryObject* inventoryObject = *m_inventoryPtrIterator;
	unsigned short int currentStackSize = *inventoryObject->GetStackSize();
	unsigned short int maxStackSize = inventoryObject->GetMaxStackSize();
	COORD consoleColCharToStack;
	consoleColCharToStack.X = static_cast<SHORT>(strlen(UNIFORM_TAB) + strlen(SELECTED_OBJECT) + (*m_inventoryPtrIterator)->GetNameLenght() + strlen(UNIFORM_TAB) + strlen(STACK_SIZE));
	consoleColCharToStack.Y = 5;

	if (isIncreasing && currentStackSize < maxStackSize)
	{
		// Get the number of console collones until the end of 'Stack size: '
		(*(*m_inventoryPtrIterator)->GetStackSize())++;

		MoveCursorToLocation(consoleColCharToStack);
		DisplayStackSize();
	}
	else if (isIncreasing && currentStackSize == maxStackSize)
	{
		// Creates another stack of the same item

	}
	else if (!isIncreasing && currentStackSize > 1)
	{
		(*(*m_inventoryPtrIterator)->GetStackSize())--;

		MoveCursorToLocation(consoleColCharToStack);
		DisplayStackSize();
	}
}

E_inputMode Inventory::GetCurrentInputMode()
{
	return m_currentInputMode;
}

E_equimentSlots Inventory::GetCurrentEquipmentSlot()
{
	return m_currentEquipmentSlot;
}

void Inventory::SetCurrentInputMode(E_equimentSlots currentEquipmentSlotPtr)
{
	m_currentEquipmentSlot = currentEquipmentSlotPtr;
}

void Inventory::SetCurrentInputMode(E_inputMode currentInputMode)
{
	m_currentInputMode = currentInputMode;
}

void Inventory::ClearConsolePreviousLine()
{
	std::cout << "\033[1A\033[0K";
}

void Inventory::MoveCursorToLocation(COORD position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}

bool Inventory::IsInventoryEmpty()
{
	return m_inventoryObjectsList.empty();
}

void Inventory::ClearInventoryList()
{
	m_inventoryObjectsList.clear();
}

void Inventory::CleanIfLogMessagePrinted()
{
	if (!m_isLogMessagePrinted)
	{
		return;
	}

	ClearConsolePreviousLine();
	ClearConsolePreviousLine();
	m_isLogMessagePrinted = false;
}
