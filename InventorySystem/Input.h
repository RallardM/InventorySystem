#pragma once
#include "Inventory.h"

class Input
{
// Methods
public:
	void GetInput();
	void SetInventory(Inventory* inventory);

private:
	void GetNavigationInput();
	void GetEditionInput();
	
// Member variables
public:
private:
	Inventory* m_inventory = nullptr;
	enum e_inputMode
	{
		NAVIGATION,
		EDITION,
		COUNT
	};

	e_inputMode m_currentInputMode = NAVIGATION;
};