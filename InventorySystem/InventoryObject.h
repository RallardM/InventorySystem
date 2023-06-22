#pragma once
#include <string>

using namespace std;

class InventoryObject
{
//Methods
public:
	InventoryObject(string name, int cost = 0);
	string ToString();

//Member variables
private:
	string m_name = "nameless object";

	int m_cost = 0;
};