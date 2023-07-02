#include <fstream>
#include <iostream>
#include <cctype>

#include "FileManager.h"

using namespace std;

FileManager::FileManager(Inventory* inventory) :
	m_inventory(inventory),
	m_line(new string())
{
	cout << "FileManager constructor called!" << endl;
}

FileManager::~FileManager()
{
	cout << "FileManager destructor called!" << endl;
	delete m_line;
}

void FileManager::LoadInventory()
{
	ifstream loadFile;
	loadFile.open(m_inventory->FILE_PATH);

	string previousLine = "";

	string name = "";
	unsigned short int cost = 0;
	unsigned short int stacks = 1;
	unsigned short int currentDurability = 0;
	unsigned short int maxDurability = 0;
	E_itemType type = E_itemType::Count;
	E_equimentSlots equipmentSlot = E_equimentSlots::Count;

	if (loadFile.is_open() == false)
	{
		cout << endl << "Unable to open file!";
		exit(EXIT_FAILURE);
		return;
	}

	while (getline(loadFile, *m_line))
	{
		if (IsLineEmpty() || IsLineSingleRawString())
		{
			continue;
		}

		RemoveRawStrings();
		RemoveDoubleSpaces();
		RemoveSpaceInFront();
		RemoveSpaceInMiddle();
		RemoveSpaceInBack();
		// TODO : Add a check if all words starts with a capital letter. ex: Broken urn
		IdentifyString(previousLine, type, name, equipmentSlot, cost, stacks, currentDurability, maxDurability);
		previousLine = *m_line;
	}
	loadFile.close();
}

void FileManager::SaveInventory()
{
	ofstream saveFile;
	saveFile.open(m_inventory->FILE_PATH);

	if (saveFile.is_open() == false)
	{
		cout << endl << "Unable to open file!";
		exit(EXIT_FAILURE);
		return;
	}

	for (const auto& object : m_inventory->m_inventoryObjectsList)
	{
		saveFile << EnumToString(object->GetType()) << endl;
		saveFile << OPENING_BRACKETS << endl;
		saveFile << "\t" << NAME << " " << *object->GetName() << endl;
		saveFile << "\t" << COST << " " << *object->GetCost() << endl;

		if (*object->GetStackSize() > 1)
		{
			saveFile << "\t" << STACKS << " " << *object->GetStackSize() << endl;
		}

		if (*object->GetCurrentDurability() > 0)
		{
			saveFile << "\t" << CURRENT_DURABILITY << " " << *object->GetCurrentDurability() << endl;
		}

		if (*object->GetMaxDurability() > 0)
		{
			saveFile << "\t" << MAX_DURABILITY << " " << *object->GetMaxDurability() << endl;
		}

		if (*object->GetEquipmentSlot() != E_equimentSlots::Count)
		{
			saveFile << "\t" << EQUIPMENT_SLOT << " " << EnumToString(object->GetEquipmentSlot()) << endl;
		}

		saveFile << CLOSING_BRACKETS << endl;
		saveFile << endl;
	}

	saveFile.close();
	cout << endl << "Inventory saved!" << endl; // TODO : Remi : Test to see if message shows
}

// Source : https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
void FileManager::CleanTxtFile()
{
	// Erase the contents of the file
	ofstream truncateFile(m_inventory->FILE_PATH, std::ios::trunc);

	// Check if the file was successfully opened and truncated
	if (!truncateFile)
	{
		cout << endl << "Unable to open file!";
		exit(EXIT_FAILURE);
		return;
	}

	// Close the file after truncating
	truncateFile.close();
}

