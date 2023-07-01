#include <conio.h>
#include <iostream>

#include "Input.h"

using namespace std;

Input::Input() :
	m_isGameRunning(nullptr),
	m_inventory(nullptr),
	m_fileManager(nullptr)
{
	cout << "First Input constructor called!" << endl;
}

Input::Input(bool* isGameRunning) :
	m_isGameRunning(isGameRunning),
	m_inventory(nullptr),
	m_fileManager(nullptr)
{
	cout << "Second Input constructor called!" << endl;
}

void Input::GetInput()
{
	switch (m_inventory->GetCurrentInputMode())
	{
	case E_inputMode::Navigation:
		GetNavigationInput();
		break;

	case E_inputMode::Edition:
		GetEditionInput();
		break;

	default:
		// TODO : Remi : Error handling : The input mode is not valid
		break;
	}
}

void Input::GetNavigationInput()
{
	char input = _getch();
	switch (input)
	{
	// Move the selection to the object on the left
	case 'a':
	case 'A':
		m_inventory->CleanIfLogMessagePrinted();
		NavigateItems(false);
		break;

	// Move the selection to the object on the right
	case 'd':
	case 'D':
		m_inventory->CleanIfLogMessagePrinted();
		NavigateItems(true);
		break;

	// Remove the selected object from the inventory
	case 'r':
	case 'R':
		// TODO : Remi
		m_inventory->RemoveItem();
		break;

	// Display the edition menu
	case 'i':
	case 'I':
		m_inventory->SetCurrentInputMode(E_inputMode::Edition);
		m_inventory->DisplayEditionMenu();
		break;

	// Load the inventory from the txt file
	case 'l':
	case 'L':
		// TODO : Remi : test
		m_inventory->ClearInventoryList();
		m_fileManager->LoadInventory();
		break;

	// Save the inventory to the txt file
	case 's':
	case 'S':
		// TODO : Remi save inventory
		m_fileManager->CleanTxtFile();
		m_fileManager->SaveInventory();
		break;

	// Exit the game
	case 'q':
	case 'Q':
	case 'esc':
		m_isGameRunning = false;
		break;

	default:
		// TODO : Paulo : Error message : You have to enter an invalid input
		break;
	}
}

void Input::GetEditionInput()
{
	char input = _getch();
	switch (input)
	{
	// Add a basic object to the inventory
	case 'b':
	case 'B':
		m_inventory->AddBasicObject();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
		m_inventory->DisplayCurrentObject();
		break;

	// Add a consumable to the inventory
	case 'c':
	case 'C':
		m_inventory->AddConsumable();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
		m_inventory->DisplayCurrentObject();
		break;
	
	// Add an equipment to the inventory
	case 'e':
	case 'E':
		m_inventory->AddEquipment();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
		m_inventory->DisplayCurrentObject();
		break;

	// Quit the game
	case 'q':
	case 'Q':
	case 'esc':
		m_isGameRunning = false;
		break;

	// Go back to the navigation menu
	case 'n':
	case 'N':
		m_inventory->DisplayNavigationMenu();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
		m_inventory->DisplayCurrentObject();
		break;
	
	default:
		// TODO : Remi : Error handling : You have to enter an invalid input
		break;
	}
}

void Input::NavigateEquipmentSlots(E_equimentSlots& currentEquipmentSlot)
{
	bool IsChoiceMade = false;
	while (!IsChoiceMade)
	{
		if (_kbhit())
		{
			char input = _getch();
			switch (input)
			{
			// Move the selection to the slot on the left
			case 'a':
			case 'A':
				NavigateSlots(false); // TODO: Remi : check if correct directions
				break;

			// Move the selection to the slot on the right
			case 'd':
			case 'D':
				NavigateSlots(true); // TODO: Remi : check if correct directions
				break;

			// Choose the selected slot
			case 'e':
			case 'E':
				IsChoiceMade = true;
				m_inventory->ClearConsolePreviousLine();
				break;

			default:
				// TODO : Remi : Error message : You have to enter an invalid input
				break;
			}
		}
	}
}

