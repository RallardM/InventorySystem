#include <conio.h>
#include <iostream>

#include "Input.h"

using namespace std;

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

void Input::SetInventory(Inventory* inventory)
{
	m_inventory = inventory;
}

void Input::GetNavigationInput()
{
	char input = _getch();
	switch (input)
	{
		// Move the selection to the object on the left
	case 'a':
	case 'A':
		// TODO : Paulo : Navigation
		break;

		// Move the selection to the object on the right
	case 'd':
	case 'D':
		// TODO : Paulo : Navigation
		break;

		// Remove the selected object from the inventory
	case 'r':
	case 'R':
		// TODO : Remi
		break;

	case 'i':
	case 'I':
		m_inventory->SetCurrentInputMode(E_inputMode::Edition);
		m_inventory->DisplayEditionMenu();
		break;

	case 's':
	case 'S':
		// TODO : Remi save inventory : Display in the cout

	case 'l':
	case 'L':
		// TODO : Remi load inventory : Display in the cout
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
	case 'b':
	case 'B':
		m_inventory->AddBasicObject();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
		break;

	case 'c':
	case 'C':
		m_inventory->AddConsumable();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
		break;

	case 'e':
	case 'E':
		m_inventory->AddEquipment();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
		break;

	case 'n':
	case 'N':
		m_inventory->DisplayNavigationMenu();
		m_inventory->SetCurrentInputMode(E_inputMode::Navigation);
		m_inventory->DisplayNavigationMenu();
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
				NavigateSlots(true);
				break;

			// Move the selection to the slot on the right
			case 'd':
			case 'D':
				NavigateSlots(false);
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