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
	void RemoveSpaces(string& line);
	void IdentifyString(
		string* line,
		string* previousLine,
		string& type,
		string& name,
		unsigned short int& cost,
		unsigned short int& currentDurability,
		unsigned short int& maxDurability,
		E_equimentSlots& slot);
	bool IsThisStringInLine(string* line, const char* word, unsigned short int xFirstLetters);

//Member variables
public:

private:
	enum e_objectAttributes
	{
		TYPE,
		NAME,
		COST,
		CURRENT_DURABILITY,
		MAX_DURABILITY,
		EQUIPMENT_SLOT,
		COUNT
	};

	Inventory* m_inventory = nullptr;
	std::string m_loadfilePath = "saved_files/InventorySaveFile.txt";
	std::string m_savefilePath = "saved_files";
};

