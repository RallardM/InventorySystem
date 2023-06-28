#include <string>
#include <iostream>
#include <conio.h>
#include <filesystem>

#include "Inventory.h"

using namespace std;

void Inventory::AddItem(string& itemType, string& itemName, unsigned short int itemCost/* = 0 */, unsigned short int itemStacks/* = 1 */, unsigned short int currentDurability/* = 0 */, unsigned short int maxDurability /* = 0 */, E_equimentSlots equipmentSlot/* = E_equimentSlots::Count */)
{
	InventoryObject* newObject = new InventoryObject(itemType, itemName, itemCost, itemStacks, currentDurability, maxDurability, equipmentSlot);
	m_inventoryObjectsList.push_back(newObject);

	if (m_inventoryObjectsList.size() == 1)
	{
		m_currentItem = m_inventoryObjectsList.front();
	}
}

void Inventory::AddBasicObject()
{
	string itemType = "BaseObject";
	string itemName;
	unsigned short int itemCost;

	cout << endl << "Enter item name: ";
	cin >> itemName;
	cout << endl << "Enter item cost: ";
	cin >> itemCost;

	AddItem(itemType, itemName, itemCost);
}

void Inventory::AddConsumable()
{
	string itemType = "Consumable";
	string itemName;
	unsigned short int itemCost;
	unsigned short int itemStacks;

	cout << endl << "Enter item name: ";
	cin >> itemName;
	cout << endl << "Enter item cost: ";
	cin >> itemCost;
	cout << endl << "Enter item stacks: ";
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

	cout << endl << "Enter item name: ";
	cin >> itemName;
	cout << endl << "Enter item cost: ";
	cin >> itemCost;
	cout << endl << "Enter item current durability: ";
	cin >> currentDurability;
	cout << endl << "Enter item max durability: ";
	cin >> maxDurability;
	cout << endl << "Select an item equipment slot: ";
	cout << endl << '\t' << "A. Previous Slot" << '\t' << "D. Next Slot" << "E. Select";
	cout << endl << '\t' << GetEnumString(m_currentEquipmentSlot);
	NavigateEquipmentSlots();

	AddItem(itemType, itemName, itemCost, 1, currentDurability, maxDurability, m_currentEquipmentSlot);
}

void Inventory::NavigateEquipmentSlots()
{
	while (_kbhit())
	{
		E_equimentSlots newLeftEnumPosition = static_cast<E_equimentSlots>(static_cast<int>(m_currentEquipmentSlot) - 1);
		E_equimentSlots newRightEnumPosition = static_cast<E_equimentSlots>(static_cast<int>(m_currentEquipmentSlot) + 1);
		E_equimentSlots firstEnumPosition = static_cast<E_equimentSlots>(0);
		E_equimentSlots lastEnumPosition = static_cast<E_equimentSlots>(static_cast<int>(E_equimentSlots::Count) - 1);
		char input = _getch();
		switch (input)
		{
			// Move the selection to the slot on the left
		case 'a':
		case 'A':
			ClearConsolePreviousLine();
			// If the current enum number is greater than 0, it can move the selection to the slot on the left
			// else it will move the selection to the last slot
			if (newLeftEnumPosition >= firstEnumPosition)
			{
				cout << endl << '\t' << GetEnumString(newLeftEnumPosition);
				m_currentEquipmentSlot = newLeftEnumPosition;
			}
			else
			{
				cout << endl << '\t' << GetEnumString(lastEnumPosition);
				m_currentEquipmentSlot = lastEnumPosition;
			}
			break;

			// Move the selection to the slot on the right
		case 'd':
		case 'D':
			ClearConsolePreviousLine();
			// If the current enum number is smaller than the last enum number, it can move the selection to the slot on the right
			// else it will move the selection to the first slot
			if (newRightEnumPosition <= lastEnumPosition)
			{
				cout << endl << '\t' << GetEnumString(newRightEnumPosition);
				m_currentEquipmentSlot = newRightEnumPosition;
			}
			else
			{
				cout << endl << '\t' << GetEnumString(firstEnumPosition);
				m_currentEquipmentSlot = firstEnumPosition;
			}
			break;

		case 'e':
		case 'E':
			ClearConsolePreviousLine();
			break;

		default:
			// TODO : Remi : Error message : You have to enter an invalid input
			break;
		}
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

void Inventory::DisplaySelectedInventory()
{
	// TODO : Remi
}

void Inventory::DisplayCurrentMenu()
{
	switch (GetCurrentInputMode())
	{
	case E_inputMode::Loading:
		DisplayLoadingMenu();
		break;

	case E_inputMode::Navigation:
		DisplayNavigationMenu();
		break;

	case E_inputMode::Edition:
		DisplayEditionMenu();

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
	case E_inputMode::Loading:
		DisplaySelectedInventory();
		break;
	case E_inputMode::Navigation:
		break;
	case E_inputMode::Edition:
		break;
	case E_inputMode::Count:
		break;
	default:
		break;
	}
}

bool Inventory::IsCurrentSelectionPrinted() // TODO: To complete
{
	switch (m_currentInputMode)
	{
	case E_inputMode::Loading:

		break;
	case E_inputMode::Navigation:
		break;
	case E_inputMode::Edition:
		break;
	case E_inputMode::Count:
		break;
	default:
		break;
	}
	return false;
}

void Inventory::DisplayLoadingMenu()
{
	system("CLS");
	cout << endl << 
		"    " << "A. Previous Inventory" << 
		"    " << "D. Next Inventory" << 
		"    " << "R. Remove Selected" << 
		"    " << "I. Edit Inventory";
}

void Inventory::DisplayNavigationMenu()
{
	system("CLS");
	cout << endl << 
		"    " << "A. Previous Object" << 
		"    " << "D. Next Object" << 
		"    " << "R. Remove Selected" << 
		"    " << "I. Edit Objects";
}

void Inventory::DisplayEditionMenu()
{
	system("CLS");
	cout << endl <<
		"    " << "B. Add Basic Object" <<
		"    " << "C. Add Consumable" <<
		"    " << "E. Add Equipment" << endl <<
		"    " << "N. Back To Navigation";
}

void Inventory::DestroyAllInventoryObjects() // TODO : Delete objects of objects before deleting the objects
{
	for (InventoryObject* object : m_inventoryObjectsList)
	{
		object->DeleteAttributes();
		delete object;
	}
	m_inventoryObjectsList.clear();
}

string Inventory::GetEnumString(E_equimentSlots equipmentSlot)
{
	switch (equipmentSlot)
	{
	case E_equimentSlots::Head:
		return "Head";
		break;

	case E_equimentSlots::Chest:
		return "Chest";
		break;

	case E_equimentSlots::Legs:
		return "Legs";
		break;

	case E_equimentSlots::Weapon1:
		return "Weapon1";
		break;

	case E_equimentSlots::Weapon2:
		return "Weapon2";
		break;

	default:
		// TODO : Remi : Error message : You have to enter an invalid input
		return "Error";
		break;
	}
	return "Error";
}

E_inputMode Inventory::GetCurrentInputMode()
{
	return m_currentInputMode;
}

void Inventory::SetCurrentInputMode(E_inputMode currentInputMode)
{
	m_currentInputMode = currentInputMode;
}

void Inventory::ClearConsolePreviousLine()
{
	std::cout << "\033[1A\033[0K";
}