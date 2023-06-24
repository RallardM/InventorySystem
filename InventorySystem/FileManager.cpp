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
	E_equimentSlots slot = E_equimentSlots::COUNT;

	if (loadFile.is_open() == false)
	{
		cout << endl << "Unable to open file!";
		exit(EXIT_FAILURE);
		return;
	}

	while (getline(loadFile, line))
	{
		RemoveSpaces(line);
		IdentifyString(&line, &previousLine, type, name, cost, currentDurability, maxDurability, slot);
		previousLine = line;

		//string itemName = line;
		//getline(loadFile, line);
		//int itemCost = stoi(line);
		//m_inventory->AddItem(itemName, itemCost);
	}
	loadFile.close();
}

void FileManager::RemoveSpaces(string& line)
{
	// Source : https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
	line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
}

void FileManager::IdentifyString(
	string* line,
	string* previousLine,
	string& type,
	string& name,
	unsigned short int& cost,
	unsigned short int& currentDurability,
	unsigned short int& maxDurability,
	E_equimentSlots& slot)
{
	//In order to have a string pointer it can only be a const char* 
	const char* OPENING_BRACKETS = "{";
	const char* NAME = "Name:";
	const unsigned short int NAME_LENGTH = 5;

	if (line[0] == OPENING_BRACKETS)
	{
		type = *previousLine;
		return;
	}
	else if (IsThisStringInLine(line, NAME, NAME_LENGTH))
	{
		// Source: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s12.html
		// Find "Name:" in the given line and removes it to keep the name of the object only.
		string::size_type findNameInString = line->find(NAME);
		if (findNameInString != string::npos)
		{
			// Erase "Name:" from the line.
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