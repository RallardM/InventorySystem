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
	unsigned short int stacks = 1;
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
		RemoveSpaceInFront(line);
		RemoveSpaceInMiddle(line);
		RemoveSpaceInBack(line);
		RemoveRawStrings(line);
		IdentifyString(&line, previousLine, type, name, equipmentSlot, cost, stacks, currentDurability, maxDurability);
		previousLine = line;
	}
	loadFile.close();
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
		stacks = 1;
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
		RemoveRawStrings(*line);
		RemoveExtraLengthFromString(*line, NAME);
		name = *line;
		return;
	}

	if (IsThisStringInLine(line, COST))
	{
		RemoveStringFromString(*line, COST);
		RemoveRawStrings(*line);
		RemoveExtraLengthFromString(*line, COST);
		cost = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, STACKS))
	{
		RemoveStringFromString(*line, STACKS);
		RemoveRawStrings(*line);
		RemoveExtraLengthFromString(*line, STACKS);
		stacks = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, CURRENT_DURABILITY))
	{
		RemoveStringFromString(*line, CURRENT_DURABILITY);
		RemoveRawStrings(*line);
		RemoveExtraLengthFromString(*line, CURRENT_DURABILITY);
		currentDurability = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, MAX_DURABILITY))
	{
		RemoveStringFromString(*line, MAX_DURABILITY);
		RemoveRawStrings(*line);
		RemoveExtraLengthFromString(*line, MAX_DURABILITY);
		maxDurability = stoi(*line);
		return;
	}

	if (IsThisStringInLine(line, EQUIPMENT_SLOT))
	{
		RemoveStringFromString(*line, EQUIPMENT_SLOT);
		RemoveRawStrings(*line);
		RemoveExtraLengthFromString(*line, EQUIPMENT_SLOT);
		slot = StringToEnum(line);
		return;
	}

}


//bool FileManager::IsStringAnEnum(string* line)
//{
//	// Source : https://cplusplus.com/reference/string/string/compare/
//	if (line->compare("Head") == 0 || line->compare("Chest") == 0 || line->compare("Legs") == 0 || line->compare("Weapon1") == 0 || line->compare("Weapon2") == 0)
//	{
//		return true;
//	}
//	return false;
//}

E_equimentSlots FileManager::StringToEnum(string* line)
{
	if (IsThisStringInLine(line, "Head"))
	{
		return E_equimentSlots::Head;
	}
	else if (IsThisStringInLine(line, "Chest"))
	{
		return E_equimentSlots::Chest;
	}
	else if (IsThisStringInLine(line, "Legs"))
	{
		return E_equimentSlots::Legs;
	}
	else if (IsThisStringInLine(line, "Weapon1"))
	{
		return E_equimentSlots::Weapon1;
	}
	else if (IsThisStringInLine(line, "Weapon2"))
	{
		return E_equimentSlots::Weapon2;
	}
	else
	{
		return E_equimentSlots::Count;
	}
}


//void FileManager::EnumtoIntString(string* line, string& modifiedAttribute)
//{
//	switch ((E_equimentSlots)stoi(*line))
//	{
//	case E_equimentSlots::Head:
//		modifiedAttribute = to_string(static_cast<int>(E_equimentSlots::Head));
//		break;
//	case E_equimentSlots::Chest:
//		modifiedAttribute = to_string(static_cast<int>(E_equimentSlots::Chest));
//		break;
//	case E_equimentSlots::Legs:
//		modifiedAttribute = to_string(static_cast<int>(E_equimentSlots::Legs));
//		break;
//	case E_equimentSlots::Weapon1:
//		modifiedAttribute = to_string(static_cast<int>(E_equimentSlots::Weapon1));
//		break;
//	case E_equimentSlots::Weapon2:
//		modifiedAttribute = to_string(static_cast<int>(E_equimentSlots::Weapon2));
//		break;
//	case E_equimentSlots::Count:
//		modifiedAttribute = to_string(static_cast<int>(E_equimentSlots::Count));
//		break;
//	default:
//		// TODO : Add error message
//		break;
//	}
//}

