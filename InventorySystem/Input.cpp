#include <conio.h>
#include "Input.h"

void Input::GetInput()
{
	switch (m_currentInputMode)
	{
	case LOADING:
		GetLoadingInput();
		break;

	case NAVIGATION:
		GetNavigationInput();
		break;

	case EDITION:
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

void Input::GetLoadingInput()
{
	char input = _getch();
	switch (input)
	{
		// Move the selection to the inventory on the left
	case 'a':
	case 'A':
		// TODO : Remi : inventory navigation
		break;

		// Move the selection to the inventory on the right
	case 'd':
	case 'D':
		// TODO : Remi : inventory navigation
		break;

		// Remove the selected inventory from the inventory
	case 'r':
	case 'R':
		// TODO : Remi : inventory navigation
		break;

	case 'i':
	case 'I':
		// TODO : Remi : inventory navigation
		break;

	default:
		// TODO : Paulo : Error message : You have to enter an invalid input
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
		m_currentInputMode = EDITION;
		m_inventory->DisplayEditionMenu();
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
		m_currentInputMode = NAVIGATION;
		m_inventory->DisplayNavigationMenu();
		break;

	case 'c':
	case 'C':
		m_inventory->AddConsumable();
		m_currentInputMode = NAVIGATION;
		m_inventory->DisplayNavigationMenu();
		break;

	case 'e':
	case 'E':
		m_inventory->AddEquipment();
		m_currentInputMode = NAVIGATION;
		m_inventory->DisplayNavigationMenu();
		break;

	case 'n':
	case 'N':
		m_inventory->DisplayNavigationMenu();
		m_currentInputMode = NAVIGATION;
		m_inventory->DisplayNavigationMenu();
		break;

	default:
		// TODO : Remi : Error handling : You have to enter an invalid input
		break;
	}
}

