#include <fstream>
#include <iostream>

#include "FileManager.h"

using namespace std;

FileManager::FileManager(Inventory* inventory) :
	m_inventory(inventory)
{
}

void FileManager::LoadInventory()
{
	ifstream loadFile;
	loadFile.open(m_loadfilePath);

	if (loadFile.is_open() == false)
	{
		cout << endl << "Unable to open file!";
		exit(EXIT_FAILURE);
		return;
	}

	string line;
	while (getline(loadFile, line))
	{
		string itemName = line;
		getline(loadFile, line);
		int itemCost = stoi(line);
		m_inventory->AddItem(itemName, itemCost);
	}
	loadFile.close();
}