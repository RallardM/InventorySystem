#include <conio.h>

#include "Inventory.h"
#include "Input.h"
#include "FileManager.h"


int main()
{
	// Create pointer objects
	Input* input = new Input();
	Inventory* inventory = new Inventory();
	FileManager* fileManager = new FileManager(inventory);

	input->SetInventory(inventory);
	fileManager->LoadInventory();
	delete fileManager;

	inventory->DisplayNavigationMenu();


	bool isGameRunning = true;
	while (isGameRunning)
	{
		// If the user presses a key
		if (_kbhit())
		{
			// Verify that key
			input->GetInput();
		}
		
	}

	// Delete pointer objects
	delete input;
	inventory->DestroyAllInventoryObjects();
	delete inventory;
}