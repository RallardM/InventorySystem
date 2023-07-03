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

	m_inventoryPtrIterator = m_inventoryObjectsList.begin();
}

void Inventory::AddItem(E_itemType itemType, string itemName, unsigned short int itemCost/* = 0 */, unsigned short int itemStacks/* = 1 */, unsigned short int currentDurability/* = 0 */, unsigned short int maxDurability /* = 0 */, E_equimentSlots equipmentSlot/* = E_equimentSlots::Count */, bool hasStack /* = false */)
{
	if (itemType == E_itemType::Consumable)
	{
		ConsumableObject* newConsumableObject;
		newConsumableObject = new ConsumableObject(itemName, itemCost, itemType, itemStacks, hasStack);
		m_inventoryObjectsList.push_back(newConsumableObject);
	}
	else if (itemType == E_itemType::Equipment)
	{
		EquipmentObject* newEquipmentObject;
		newEquipmentObject = new EquipmentObject(itemName, itemCost, false, itemType, currentDurability, maxDurability, equipmentSlot);
		m_inventoryObjectsList.push_back(newEquipmentObject);
	}
	else if (itemType == E_itemType::BaseObject)
	{
		BaseObject* newBaseObject;
		newBaseObject = new BaseObject(itemName, itemCost, itemType);
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

void Inventory::DisplayNavigationMenu()
{
	system("CLS");
	cout << endl <<
		UNIFORM_TAB << "A. Previous Object" <<
		UNIFORM_TAB << "D. Next Object" <<
	    UNIFORM_TAB << "E. Equip Object" <<
		UNIFORM_TAB << "R. Remove Selected" << endl << endl <<
		UNIFORM_TAB << "SPACE. Show Invetory" <<
		UNIFORM_TAB << "I. Edit Objects" << 
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
		UNIFORM_TAB << "SPACE. Show Invetory" <<
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

	if ((*m_inventoryPtrIterator)->IsStackable() && *(*m_inventoryPtrIterator)->GetStackSize() > 0)
	{
		cout << STACK_SIZE;
		DisplayStackSize();
	}
}

void Inventory::DisplayInventory()
{
	m_cursorPositionBeforeInventory = GetConsoleCursorPosition();
	ResetPrintedInventoryRows();

	PrintInventoryRows();
	PrintEquipmentRows();

	m_printedInvetoryLastCursorPosition = GetConsoleCursorPosition();
	MoveCursorToLocation(m_cursorPositionBeforeInventory);
	SetIsInventoryPrinted(true);
}

void Inventory::PrintInventoryRows()
{
	size_t iteration = 0;

	cout << endl << endl;
	cout << UNIFORM_TAB << "Inventory: " << endl << endl;
	SetPrintedInventoryRows(m_printedInventoryRows + 3);

	if (IsInventoryEmpty())
	{
		cout << UNIFORM_TAB << "Inventory is empty.";
		SetPrintedInventoryRows(m_printedInventoryRows + 1);
		return;
	}
	
	for (InventoryObject* object : m_inventoryObjectsList)
	{
		if (*object->GetType() == E_itemType::Equipment && object->IsEquiped() == true)
		{
			continue;
		}

		if (iteration == 5)
		{
			cout << endl;
			SetPrintedInventoryRows(m_printedInventoryRows + 1);
		}

		cout << UNIFORM_TAB << *object->GetName() << UNIFORM_TAB;
		iteration++;
	}
	SetPrintedInventoryRows(m_printedInventoryRows + 1);
}

void Inventory::PrintEquipmentRows()
{
	size_t iteration = 0;

	cout << endl << endl;
	cout << UNIFORM_TAB << "Equipment: " << endl << endl;
	SetPrintedInventoryRows(m_printedInventoryRows + 3);

	if (!IsThereEquipedItems())
	{
		cout << UNIFORM_TAB << "No item equiped.";
		SetPrintedInventoryRows(m_printedInventoryRows + 1);
		return;
	}

	for (InventoryObject* object : m_inventoryObjectsList)
	{
		if (*object->GetType() != E_itemType::Equipment || object->IsEquiped() == false)
		{
			continue;
		}

		if (iteration == 5)
		{
			cout << endl;
			SetPrintedInventoryRows(m_printedInventoryRows + 1);
		}

		cout << UNIFORM_TAB << *object->GetName() << UNIFORM_TAB;
		iteration++;
	}
	SetPrintedInventoryRows(m_printedInventoryRows + 1);
}

void Inventory::MoveCursorToLocation(COORD position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
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

void Inventory::ChangeStackSize(bool isIncreasing)
{
	bool isItStackable = (*m_inventoryPtrIterator)->IsStackable(); // TODO : Remi : Delete after Debug
	if (!isItStackable)
	{
		return;
	}

	InventoryObject* inventoryObject = *m_inventoryPtrIterator;// TODO : Remi : Delete after Debug
	unsigned short int currentStackSize = *inventoryObject->GetStackSize();// TODO : Remi : Delete after Debug
	unsigned short int maxStackSize = inventoryObject->GetMaxStackSize();// TODO : Remi : Delete after Debug
	COORD consoleColCharToStack;// TODO : Remi : Delete after Debug
	consoleColCharToStack.X = static_cast<SHORT>(strlen(UNIFORM_TAB) + strlen(SELECTED_OBJECT) + (*m_inventoryPtrIterator)->GetNameLenght() + strlen(UNIFORM_TAB) + strlen(STACK_SIZE));
	consoleColCharToStack.Y = 5; // TODO : Remi : Magic number

	if (isIncreasing && currentStackSize < maxStackSize)
	{
		// Get the number of console columns until the end of 'Stack size: '
		(*(*m_inventoryPtrIterator)->GetStackSize())++;

		MoveCursorToLocation(consoleColCharToStack);
		DisplayStackSize();
	}
	else if (isIncreasing && currentStackSize == maxStackSize)
	{
		// Creates another stack of the same item
		AddItem(*(*m_inventoryPtrIterator)->GetType(), *(*m_inventoryPtrIterator)->GetName(), *(*m_inventoryPtrIterator)->GetCost(), 20, 0, 0, E_equimentSlots::Count, true); // TODO : Remi : Magic numbers
		cout << endl; // Jumps next constructor message
		ClearConsolePreviousLine(); // Removes constructor message
		
		SetStackSizeFromObjectId();

		// TODO : Remi : Delete after Debug
		//unsigned short int stackSize = 1;
		//(*m_inventoryPtrIterator)->SetStackSize(&stackSize);
		//(*m_inventoryPtrIterator)->SetMultupleStacks(true);
		MoveCursorToLocation(consoleColCharToStack);
		DisplayStackSize();

		consoleColCharToStack.X = static_cast<SHORT>(strlen(UNIFORM_TAB) + strlen(SELECTED_OBJECT) + (*m_inventoryPtrIterator)->GetNameLenght() + strlen(UNIFORM_TAB) + strlen(STACK_SIZE) + ((*(*m_inventoryPtrIterator)->GetStackSize()) % 10) + strlen(UNIFORM_TAB) + strlen(CHANGE_STACK));
		consoleColCharToStack.Y = 5; // TODO : Remi : Magic number
		MoveCursorToLocation(consoleColCharToStack);
		cout << UNIFORM_TAB << STACK_CREATED;
		m_isNewStackLogMessagePrinted = true;
		SetPrintedInventoryRows(m_printedInventoryRows + 1);
		RefreshPrintedInventory();
	}
	else if (!isIncreasing && currentStackSize > 1)
	{
		(*(*m_inventoryPtrIterator)->GetStackSize())--;

		MoveCursorToLocation(consoleColCharToStack);
		DisplayStackSize();
	}
	else if (!isIncreasing && currentStackSize == 1)
	{
		OnLastOnStack();
		RefreshPrintedInventory();
	}
	else
	{
		cout << endl << "Error : wrong stack manipulation in Inventory::ChangeStackSize()";
	}
}

void Inventory::SetStackSizeFromObjectId()
{
	for (InventoryObject* object : m_inventoryObjectsList)
	{
		if ((*m_inventoryPtrIterator)->GetId() == object->GetId())
		{
			unsigned short int stackSize = 1;
			object->SetStackSize(stackSize);
			object->SetMultupleStacks(true);
		}
	}
}

// Source : https://www.w3schools.blog/c-get-cursor-position-console
// Source : https://stackoverflow.com/questions/35800020/how-do-i-find-the-coordinates-of-the-cursor-in-a-console-window
COORD Inventory::GetConsoleCursorPosition()
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
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

void Inventory::SetCurrentInputMode(E_equimentSlots currentEquipmentSlotPtr)
{
	m_currentEquipmentSlot = currentEquipmentSlotPtr;
}

void Inventory::SetCurrentInputMode(E_inputMode currentInputMode)
{
	m_currentInputMode = currentInputMode;
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

void Inventory::ClearConsolePreviousLine()
{
	std::cout << "\033[1A\033[0K";
}

void Inventory::ClearInventoryList()
{
	m_inventoryObjectsList.clear();
}

void Inventory::CleanIfNewStackLogMessage()
{
	if (!m_isNewStackLogMessagePrinted)
	{
		return;
	}

	COORD consoleColCharToStack{};
	consoleColCharToStack.X = static_cast<SHORT>(strlen(UNIFORM_TAB) + strlen(SELECTED_OBJECT) + (*m_inventoryPtrIterator)->GetNameLenght() + strlen(UNIFORM_TAB) + strlen(STACK_SIZE) + ((*(*m_inventoryPtrIterator)->GetStackSize()) % 10) + strlen(UNIFORM_TAB) + strlen(CHANGE_STACK));
	consoleColCharToStack.Y = 5; // TODO : Remi : Magic number
	MoveCursorToLocation(consoleColCharToStack);

	CleanNumberOfcolumnChars(strlen(UNIFORM_TAB) + strlen(STACK_CREATED));

	consoleColCharToStack.X = consoleColCharToStack.X - static_cast<SHORT>(strlen(UNIFORM_TAB) + strlen(UNIFORM_TAB) + strlen(UNIFORM_TAB) + strlen(UNIFORM_TAB) + strlen(UNIFORM_TAB) + strlen(UNIFORM_TAB));
	consoleColCharToStack.Y = 5; // TODO : Remi : Magic number
	MoveCursorToLocation(consoleColCharToStack);

	m_isNewStackLogMessagePrinted = false;
}

void Inventory::CleanInventory()
{
	MoveCursorToLocation(m_printedInvetoryLastCursorPosition);
	cout << endl;

	for (size_t i = 0; i < GetPrintedInventoryRows(); i++)
	{
		ClearConsolePreviousLine();
	}

	SetIsInventoryPrinted(false);
	MoveCursorToLocation(m_cursorPositionBeforeInventory);
}

bool Inventory::GetInventoryToggle()
{
	return m_inventoryToggle;
}

void Inventory::SetInventoryToggle(bool isInventoryDisplayed)
{
	m_inventoryToggle = isInventoryDisplayed;
}

bool Inventory::IsInventoryPrinted()
{
	return m_isInventoryPrinted;
}

void Inventory::SetIsInventoryPrinted(bool isInventoryPrinted)
{
	m_isInventoryPrinted = isInventoryPrinted;
}

void Inventory::EquipObject()
{
	if (*(*m_inventoryPtrIterator)->GetType() != E_itemType::Equipment)
	{
		// TODO : Remi : add 'not equipable' message
		return;
	}

	if ((*m_inventoryPtrIterator)->IsEquiped())
	{
		(*m_inventoryPtrIterator)->SetIsEquiped(false);
	}
	else
	{
		(*m_inventoryPtrIterator)->SetIsEquiped(true);
	}

	RefreshPrintedInventory();
}

void Inventory::CleanNumberOfcolumnChars(size_t numberOfColToClean)
{
	for (size_t i = 0; i < numberOfColToClean; i++)
	{
		cout << " ";
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

void Inventory::DisplayStackSize()
{
	cout << *(*m_inventoryPtrIterator)->GetStackSize();
	cout << UNIFORM_TAB << CHANGE_STACK << UNIFORM_TAB;
}

void Inventory::OnLastOnStack()
{ 
	bool hasMultipleStacks = (*m_inventoryPtrIterator)->HasMultipleStacks(); // TODO : Remi : Delete after debug 
	if ((*m_inventoryPtrIterator)->HasMultipleStacks())
	{
		FindOtherStack();
		CheckIfLastStack();
	}
	else
	{
		m_inventoryPtrIterator = m_inventoryObjectsList.erase(m_inventoryPtrIterator);
		DisplayCurrentObject();
	}
}

void Inventory::FindOtherStack()
{
	for (InventoryObject* object : m_inventoryObjectsList)
	{
		if (object->IsStackable() == false)
		{
			continue;
		}

		if (object == *m_inventoryPtrIterator)
		{
			continue;
		}

		*m_inventoryPtrIterator = object;
		break;
	}
}

void Inventory::CheckIfLastStack()
{
	unsigned short int count = 0;
	for (InventoryObject* object : m_inventoryObjectsList)
	{
		if (object->IsStackable() == false)
		{
			continue;
		}

		count++;
	}

	if (count == 1)
	{
		(*m_inventoryPtrIterator)->SetMultupleStacks(false);
	}
}

bool Inventory::IsInventoryEmpty()
{
	return m_inventoryObjectsList.empty();
}

void Inventory::RefreshPrintedInventory()
{
	if (IsInventoryEmpty())
	{
		return;
	}

	if (!GetInventoryToggle())
	{
		return;
	}

	CleanInventory();
	DisplayInventory();
}

void Inventory::ResetPrintedInventoryRows()
{
	SetPrintedInventoryRows(0);
}


size_t Inventory::GetPrintedInventoryRows()
{
	return m_printedInventoryRows;
}

void Inventory::SetPrintedInventoryRows(size_t printedInventoryRows)
{
	m_printedInventoryRows = printedInventoryRows;
}

bool Inventory::IsThereEquipedItems()
{
	for (InventoryObject* object : m_inventoryObjectsList)
	{
		if (object->IsEquiped())
		{
			return true;
		}
	}
	return false;
}
