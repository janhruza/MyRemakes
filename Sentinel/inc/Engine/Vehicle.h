#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include <wtypes.h>

// TODO add values
typedef enum tagVehicleClass
{
	VC_RESERVED = 0, // first, must be reserved
	VC_SEDAN,
	VC_UTILITY,

	VC_LAST // must be last, reserved

} VEHICLE_CLASS;

// TODO add values
typedef enum tagVehicleManufacturer
{
	VB_FIRST = 0, // first, must be reserved
	VB_LAST // last, must be reserved
} VEHICLE_BRAND;

// TODO add members
typedef struct tagVehicle
{
	UINT Id;
	VEHICLE_CLASS Class;
	VEHICLE_BRAND Manufacturer;

} Vehicle, *PVehicle, *VehiclePtr;

#endif