// Throws a warning if equipmentSlot is placed last in the parameter list.
void FileManager::IdentifyString(string& previousLine, E_itemType& type, string& name, E_equimentSlots& equipmentSlot, unsigned short int& cost, unsigned short int& stacks, unsigned short int& currentDurability, unsigned short int& maxDurability)
{
	if (m_line[0] == OPENING_BRACKETS)
	{
		type = StringToE_itemType(&previousLine);
		return;
	}
	else if (m_line[0] == CLOSING_BRACKETS)
	{
		m_inventory->AddItem(type, name, cost, stacks, currentDurability, maxDurability, equipmentSlot);
		previousLine = "";
		type = E_itemType::Count;
		name = "";
		cost = 0;
		stacks = 1;
		currentDurability = 0;
		maxDurability = 0;
		equipmentSlot = E_equimentSlots::Count;
		return;
	}

	// Early return if the previous line is empty, 
	// because iterations means that iterations is a new item.
	if (previousLine.empty())
	{
		return;
	}

	if (IsThisStringInLine(NAME))
	{
		RemoveStringFromString(NAME);
		RemoveRawStrings();
		RemoveExtraLengthFromString(NAME);
		name = *m_line;
		return;
	}

	if (IsThisStringInLine(COST))
	{
		RemoveStringFromString(COST);
		RemoveRawStrings();
		RemoveExtraLengthFromString(COST);
		cost = stoi(*m_line);
		return;
	}

	if (IsThisStringInLine(STACKS))
	{
		RemoveStringFromString(STACKS);
		RemoveRawStrings();
		RemoveExtraLengthFromString(STACKS);
		stacks = stoi(*m_line);
		return;
	}

	if (IsThisStringInLine(CURRENT_DURABILITY))
	{
		RemoveStringFromString(CURRENT_DURABILITY);
		RemoveRawStrings();
		RemoveExtraLengthFromString(CURRENT_DURABILITY);
		currentDurability = stoi(*m_line);
		return;
	}

	if (IsThisStringInLine(MAX_DURABILITY))
	{
		RemoveStringFromString(MAX_DURABILITY);
		RemoveRawStrings();
		RemoveExtraLengthFromString(MAX_DURABILITY);
		maxDurability = stoi(*m_line);
		return;
	}

	if (IsThisStringInLine(EQUIPMENT_SLOT))
	{
		RemoveStringFromString(EQUIPMENT_SLOT);
		RemoveRawStrings();
		RemoveExtraLengthFromString(EQUIPMENT_SLOT);
		equipmentSlot = StringToE_equimentSlots();
		return;
	}

}

E_equimentSlots FileManager::StringToE_equimentSlots()
{
	if (IsThisStringInLine("Head"))
	{
		return E_equimentSlots::Head;
	}
	else if (IsThisStringInLine("Chest"))
	{
		return E_equimentSlots::Chest;
	}
	else if (IsThisStringInLine("Legs"))
	{
		return E_equimentSlots::Legs;
	}
	else if (IsThisStringInLine("Weapon1"))
	{
		return E_equimentSlots::Weapon1;
	}
	else if (IsThisStringInLine("Weapon2"))
	{
		return E_equimentSlots::Weapon2;
	}
	else
	{
		cout << endl << "Error in E_equimentSlots FileManager::StringToEnum() : Invalid slot!";
		return E_equimentSlots::Count;
	}
}

E_itemType FileManager::StringToE_itemType(string* previousLine)
{
	if (IsThisStringInPreviousLine("BaseObject", previousLine))
	{
		return E_itemType::BaseObject;
	}
	else if (IsThisStringInPreviousLine("Consumable", previousLine))
	{
		return E_itemType::Consumable;
	}
	else if (IsThisStringInPreviousLine("Equipment", previousLine))
	{
		return E_itemType::Equipment;
	}
	else
	{
		cout << endl << "Error in E_itemType FileManager::StringToEnum() : Invalid slot!";
		return E_itemType::Count;
	}
}

string FileManager::EnumToString(E_equimentSlots* slot)
{
	switch (*slot)
	{
	case E_equimentSlots::Head:
		return "Head";
		break;

	case E_equimentSlots::Chest:
		return "Chest";
		break;

	case E_equimentSlots::Legs:
		return "Legs";
		break;

	case E_equimentSlots::Weapon1:
		return "Weapon1";
		break;

	case E_equimentSlots::Weapon2:
		return "Weapon2";
		break;

	case E_equimentSlots::Count:
	default:
		cout << endl << "Error in FileManager::EnumToString(E_equimentSlots* slot) : Invalid slot!";
		return "";
		break;
	}
}

