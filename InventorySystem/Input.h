#pragma once
#include "Inventory.h"
#include "FileManager.h"

class Input
{
// Methods
public:
	Input();
	Input(bool* isGameRunning);
	void GetInput();
	void NavigateEquipmentSlots(E_equimentSlots& currentEquipmentSlot);
	bool GetIsGameRunning();
	void SetInventory(Inventory* inventory);
	void SetFileManager(FileManager* fileManager);

private:
	void NavigateSlots(bool isNext);
	void NavigateItems(bool isNext);
	void GetNavigationInput();
	void GetEditionInput();
	void InventoryDisplayToggle();
	void EquipmentDisplayToggle();
	
// Member variables
public:
private:
	Inventory* m_inventory = nullptr;
	FileManager* m_fileManager = nullptr;
	bool m_isGameRunning;
};