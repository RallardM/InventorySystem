#include <string>
#include <iostream>
#include <conio.h>
#include <filesystem>

#include "Inventory.h"
#include "Input.h"

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

void Inventory::AddItem(string itemType, string itemName, unsigned short int itemCost/* = 0 */, unsigned short int itemStacks/* = 1 */, unsigned short int currentDurability/* = 0 */, unsigned short int maxDurability /* = 0 */, E_equimentSlots equipmentSlot/* = E_equimentSlots::Count */)//, bool isEmpty /* = false */)
{
	InventoryObject* newObject = new InventoryObject(itemType, itemName, itemCost, itemStacks, currentDurability, maxDurability, equipmentSlot);// , isEmpty);
	m_inventoryObjectsList.push_back(newObject);

	if (m_inventoryObjectsList.size() == 1)
	{
		m_inventoryPtrIterator = m_inventoryObjectsList.begin();
		//m_currentItem = *m_inventoryPtrIterator;
	}
}

void Inventory::AddBasicObject()
{
	string itemType = "BaseObject";
	string itemName;
	unsigned short int itemCost;

	cout << endl <<
		"    " << "Enter item name: ";
	cin >> itemName; // TODO : Remi : Use getline to allow spaces in the name // TODO : Remi : Check for wrong inputs
	cout << endl <<
		"    " << "Enter item cost: ";
	cin >> itemCost; // TODO : Remi : Check for wrong inputs

	AddItem(itemType, itemName, itemCost);
}

void Inventory::AddConsumable()
{
	string itemType = "Consumable";
	string itemName;
	unsigned short int itemCost;
	unsigned short int itemStacks;

	cout << endl <<
		"    " << "Enter item name: ";
	cin >> itemName; // TODO : Remi : Check for wrong inputs
	cout << endl <<
		"    " << "Enter item cost: ";
	cin >> itemCost; // TODO : Remi : Check for wrong inputs
	cout << endl <<
		"    " << "Enter item stacks: ";
	cin >> itemStacks;

	AddItem(itemType, itemName, itemCost, itemStacks);
}

void Inventory::AddEquipment()
{
	string itemType = "Equipment";
	string itemName;
	unsigned short int itemCost;
	unsigned short int currentDurability;
	unsigned short int maxDurability;

	system("CLS");
	cout << endl <<
		"    " << "Enter item name: ";
	cin >> itemName; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		"    " << "Enter item cost: ";
	cin >> itemCost; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		"    " << "Enter item current durability: ";
	cin >> currentDurability; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		"    " << "Enter item max durability: ";
	cin >> maxDurability; // TODO : Remi : Check for wrong inputs

	system("CLS");
	cout << endl <<
		"    " << "A. Previous Slot" << "    " << "D. Next Slot" << "    " << "E. Select";
	cout << endl <<
		"    " << "Select an item equipment slot: ";

	MoveCursorToLocation({ 35, 2 }); // TODO : Remi : Magic number
	cout << GetEnumString(&m_currentEquipmentSlot) << endl;

	// Access to Input class by creating an instance of it and assigning the current Inventory 
	// class object to give Input access to this new instance specifically.
	Input input;
	input.SetInventory(this);
	input.NavigateEquipmentSlots(m_currentEquipmentSlot);

	AddItem(itemType, itemName, itemCost, 1, currentDurability, maxDurability, m_currentEquipmentSlot);
}

//void Inventory::DisplaySelectedItem()
//{
//	system("CLS");
//	if (!m_currentItem)
//	{
//		cout << endl << "There is no item in this inventory!";
//		return;
//	}
//	cout << endl << "Current item: " << endl << m_currentItem->ToString();
//}

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

void Inventory::DisplayCurrentSelection()
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
		"    " << "A. Previous Object" <<
		"    " << "D. Next Object" <<
		"    " << "R. Remove Selected" <<
		"    " << "I. Edit Objects" << endl << endl <<
		"    " << "L. Load Invetory" <<
		"    " << "S. Save Invetory" <<
		"    " << "Q. Quit" << endl << endl;
}

void Inventory::DisplayEditionMenu()
{
	system("CLS");
	cout << endl <<
		"    " << "B. Add Basic Object" <<
		"    " << "C. Add Consumable" <<
		"    " << "E. Add Equipment" << endl << endl <<
		"    " << "N. Back To Navigation" <<
		"    " << "Q. Quit" << endl << endl;
}

void Inventory::DisplayCurrentObject()
{
	if (IsInventoryEmpty())
	{
		return;
	}

	cout << endl;
	ClearConsolePreviousLine();
	cout << "    " << "Selected objec: ";
	cout << *(*m_inventoryPtrIterator)->GetName() + "   "; 
	// TODO : Add stacks from consumable class
}

void Inventory::DestroyAllInventoryObjects() // TODO : Delete objects of objects before deleting the objects
{
	if (IsInventoryEmpty())
	{
		return;
	}
	for (InventoryObject* object : m_inventoryObjectsList)
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
