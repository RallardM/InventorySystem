#pragma once

enum class E_equimentSlots : unsigned short int
{
	Head,
	Chest,
	Legs,
	Weapon1,
	Weapon2,
	Count
};

enum class E_itemType : unsigned short int
{
	BaseObject,
	Consumable,
	Equipment,
	Count
};

enum class E_inputMode : unsigned short int
{
	Navigation,
	Edition,
	Count
};