void FileManager::RemoveDoubleSpaces(string& line)
{
	CheckIfEmpty(&line);

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
void FileManager::RemoveSpaceInFront(string& line)
{
	CheckIfEmpty(&line);

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
}

void FileManager::RemoveSpaceInMiddle(string& line)
{
	CheckIfEmpty(&line);

	// If there is a lonely space between a colon and a character
	for (size_t i = 0; i < line.length() - 1; i++)
	{
		if (line[i] == ':' && isspace(line[i + 1]))
		{
			// Shift all characters to the left by one
			for (size_t j = i + 1; j < line.length() - 1; j++)
			{
				line[j] = line[j + 1];
			}
			break;
		}

		if (i > 0 && isspace(line[i - 1]) && line[i] == ':')
		{
			// Shift all characters to the left by one
			for (size_t j = i + 1; j < line.length() - 1; j++)
			{
				line[j] = line[j + 1];
			}
			break;
		}
	}
}

void FileManager::RemoveSpaceInBack(string& line)
{
	CheckIfEmpty(&line);

	// If there is a lonely space at the end of the (non-empty) string
	if (!line.empty() && std::isspace(line.back()))
	{
		// Remove the last character from memory
		line.pop_back();
	}
}

void FileManager::RemoveRawStrings(string& line)
{
	CheckIfEmpty(&line);

	// Source : https://learn.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-170
	char rawStrings[12] = { '\n', '\r', '\t', '\v', '\f', '\b', '\a', '\\', '\?' , '\'', '\"', '\0'};
	size_t rawStringsLength = sizeof(rawStrings) / sizeof(rawStrings[0]);
	string initialLine = line;
	//const char* newLine = "\n";
	//const char* carriageReturn = "\r";
	//const char* tabulation = "\t";
	//const char* verticalTabulation = "\v";
	//const char* formFeed = "\f";
	//const char* backspace = "\b";
	//const char* alert = "\a";
	//const char* backslash = "\\";
	//const char* questionMark = "\?";
	//const char* singleQuote = "\'";
	//const char* doubleQuote = "\"";
	//const char* nullCharacter = "\0";
	//const char* octalValue = "\ooo"; C4129 warning
	//const char* hexValue = "\xhh"; Error E0022

	for (size_t i = 0; i < line.length(); i++)
	{
		for (size_t j = i + 1; j < rawStringsLength; j++)
		{
			auto stringi = line[i];// TODO : Remove after debug
			auto rawStr = rawStrings[j];// TODO : Remove after debug

			if (line[i] == rawStrings[j])
			{
				// Shift all characters to the begginig of the string
				for (size_t K = i; K < line.length() - 1; K++)
				{
					line[K] = line[K + 1];
				}
				break;
			}
		}
		break;
	}
}

void FileManager::RemoveStringFromString(string& line, const char* STRING_TO_REMOVE)
{
	CheckIfEmpty(&line);

	// For chars in line that are not chars in STRING_TO_REMOVE 
	// move STRING_TO_REMOVE characters to the beginning of the string
	for (size_t i = 0; i < line.length(); i++)
	{
		for (size_t j = i; j < strlen(STRING_TO_REMOVE); j++)
		{
			auto linei = line[j];// TODO : Remove after debug
			auto stringToRemovej = STRING_TO_REMOVE[i];// TODO : Remove after debug
			auto lineiPlus = line[j + (strlen(STRING_TO_REMOVE) - 1)];// TODO : Remove after debug
			auto stringToRemovejPlus = STRING_TO_REMOVE[i + (strlen(STRING_TO_REMOVE) - 1)];// TODO : Remove after debug

			// If the first and last char fits for both line and STRING_TO_REMOVE
			if (line[j] == STRING_TO_REMOVE[i] && line[j + (strlen(STRING_TO_REMOVE) - 1)] == STRING_TO_REMOVE[i + (strlen(STRING_TO_REMOVE) - 1)])
			{
				// Shift all characters to the begginig of the string
				for (size_t k = j; k < line.length() - (strlen(STRING_TO_REMOVE) + 1); k++)
				{
					line[k] = line[k + (strlen(STRING_TO_REMOVE))];
				}
				break;
			}
		}
		break;
	}
}

void FileManager::RemoveExtraLengthFromString(string& line, const char* STRING_TO_REMOVE)
{
	CheckIfEmpty(&line);

	// Source : https://stackoverflow.com/questions/74150327/string-size-returns-1-too-large-value-in-evaluation-system

	// "Hello World!\r\n" Windows string have two encoded raw strings at the end. 
	unsigned short const int ENCODED_RAW_STRINGS = 2;
	size_t lineLength = line.length();// + ENCODED_RAW_STRINGS;
	size_t stringLength = strlen(STRING_TO_REMOVE);// +ENCODED_RAW_STRINGS;
	size_t leanghtToRemain = (lineLength - stringLength) - ENCODED_RAW_STRINGS;

	// For the remaining characters in the string, remove them from memory
	for (size_t i = lineLength; i > 0; i--)
	{
		// Source : https://en.cppreference.com/w/cpp/string/byte/isspace
		if (i != leanghtToRemain)
		{
			line.pop_back();
		}
		else
		{
			break;
		}
	}
}

void FileManager::CheckIfEmpty(string* line)
{
	// If the line is empty, remove it from memory
	if (line->empty())
	{
		return;
	}
}

bool FileManager::IsThisStringInLine(string* line, const char* word)
{
	// Source : https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
	// Convert string* to const char* to compare it to the line pointer
	const char* lineChar = line->c_str();
	auto sixe = strlen(word);

	for (size_t i = 0; i < strlen(word); i++)
	{
		for (size_t j = i; j < line->length(); j++)
		{
			auto linezero = lineChar[j]; // TODO : Remove after debug
			auto wordzero = word[i]; // TODO : Remove after debug
			auto lineone = lineChar[j + strlen(word) - 1]; // TODO : Remove after debug
			auto wordone = word[i + strlen(word) - 1]; // TODO : Remove after debug

			// If it reaches the end of the string, return false
			if (lineChar[j + strlen(word) - 1] == '\0')
			{
				return false;
			}

			if (lineChar[j] == word[i] && lineChar[j + strlen(word) - 1] == word[i + strlen(word) - 1])
			{
				return true;
			}
		}
	}
	return false;
}