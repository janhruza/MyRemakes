#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <wtypes.h>

typedef struct TagWeapon
{
	UINT Id;
	UINT Capacity;
	UINT MaxAmmo;

} Weapon, *PWeapon, *WeaponPtr;

#endif