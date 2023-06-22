#include "Inventory.h"

int main()
{
	Inventory* inventory = new Inventory();

	inventory->DisplaySelectedItem();
	//TODO: Remove this part. These are examples of item instantiations
	inventory->AddItem("Test", 30);
	inventory->AddItem("Test2");
	inventory->AddItem("Test3", 3);
	inventory->AddItem("Test4", 10);

	inventory->DisplaySelectedItem();
}