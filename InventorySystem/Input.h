#pragma once
#include "Inventory.h"

class Input
{
// Methods
public:
	void GetInput();
	void SetInventory(Inventory* inventory);

private:
	void GetLoadingInput();
	void GetNavigationInput();
	void GetEditionInput();
	
// Member variables
public:
private:
	Inventory* m_inventory = nullptr;
};