#include <conio.h>

#include "Inventory.h"
#include "Input.h"


int main()
{
	Input* input = new Input();
	Inventory* inventory = new Inventory();
	bool isGameRunning = true;


	//inventory->DisplaySelectedItem();
	//TODO: Remove this part. These are examples of item instantiations
	//inventory->AddItem("Test", 30);
	//inventory->AddItem("Test2");
	//inventory->AddItem("Test3", 3);
	//inventory->AddItem("Test4", 10);

	//inventory->DisplaySelectedItem();

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
	delete inventory;
}