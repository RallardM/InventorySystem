#include <conio.h>

#include "Inventory.h"
#include "Input.h"
#include "FileManager.h"

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

		//if (!inventory->IsCurrentSelectionPrinted()) // TODO: to complete
		//{
		//	inventory->DisplayCurrentMenuMode();
		//}
	}

	// Delete pointer objects
	delete fileManager;
	inventory->m_inventoryObjectsList;
	delete isGameRunning;
	inventory->DestroyAllInventoryObjects();
	delete inventory;
	delete input;
}