#pragma once
#include <string>
#include "Inventory.h"

class FileManager
{
//Methods
public:
	FileManager(Inventory* inventory);
private:
	void LoadInventory();

//Member variables
public:

private:
	Inventory* m_inventory = nullptr;
	std::string m_loadfilePath = "saved_files/InventorySaveFiles.txt";
	std::string m_savefilePath = "saved_files/";
};

