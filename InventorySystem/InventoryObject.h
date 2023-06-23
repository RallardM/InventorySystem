#pragma once
#include <string>

using namespace std;

class InventoryObject
{
	//Methods
public:
	InventoryObject(string type, string name, int cost = 0);
	string ToString();
private:

	//Member variables
public:
private:
	enum e_equimentSlots
	{
		HEAD,
		CHEST,
		LEGS,
		WEAPON1,
		WEAPON2,
		COUNT
	};
	string m_name = "nameless object";
	string m_type = "nameless type";
	unsigned short int m_cost = 0;
	unsigned short int m_stackSize = 0;
	unsigned short int m_currentDurability = 0;
	unsigned short int m_maxDurability = 0;

};