#pragma once
#include "Inventory.h"

class Input
{
// Methods
public:
	void GetInput();
	void SetInventory(Inventory* inventory);
	void NavigateEquipmentSlots();

	void NavigateSlots(bool isNext);

private:
	void GetNavigationInput();
	void GetEditionInput();
	
// Member variables
public:
private:
	Inventory* m_inventory = nullptr;
};