string FileManager::EnumToString(E_itemType* slot)
{
	switch (*slot)
	{
	case E_itemType::BaseObject:
		return "BaseObject";
		break;

	case E_itemType::Consumable:
		return "Consumable";
		break;

	case E_itemType::Equipment:
		return "Equipment";
		break;

	case E_itemType::Count:
	default:
		cout << endl << "Error in FileManager::EnumToString(E_itemType* slot) : Invalid slot!";
		return "";
		break;
	}
}

void FileManager::RemoveDoubleSpaces()
{
	// Source : https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
	// Source : https://stackoverflow.com/questions/48029688/how-to-remove-all-double-spaces-from-string
	size_t doubleSpace = m_line->find("  ");

	// While there are double spaces, remove them until the end of string 
	// (npos is the greatest possible value for an element of type size_t)
	// Source : https://cplusplus.com/reference/string/string/npos/
	while (doubleSpace != string::npos)
	{
		m_line->erase(doubleSpace, 1);
		doubleSpace = m_line->find("  ");
	}
}

// To only use afte a RemoveDoubleSpaces() to check if uneven spaces are still there.
void FileManager::RemoveSpaceInFront()
{
	// isspace() does not work well with pointers 
	if (m_line[0] == " ")
	{
		// Shift all characters to the left by one
		ShiftCharsToLeftInLine(0);

		// Remove the last extra character
		m_line->pop_back();
	}
}

void FileManager::RemoveSpaceInMiddle()
{
	// If there is a lonely space between a colon and a character
	for (size_t i = 0; i < m_line->length() - 1; i++)
	{
		// Source : https://stackoverflow.com/questions/30457813/varn-what-does-iterations-mean-in-c
		// isspace() does not work well with pointers 
		auto linei = (*m_line)[i]; // TODO : Remove after debug
		auto linei1 = (*m_line)[i + 1]; // TODO : Remove after debug

		// If the element is not out of range and there is a space before a colon
		if (i > 0 && (*m_line)[i - 1] == ' ' && (*m_line)[i] == ':')
		{
			// Shift all characters to the left by one to remove the space
			ShiftCharsToLeftInLine(i - 1);
		}

		// If there is a space after a colon
		if ((*m_line)[i] == ':' && (*m_line)[i + 1] == ' ')
		{
			// Shift all characters to the left by one to remove the space
			ShiftCharsToLeftInLine(i + 1);
			break;
		}
	}
}

void FileManager::RemoveSpaceInBack()
{
	// If there is a lonely space at the end of the (non-empty) string
	if (!m_line->empty() && (isspace(m_line->back()) || m_line->back() == ' ')) // Double check because isspace() does not work well with pointers 
	{
		// Remove the last character from memory
		m_line->pop_back();
	}
}

void FileManager::RemoveRawStrings()
{
	// Source : https://learn.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-170
	//const char* rawStrings[12] = { '\n', '\r', '\t', '\v', '\f', '\b', '\a', '\\', '\?' , '\'', '\"', '\0'}; // TODO : Remove after debug

	size_t rawStringsLength = sizeof(rawStrings) / sizeof(rawStrings[0]);
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

	for (size_t i = 0; i < m_line->length(); i++)
	{
		for (size_t j = i + 1; j < rawStringsLength; j++)
		{
			auto stringi = (*m_line)[i];// TODO : Remove after debug
			auto rawStr = *rawStrings[j];// TODO : Remove after debug

			if ((*m_line)[i] == *rawStrings[j])
			{
				ShiftCharsToLeftInLine(i);
				j = 0;
			}
		}
		break;
	}
}

