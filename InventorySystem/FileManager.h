#pragma once
#include <string>
#include "Inventory.h"
#include "Enumerations.h"

class FileManager
{
//Methods
public:
	FileManager(Inventory* inventory);
	~FileManager();

	void LoadInventory();
	void SaveInventory();
	void CleanTxtFile();

private:
	void IdentifyString(string& previousLine, string& type, string& name, E_equimentSlots& slot, unsigned short int& cost, unsigned short int& stacks, unsigned short int& currentDurability, unsigned short int& maxDurability);
	E_equimentSlots StringToEnum();
	string EnumToString(E_equimentSlots* slot);
	void RemoveDoubleSpaces();
	void RemoveSpaceInFront();
	void RemoveSpaceInMiddle();
	void RemoveSpaceInBack();
	void RemoveRawStrings();
	void RemoveStringFromString(const char* NAME);
	void RemoveExtraLengthFromString(const char* CHAR_TO_REMOVE);
	bool IsLineEmpty();
	bool IsLineSingleRawString();
	bool IsThisStringInLine(const char* word);
	bool IsThisStringThisString(const char* word, size_t wordIndex, size_t lineIndex);
	void ShiftCharsToLeftInLine(size_t index);
	void ShiftCharsToStartOfString(const char* STRING_TO_MOVE, size_t j);
	unsigned short int ConstCharSize(const char* a);

//Member variables
public:

private:
	Inventory* m_inventory = nullptr; // Size: total size of the member variables in Inventory class.
	
	const char* rawStrings[12] = { "\n", "\r", "\t", "\v", "\f", "\b", "\a", "\\", "\?" , "\'", "\"", "\0" };

	//In order to have a string pointer it can only be a const char* with "".
	const char* OPENING_BRACKETS = "{";
	const char* CLOSING_BRACKETS = "}";
	const char* NAME = "Name:";
	const char* COST = "Cost:";
	const char* STACKS = "Stacks:";
	const char* CURRENT_DURABILITY = "CurrentDurability:";
	const char* MAX_DURABILITY = "MaxDurability:";
	const char* EQUIPMENT_SLOT = "EquipmentSlot:";

	// Dynamic size
	string* m_line;
};

