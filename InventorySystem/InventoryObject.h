#pragma once
#include <string>

#include "Enumerations.h"

using namespace std;

class InventoryObject
{
	//Methods
public:
	InventoryObject(
	string type, 
	string name, 
	unsigned short int cost, 
	unsigned short int currentDurability = 0, 
	unsigned short int maxDurability = 0, 
	E_equimentSlots slot = E_equimentSlots::COUNT);

	string ToString();
private:

	//Member variables
public:


private:
	string m_name = "nameless object";
	string m_type = "nameless type";
	unsigned short int m_cost = 0;
	unsigned short int m_stackSize = 0;
	unsigned short int m_currentDurability = 0;
	unsigned short int m_maxDurability = 0;
	E_equimentSlots m_equipmentSlot = E_equimentSlots::COUNT;

};