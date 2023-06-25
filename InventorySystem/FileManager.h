#pragma once
#include <string>
#include "Inventory.h"
#include "Enumerations.h"

class FileManager
{
//Methods
public:
	FileManager(Inventory* inventory);
	void LoadInventory();

private:
	void RemoveDoubleSpaces(string& line);
	void RemoveLoneSpaces(string& line);
	void RemoveTabulations(string& line);
	void IdentifyString(string* line, string& previousLine, string& type, string& name, E_equimentSlots& slot, unsigned short int& cost, unsigned short int& stacks, unsigned short int& currentDurability, unsigned short int& maxDurability);
	void RemoveStringFromString(string& line, const char* NAME);
	bool IsThisStringInLine(string* line, const char* word);

//Member variables
public:

private:
	Inventory* m_inventory = nullptr;
	std::string m_loadfilePath = "saved_files/InventorySaveFile.txt";
	std::string m_savefilePath = "saved_files";
};

