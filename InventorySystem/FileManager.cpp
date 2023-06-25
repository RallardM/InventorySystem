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
	string line = "";
	string previousLine = "";

	string type = "";
	string name = "";
	unsigned short int cost = 0;
	unsigned short int stacks = 0;
	unsigned short int currentDurability = 0;
	unsigned short int maxDurability = 0;
	E_equimentSlots equipmentSlot = E_equimentSlots::Count;

	if (loadFile.is_open() == false)
	{
		cout << endl << "Unable to open file!";
		exit(EXIT_FAILURE);
		return;
	}

	while (getline(loadFile, line))
	{
		RemoveDoubleSpaces(line);
		RemoveLoneSpaces(line);
		RemoveTabulations(line);
		IdentifyString(&line, previousLine, type, name, equipmentSlot, cost, stacks, currentDurability, maxDurability);
		previousLine = line;
	}
	loadFile.close();
}

void FileManager::RemoveDoubleSpaces(string& line)
{
	// Source : https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
	// Source : https://stackoverflow.com/questions/48029688/how-to-remove-all-double-spaces-from-string
	std::size_t doubleSpace = line.find("  ");
	while (doubleSpace != std::string::npos)
	{
		line.erase(doubleSpace, 1);
		doubleSpace = line.find("  ");
	}
}

// To only use afte a RemoveDoubleSpaces() to check if uneven spaces are still there.
void FileManager::RemoveLoneSpaces(string& line)
{
	// Source : https://en.cppreference.com/w/cpp/string/byte/isspace

	// If there is a lonely space at the beginning of the string
	if (isspace(line[0]))
	{
		// Shift all characters to the left by one
		for (size_t i = 0; i < line.length() - 1; i++)
		{
			line[i] = line[i + 1];
		}

		line[line.length() - 1] = '\0';
	}

	// If there is a lonely space at the end of the (non-empty) string
	if (!line.empty() && std::isspace(line.back()))
	{
		// Remove the last character from memory
		line.pop_back();
	}
}

void FileManager::RemoveTabulations(string& line)
{
	//TODO: Implement
}

// Throws a warning if slot is placed last in the parameter list.
void FileManager::IdentifyString(string* line, string& previousLine, string& type, string& name, E_equimentSlots& slot, unsigned short int& cost, unsigned short int& stacks, unsigned short int& currentDurability, unsigned short int& maxDurability)
{
	//In order to have a string pointer it can only be a const char* with "".
	const char* OPENING_BRACKETS = "{";
	const char* CLOSING_BRACKETS = "}";
	const char* NAME = "Name:";
	const char* COST = "Cost:";
	const char* STACKS = "Stacks:";
	const char* CURRENT_DURABILITY = "CurrentDurability:";
	const char* MAX_DURABILITY = "MaxDurability:";
	const char* EQUIPMENT_SLOT = "EquipmentSlot:";

	if (line[0] == OPENING_BRACKETS)
	{
		type = previousLine;
		return;
	}
	else if (line[0] == CLOSING_BRACKETS)
	{
		m_inventory->AddItem(type, name, slot, cost, stacks, currentDurability, maxDurability);
		previousLine = "";
		type = "";
		name = "";
		cost = 0;
		stacks = 0;
		currentDurability = 0;
		maxDurability = 0;
		slot = E_equimentSlots::Count;
		return;
	}

	// Early return if the previous line is empty, 
	// because it means that it is a new item.
	if (previousLine.empty())
	{
		return;
	}

	if (IsThisStringInLine(line, NAME))
	{
		RemoveStringFromString(*line, NAME);
		name = *line;
		return;
	}

	if (IsThisStringInLine(line, COST))
	{
		RemoveStringFromString(*line, COST);
		cost = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, STACKS))
	{
		RemoveStringFromString(*line, STACKS);
		stacks = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, CURRENT_DURABILITY))
	{
		RemoveStringFromString(*line, CURRENT_DURABILITY);
		currentDurability = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, MAX_DURABILITY))
	{
		RemoveStringFromString(*line, MAX_DURABILITY);
		maxDurability = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, EQUIPMENT_SLOT))
	{
		RemoveStringFromString(*line, EQUIPMENT_SLOT);
		slot = (E_equimentSlots)stoi(*line);
		return;
	}
}

void FileManager::RemoveStringFromString(string& line, const char* STRING_TO_REMOVE)
{
	// For chars in line that are not chars in STRING_TO_REMOVE 
	// move STRING_TO_REMOVE characters to the beginning of the string
	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] != STRING_TO_REMOVE[i])
		{
			line[i - strlen(STRING_TO_REMOVE)] = line[i];
		}
	}

	// For the remaining characters in the string, remove them from memory
	for (size_t i = line.length(); i > line.length(); i--)
	{
		if (i >= strlen(STRING_TO_REMOVE))
		{
			line.pop_back();
		}

	}
}

bool FileManager::IsThisStringInLine(string* line, const char* word)
{
	// Source : https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
	// Convert string* to const char* to compare it to the line pointer
	const char* lineChar = line->c_str();
	// Source : https://stackoverflow.com/questions/33457363/find-substring-in-a-string-with-loops-in-c
	for (size_t i = 0; i < line->length(); i++)
	{
		if (lineChar[i] == word[0])
		{
			for (size_t j = 0; j < strlen(word); j++)
			{
				if (lineChar[i + j] == word[j])
				{
					return true;
				}
			}
		}
	}
	return false;
}