void FileManager::RemoveStringFromString(const char* STRING_TO_REMOVE)
{
	unsigned short int strToRemLength = ConstCharSize(STRING_TO_REMOVE);
	// For chars in line that are not chars in CHAR_TO_REMOVE 
	// move CHAR_TO_REMOVE characters to the beginning of the string
	for (size_t i = 0; i < m_line->length(); i++)
	{
		for (size_t j = i; j < ConstCharSize(STRING_TO_REMOVE); j++)
		{
			// If the first characters fits for both line and CHAR_TO_REMOVE
			// Source : https://stackoverflow.com/questions/30457813/varn-what-does-iterations-mean-in-c
			if ((*m_line)[i] != STRING_TO_REMOVE[j])
			{
				continue;
			}

			if (!IsThisStringThisString(STRING_TO_REMOVE, j, i))
			{
				continue;
			}

			// Shift all characters to the begginig of the string
			ShiftCharsToStartOfString(STRING_TO_REMOVE, j);
			break;
		}
		break;
	}
}

void FileManager::RemoveExtraLengthFromString(const char* CHAR_TO_REMOVE)
{
	// Source : https://stackoverflow.com/questions/74150327/string-size-returns-1-too-large-value-in-evaluation-system

	// "Hello World!\r\n" Windows string have two encoded raw strings at the end. 
	unsigned short const int ENCODED_RAW_STRINGS = 2;
	size_t lineLength = m_line->length();// TODO : Remove after debug
	size_t stringLength = ConstCharSize(CHAR_TO_REMOVE);// TODO : Remove after debug
	size_t leanghtToRemain = (lineLength - stringLength) - ENCODED_RAW_STRINGS;
	auto lineDifference = lineLength - stringLength;// TODO : Remove after debug

	// For the remaining characters in the string, remove them from memory
	for (size_t i = lineLength; i > 0; i--)
	{
		// If the last element is not the length of the string, that is
		// the object's name (or not the difference between the line and the string)
		if (i != lineDifference)
		{
			// Remove the last character from memory
			m_line->pop_back();
		}
		else
		{
			break;
		}
	}
}


// isspace does not work well with pointers
bool FileManager::IsLineEmpty()
{
	bool isLineEmpty = m_line->empty();// TODO : Remove after debug
	auto* emptyString = "";// TODO : Remove after debug
	bool isEmptyLine = (*m_line == "");// TODO : Remove after debug 
	bool isEmptyLineString = (*m_line == emptyString);// TODO : Remove after debug 

	// If the line is empty, remove iterations from memory
	//if (isspace(*m_line->c_str())) // TODO : Remove after debug
	//{
	//	return true;
	//}

	if (*m_line == "")
	{
		return true;
	}

	if (m_line->empty())
	{
		return true;
	}

	if (isLineEmpty)
	{
		return true;
	}

	if (*m_line == emptyString)
	{
		return true;
	}

	if (isEmptyLineString)
	{
		return true;
	}

	if (isEmptyLine)
	{
		return true;
	}

	return false;
}

bool FileManager::IsLineSingleRawString()
{
	auto lineLength = m_line->length();// TODO : Remove after debug

	// If the line is not a single char string, return false
	if (m_line->length() != 1)
	{
		return false;
	}

	for (size_t i = 0; i < m_line->length(); i++)
	{
		for (size_t j = i + 1; j < sizeof(rawStrings) / sizeof(rawStrings[0]); j++)
		{
			auto stringi = (*m_line)[i];// TODO : Remove after debug
			auto rawStr = *rawStrings[j];// TODO : Remove after debug

			// If it finds a raw string in the line, return true
			if ((*m_line)[i] == *rawStrings[j])
			{
				return true;
			}
		}
	}
	return false;
}

// Verify if the given string is in m_line
bool FileManager::IsThisStringInLine(const char* word)
{
	// Source : https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
	// Convert string* to const char* to compare iterations to the line pointer
	const char* lineChar = m_line->c_str();// TODO : Remove after debug
	auto sixe = ConstCharSize(word); // TODO : Remove after debug

	for (size_t i = 0; i < ConstCharSize(word); i++)
	{
		for (size_t j = i; j < m_line->length(); j++)
		{
			auto linezero = lineChar[j]; // TODO : Remove after debug
			auto lineone = lineChar[j + 1]; // TODO : Remove after debug

			auto wordzero = word[i]; // TODO : Remove after debug
			auto wordone = word[i + 1]; // TODO : Remove after debug

			// If iterations reaches the end of the string, return false
			if (m_line->c_str()[j + ConstCharSize(word) - 1] == '\0')
			{
				return false;
			}

			// As long as the characters are not the same, continue
			if (m_line->c_str()[j] != word[i])
			{
				continue;
			}

			// Once they are the same,
			// check if the rest of the elements fits for both line and word
			if (IsThisStringThisString(word, i, j))
			{
				return true;
			}
		}
	}
	return false;
}

