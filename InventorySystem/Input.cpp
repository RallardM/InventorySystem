#include <conio.h>
#include "Input.h"

void Input::GetInput()
{
	switch (m_currentInputMode)
	{
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
		break;

	case 'c':
	case 'C':
		m_inventory->AddConsumable();
		break;

	case 'e':
	case 'E':
		// TODO : Remi : Add equipment object to inventory
		break;

	case 'n':
	case 'N':
		m_inventory->DisplayNavigationMenu();
		break;

	default:
		// TODO : Remi : Error handling : You have to enter an invalid input
		break;
	}
}

