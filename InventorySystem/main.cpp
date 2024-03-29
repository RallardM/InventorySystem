#include <conio.h>

#include "Inventory.h"
#include "Input.h"
#include "FileManager.h"

void InventoryRender(Inventory* inventory);
void EquipmentRender(Inventory* inventory);

int main()
{
	// Create pointer objects
	bool* isGameRunning = new bool(true);
	Input* input = new Input(isGameRunning);
	Inventory* inventory = new Inventory();

	// Initial load of the inventory into list from the txt file
	FileManager* fileManager = new FileManager(inventory);
	fileManager->LoadInventory();

	// Give inventory and filemanager access to the input object
	input->SetFileManager(fileManager);
	input->SetInventory(inventory);

	// Initial display of current menu selected object, which is the navigation menu by default
	inventory->DisplayCurrentMenu();
	inventory->DisplayCurrentObject();

	while (input->GetIsGameRunning())
	{
		// If the user presses a key
		if (_kbhit())
		{
			// Verify that key 
			input->GetInput();
		}

		InventoryRender(inventory);
		EquipmentRender(inventory);
	}

	// Delete pointer objects
	delete fileManager;
	inventory->m_inventoryObjectsList;
	delete isGameRunning;
	inventory->DestroyAllInventoryObjects();
	delete inventory;
	delete input;
}

void InventoryRender(Inventory* inventory)
{
	if (inventory->GetInventoryToggle() && !inventory->IsInventoryPrinted())
	{
		inventory->DisplayInventory();
	}
	else if (!inventory->GetInventoryToggle() && inventory->IsInventoryPrinted())
	{
		inventory->CleanInventory();
		inventory->RefreshToggledContainers();
	}
}

void EquipmentRender(Inventory* inventory)
{
	if (inventory->GetEquipmentToggle() && !inventory->IsEquipmentPrinted())
	{
		inventory->DisplayEquipment();
	}
	else if (!inventory->GetEquipmentToggle() && inventory->IsEquipmentPrinted())
	{
		inventory->CleanEquipment();
		inventory->RefreshToggledContainers();
	}
}