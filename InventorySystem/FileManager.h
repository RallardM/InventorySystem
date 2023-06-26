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
	void IdentifyString(string* line, string& previousLine, string& type, string& name, E_equimentSlots& slot, unsigned short int& cost, unsigned short int& stacks, unsigned short int& currentDurability, unsigned short int& maxDurability);
	//bool IsStringAnEnum(string* line);
	E_equimentSlots StringToEnum(string* line);
	//void EnumtoIntString(string* line, string& modifiedAttribute);
	void RemoveDoubleSpaces(string& line);
	void RemoveSpaceInFront(string& line);
	void RemoveSpaceInMiddle(string& line);
	void RemoveSpaceInBack(string& line);
	void RemoveRawStrings(string& line);
	void RemoveStringFromString(string& line, const char* NAME);
	void RemoveExtraLengthFromString(string& line, const char* STRING_TO_REMOVE);
	bool IsLineEmpty(string* line);
	bool IsThisStringInLine(string* line, const char* word);

//Member variables
public:
	




private:
	Inventory* m_inventory = nullptr;
	string m_loadfilePath = "saved_files/InventorySaveFile.txt";
	string m_savefilePath = "saved_files";
};