bool FileManager::IsThisStringInPreviousLine(const char* word, string* previousLine)
{
	// Source : https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
	// Convert string* to const char* to compare iterations to the line pointer

	auto sixe = ConstCharSize(word); // TODO : Remove after debug

	for (size_t i = 0; i < ConstCharSize(word); i++)
	{
		for (size_t j = i; j < previousLine->length(); j++)
		{

			auto wordzero = word[i]; // TODO : Remove after debug
			auto wordone = word[i + 1]; // TODO : Remove after debug

			auto prevLineMinusOne = previousLine->c_str()[j + ConstCharSize(word) - 1]; // TODO : Remove after debug
			auto prevLinej = previousLine->c_str()[j]; // TODO : Remove after debug

			// If iterations reaches the end of the string, return false
			if (previousLine->c_str()[j + ConstCharSize(word) - 1] == '\0')
			{
				return false;
			}

			// As long as the characters are not the same, continue
			if (previousLine->c_str()[j] != word[i])
			{
				continue;
			}

			// Once they are the same,
			// check if the rest of the elements fits for both line and word
			if (IsThisStringPreviousLine(word, previousLine, i, j))
			{
				return true;
			}
		}
	}
	return false;
}

// Verify if the given string is the string in m_line by comparing their char positions at specific elements(indexes)
bool FileManager::IsThisStringThisString(const char* word, size_t wordIndex, size_t lineIndex)
{
	for (size_t i = 0; i < ConstCharSize(word); i++)
	{
		if (m_line->c_str()[lineIndex + i] == word[wordIndex + i])
		{
			continue;
		}
		else
		{
			return false;
		}

	}
	return true;
}

bool FileManager::IsThisStringPreviousLine(const char* word, string* previousLine, size_t wordIndex, size_t lineIndex)
{
	for (size_t i = 0; i < ConstCharSize(word); i++)
	{
		if (previousLine->c_str()[lineIndex + i] == word[wordIndex + i])
		{
			continue;
		}
		else
		{
			return false;
		}

	}
	return true;
}

void FileManager::ShiftCharsToLeftInLine(size_t index)
{
	// Shift all characters to the left by one
	for (size_t i = index; i < m_line->length() - 1; i++)
	{
		(*m_line)[i] = (*m_line)[i + 1];

		// Remove the last character from memory
		if (i >= m_line->length() - 2)
		{
			m_line->pop_back();
		}
	}
}

void FileManager::ShiftCharsToStartOfString(const char* STRING_TO_MOVE, size_t j)
{
	auto lineLength = m_line->length();// TODO : Remove after debug
	auto stringLength = ConstCharSize(STRING_TO_MOVE);// TODO : Remove after debug
	auto lineDifference = lineLength - stringLength;// TODO : Remove after debug
	// Shift all characters to the begginig of the string
	for (size_t i = j; i < m_line->length() - (ConstCharSize(STRING_TO_MOVE)); i++)
	{
		auto linei = (*m_line)[i]; // TODO : Remove after debug
		auto lineToMove = (*m_line)[i + ConstCharSize(STRING_TO_MOVE)]; // TODO : Remove after debug
		(*m_line)[i] = (*m_line)[i + ConstCharSize(STRING_TO_MOVE)];
	}
}

// Source : https://stackoverflow.com/questions/72124875/number-of-elements-in-const-char-array
unsigned short int FileManager::ConstCharSize(const char* a)
{
	unsigned short int iterations = 0;
	while (a[iterations] != '\0')
	{
		++iterations;
	}

	return iterations;
}