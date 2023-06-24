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
	unsigned short int currentDurability = 0;
	unsigned short int maxDurability = 0;
	E_equimentSlots equipmentSlot = E_equimentSlots::COUNT;

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
		IdentifyString(&line, &previousLine, type, name, equipmentSlot, cost, currentDurability, maxDurability);
		previousLine = line;
		//string itemName = line;
		//getline(loadFile, line);
		//int itemCost = stoi(line);
		//m_inventory->AddItem(itemName, itemCost);
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

// To only use afte a remove doulbe spaces to check if uneven spaces are still there.
void FileManager::RemoveLoneSpaces(string& line)
{
	// Source : https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
	// Source : https://en.cppreference.com/w/cpp/string/byte/isspace
	//line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ' && line[i + 1] == '\0') // If there is a lonely space at the end of the string
		{
			line.erase(i, 1); // Erase the space
		}
		{
			line.erase(i, 1);
		}

		if (line[-int(i)] == line[-1] && isalpha(line[i + 1])) // If there is a lonely space at the beginning of the string
		{
			line.erase(i, 1); // Erase the space
		}
	}
}

// Throws a warning if slot is placed last in the parameter list.
void FileManager::IdentifyString(string* line, string* previousLine, string& type, string& name, E_equimentSlots& slot, unsigned short int& cost, unsigned short int& currentDurability, unsigned short int& maxDurability)
{
	//In order to have a string pointer it can only be a const char* with "".
	const char* OPENING_BRACKETS = "{";
	const char* CLOSING_BRACKETS = "}";
	const char* NAME = "Name:";
	const unsigned short int NAME_LENGTH = 5;

	if (line[0] == OPENING_BRACKETS)
	{
		type = *previousLine;
		return;
	}
	else if (line[0] == CLOSING_BRACKETS)
	{
		m_inventory->AddItem(type, name, slot, cost, currentDurability, maxDurability);
		return;
	}
	else if (IsThisStringInLine(line, NAME, NAME_LENGTH))
	{
		// Source: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s12.html
		// Find "Name:" in the given line and removes it to keep the name of the object only.
		string::size_type findNameInString = line->find(NAME);
		if (findNameInString != string::npos)
		{
			// Erase "Name:" from the line and keep the name of the object only.
			line->erase(findNameInString, NAME_LENGTH);
		}

		return;
	}
	//else if (line == "cost")
	//{

	//}
	//else if (line == "stackSize")
	//{

	//}
	//else if (line == "currentDurability")
	//{

	//}
	//else if (line == "maxDurability")
	//{

	//}
	//else if (line == "equipmentSlot")
	//{

	//}
	else
	{
		cout << endl << "Unknown string: " << line;
		//exit(EXIT_FAILURE); // TODO: Uncomment this line after debugging
		return;
	}
}

bool FileManager::IsThisStringInLine(string* line, const char* word, unsigned short int xFirstLetters)
{
	// Source : https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
	// Convert string* to const char* to compare it to the line pointer
	const char* lineChar = line->c_str();
	for (size_t i = 0; i < xFirstLetters; i++)
	{
		if (lineChar[i] != word[i])
		{
			return false;
		}
	}
	return true;
}