void Input::NavigateSlots(bool isNext)
{
	E_equimentSlots newLeftEnumPosition = static_cast<E_equimentSlots>(static_cast<int>(m_inventory->GetCurrentEquipmentSlot()) - 1);
	E_equimentSlots newRightEnumPosition = static_cast<E_equimentSlots>(static_cast<int>(m_inventory->GetCurrentEquipmentSlot()) + 1);
	E_equimentSlots firstEnumPosition = static_cast<E_equimentSlots>(0);
	E_equimentSlots lastEnumPosition = static_cast<E_equimentSlots>(static_cast<int>(E_equimentSlots::Count) - 1);

	if (isNext)
	{
		// If the current enum number is greater than 0, it can move the selection to the slot on the left
		// and this selected enum number is smaller than the last enum number (invalid enum number comes out as large integers)
		// else it will move the selection to the last slot
		if ((newLeftEnumPosition >= firstEnumPosition) && (newLeftEnumPosition < lastEnumPosition))
		{
			m_inventory->MoveCursorToLocation({ 35, 2 }); // TODO : Remi : Magic number
			cout << m_inventory->GetEnumString(&newLeftEnumPosition) << endl;
			m_inventory->SetCurrentInputMode(newLeftEnumPosition);
		}
		else
		{
			m_inventory->MoveCursorToLocation({ 35, 2 }); // TODO : Remi : Magic number
			cout << m_inventory->GetEnumString(&lastEnumPosition) << endl;
			m_inventory->SetCurrentInputMode(lastEnumPosition);
		}
	}
	else if (!isNext)
	{
		// If the current enum number is smaller than the last enum number, it can move the selection to the slot on the right
		// else it will move the selection to the first slot
		if (newRightEnumPosition <= lastEnumPosition)
		{
			m_inventory->MoveCursorToLocation({ 35, 2 }); // TODO : Remi : Magic number
			cout << m_inventory->GetEnumString(&newRightEnumPosition) << endl;
			m_inventory->SetCurrentInputMode(newRightEnumPosition);
		}
		else
		{
			m_inventory->MoveCursorToLocation({ 35, 2 }); // TODO : Remi : Magic number
			cout << m_inventory->GetEnumString(&firstEnumPosition) << endl;
			m_inventory->SetCurrentInputMode(firstEnumPosition);
		}
	}
}


// Paulo coudl not finish in time, I used the help of chatGPT to finish this function as a placeholder for my other tasks
void Input::NavigateItems(bool isNext)
{
	if (!m_inventory->m_inventoryObjectsList.empty())
	{
		if (isNext)
		{
			// Increment the iterator if it's not pointing to the last element
			if (m_inventory->m_inventoryPtrIterator != m_inventory->m_inventoryObjectsList.end() && m_inventory->m_inventoryPtrIterator != prev(m_inventory->m_inventoryObjectsList.end()) && *(*m_inventory->m_inventoryPtrIterator)->GetStackSize() != 0)
			{
				++m_inventory->m_inventoryPtrIterator;
			}
			else
			{
				// Wrap around to the first element if at the end
				m_inventory->m_inventoryPtrIterator = m_inventory->m_inventoryObjectsList.begin();
			}
			m_inventory->m_inventoryPtrIterator = m_inventory->m_inventoryPtrIterator;
		}
		else
		{
			// Decrement the iterator if it's not pointing to the first element
			if (m_inventory->m_inventoryPtrIterator != m_inventory->m_inventoryObjectsList.begin() && *(*m_inventory->m_inventoryPtrIterator)->GetStackSize() != 0)
			{
				--m_inventory->m_inventoryPtrIterator;
			}
			else
			{
				// Wrap around to the last element if at the beginning
				m_inventory->m_inventoryPtrIterator = prev(m_inventory->m_inventoryObjectsList.end());
			}
		}

		m_inventory->DisplayCurrentObject();
	}
}


bool Input::GetIsGameRunning() 
{
	return m_isGameRunning;
}

void Input::SetInventory(Inventory* inventory)
{
	m_inventory = inventory;
}

void Input::SetFileManager(FileManager* fileManager)
{
	m_fileManager = fileManager;
}