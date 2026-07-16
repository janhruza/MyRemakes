#include "..\inc\Globals.h"
#include "..\res\resource.h"

DatabasePtr gDatabase = NULL;
PConfig gConfig = NULL;

CrimeInfo gCrimes[MAX_CRIMES] = { 0 };
WCHAR* gCountries[MAX_COUNTRIES] = { 0 };

WCHAR* gWeaponNames[W_COUNT] =
{
	L"Unknown",

	// MELEE
	L"Knife",
	L"Nightstick",
	L"Hammer",
	L"Bat",
	L"Golf Club",
	L"Crowbar",
	L"Machete",
	L"Switchblade",
	L"Battleaxe",
	L"Stone Hatchet",

	// HANDGUNS
	L"Pistol",
	L"Pistol Mk II",
	L"Combat Pistol",
	L"AP Pistol",
	L"Stun Gun",
	L"Pistol .50",
	L"SNS Pistol",
	L"SNS Pistol Mk II",
	L"Heavy Pistol",
	L"Vintage Pistol",
	L"Marksman Pistol",
	L"Revolver",
	L"Revolver Mk II",
	L"Up-n-Atomizer",

	// SMG
	L"Micro SMG",
	L"SMG",
	L"SMG Mk II",
	L"Assault SMG",
	L"Combat PDW",
	L"Machine Pistol",
	L"Mini SMG",
	L"Tactical SMG",

	// SHOTGUNS
	L"Pump Shotgun",
	L"Pump Shotgun Mk II",
	L"Sawed-Off Shotgun",
	L"Assault Shotgun",
	L"Bullpup Shotgun",
	L"Heavy Shotgun",
	L"Double Barrel Shotgun",
	L"Sweeper Shotgun",

	// RIFLES
	L"Assault Rifle",
	L"Assault Rifle Mk II",
	L"Carbine Rifle",
	L"Carbine Rifle Mk II",
	L"Advanced Rifle",
	L"Special Carbine",
	L"Special Carbine Mk II",
	L"Bullpup Rifle",
	L"Bullpup Rifle Mk II",
	L"Compact Rifle",
	L"Military Rifle",
	L"Heavy Rifle",
	L"Service Rifle",

	// MG
	L"MG",
	L"Combat MG",
	L"Combat MG Mk II",
	L"Gusenberg",

	// SNIPER
	L"Sniper Rifle",
	L"Heavy Sniper",
	L"Heavy Sniper Mk II",
	L"Marksman Rifle",
	L"Marksman Rifle Mk II",
	L"Precision Rifle",

	// HEAVY
	L"RPG",
	L"Grenade Launcher",
	L"Minigun",
	L"Firework Launcher",
	L"Homing Launcher",
	L"Railgun",
	L"Compact Launcher",
	L"Widowmaker",

	// THROWN
	L"Grenade",
	L"Sticky Bomb",
	L"Proximity Mine",
	L"Molotov",
	L"Teargas",
	L"Pipe Bomb"
};

const Weapon gWeapons[MAX_WEAPONS] =
{
	{ W_FIRST, WPT_FIRST, 0, 0 },

	// MELEE
	{ W_KNIFE, WPT_MELEE, 1, 1 },
	{ W_NIGHTSTICK, WPT_MELEE, 1, 1 },
	{ W_HAMMER, WPT_MELEE, 1, 1 },
	{ W_BAT, WPT_MELEE, 1, 1 },
	{ W_GOLFCLUB, WPT_MELEE, 1, 1 },
	{ W_CROWBAR, WPT_MELEE, 1, 1 },
	{ W_MACHETE, WPT_MELEE, 1, 1 },
	{ W_SWITCHBLADE, WPT_MELEE, 1, 1 },
	{ W_BATTLEAXE, WPT_MELEE, 1, 1 },
	{ W_STONE_HATCHET, WPT_MELEE, 1, 1 },

	// HANDGUNS
	{ W_PISTOL, WPT_HANDGUN, 12, 9999 },
	{ W_PISTOL2, WPT_HANDGUN, 12, 9999 }, // Mk II
	{ W_COMBAT_PISTOL, WPT_HANDGUN, 12, 9999 },
	{ W_AP_PISTOL, WPT_HANDGUN, 18, 9999 },
	{ W_STUN_GUN, WPT_HANDGUN, 1, 1 },
	{ W_PISTOL50, WPT_HANDGUN, 9, 9999 },
	{ W_SNS_PISTOL, WPT_HANDGUN, 6, 9999 },
	{ W_SNS_PISTOL2, WPT_HANDGUN, 6, 9999 }, // Mk II
	{ W_HEAVY_PISTOL, WPT_HANDGUN, 18, 9999 },
	{ W_VINTAGE_PISTOL, WPT_HANDGUN, 7, 9999 },
	{ W_MARKSMAN_PISTOL, WPT_HANDGUN, 1, 9999 },
	{ W_REVOLVER, WPT_HANDGUN, 6, 9999 },
	{ W_REVOLVER2, WPT_HANDGUN, 6, 9999 }, // Mk II
	{ W_UP_N_ATOMIZER, WPT_HANDGUN, 1, 1 },

	// SMG
	{ W_MICRO_SMG, WPT_SMG, 16, 9999 },
	{ W_SMG, WPT_SMG, 30, 9999 },
	{ W_SMG2, WPT_SMG, 30, 9999 }, // Mk II
	{ W_ASSAULT_SMG, WPT_SMG, 30, 9999 },
	{ W_COMBAT_PDW, WPT_SMG, 30, 9999 },
	{ W_MACHINE_PISTOL, WPT_SMG, 12, 9999 },
	{ W_MINI_SMG, WPT_SMG, 20, 9999 },
	{ W_TACTICAL_SMG, WPT_SMG, 30, 9999 },

	// SHOTGUNS
	{ W_PUMP_SHOTGUN, WPT_SHOTGUN, 8, 250 },
	{ W_PUMP_SHOTGUN2, WPT_SHOTGUN, 8, 250 }, // Mk II
	{ W_SAWEDOFF_SHOTGUN, WPT_SHOTGUN, 8, 250 },
	{ W_ASSAULT_SHOTGUN, WPT_SHOTGUN, 8, 250 },
	{ W_BULLPUP_SHOTGUN, WPT_SHOTGUN, 14, 250 },
	{ W_HEAVY_SHOTGUN, WPT_SHOTGUN, 6, 250 },
	{ W_DOUBLEBARREL_SHOTGUN, WPT_SHOTGUN, 2, 250 },
	{ W_SWEEPER_SHOTGUN, WPT_SHOTGUN, 10, 250 },

	// RIFLES
	{ W_ASSAULT_RIFLE, WPT_RIFLE, 30, 9999 },
	{ W_ASSAULT_RIFLE2, WPT_RIFLE, 30, 9999 }, // Mk II
	{ W_CARBINE_RIFLE, WPT_RIFLE, 30, 9999 },
	{ W_CARBINE_RIFLE2, WPT_RIFLE, 30, 9999 }, // Mk II
	{ W_ADVANCED_RIFLE, WPT_RIFLE, 30, 9999 },
	{ W_SPECIAL_CARBINE, WPT_RIFLE, 30, 9999 },
	{ W_SPECIAL_CARBINE2, WPT_RIFLE, 30, 9999 }, // Mk II
	{ W_BULLPUP_RIFLE, WPT_RIFLE, 30, 9999 },
	{ W_BULLPUP_RIFLE2, WPT_RIFLE, 30, 9999 }, // Mk II
	{ W_COMPACT_RIFLE, WPT_RIFLE, 30, 9999 },
	{ W_MILITARY_RIFLE, WPT_RIFLE, 30, 9999 },
	{ W_HEAVY_RIFLE, WPT_RIFLE, 30, 9999 },
	{ W_SERVICE_RIFLE, WPT_RIFLE, 30, 9999 },

	// MG
	{ W_MG, WPT_MG, 54, 9999 },
	{ W_COMBAT_MG, WPT_MG, 100, 9999 },
	{ W_COMBAT_MG2, WPT_MG, 100, 9999 }, // Mk II
	{ W_GUSENBERG, WPT_MG, 50, 9999 },

	// SNIPER
	{ W_SNIPER_RIFLE, WPT_SNIPER, 10, 9999 },
	{ W_HEAVY_SNIPER, WPT_SNIPER, 6, 9999 },
	{ W_HEAVY_SNIPER2, WPT_SNIPER, 6, 9999 }, // Mk II
	{ W_MARKSMAN_RIFLE, WPT_SNIPER, 8, 9999 },
	{ W_MARKSMAN_RIFLE2, WPT_SNIPER, 8, 9999 }, // Mk II
	{ W_PRECISION_RIFLE, WPT_SNIPER, 10, 9999 },

	// HEAVY
	{ W_RPG, WPT_HEAVY, 1, 20 },
	{ W_GRENADE_LAUNCHER, WPT_HEAVY, 10, 20 },
	{ W_MINIGUN, WPT_HEAVY, 9999, 9999 }, // Má rovnou plnou kapacitu v zásobníku
	{ W_FIREWORK_LAUNCHER, WPT_HEAVY, 1, 20 },
	{ W_HOMING_LAUNCHER, WPT_HEAVY, 1, 10 },
	{ W_RAILGUN, WPT_HEAVY, 1, 20 },
	{ W_COMPACT_LAUNCHER, WPT_HEAVY, 1, 20 },
	{ W_WIDOWMAKER, WPT_HEAVY, 9999, 9999 },

	// THROWN
	{ W_GRENADE, WPT_THROWN, 1, 25 },
	{ W_STICKY_BOMB, WPT_THROWN, 1, 25 },
	{ W_PROXIMITY_MINE, WPT_THROWN, 1, 5 },
	{ W_MOLOTOV, WPT_THROWN, 1, 25 },
	{ W_TEARGAS, WPT_THROWN, 1, 25 },
	{ W_PIPEBOMB, WPT_THROWN, 1, 25 }
};

const WCHAR* gVehicleBrands[VB_LAST] =
{
	L"Albany",
	L"Annis",
	L"Benefactor",
	L"BF",
	L"Bravado",
	L"Brute",
	L"Buckingham",
	L"Canis",
	L"Declasse",
	L"Dewbauchee",
	L"Dinka",
	L"Dundreary",
	L"Enus",
	L"Fathom",
	L"Galliwanter",
	L"Grotti",
	L"Hijak",
	L"Imponte",
	L"Invetero",
	L"Karin",
	L"Lampadati",
	L"Maibatsu",
	L"Mammoth",
	L"MTL",
	L"Obey",
	L"Ocelot",
	L"Overflod",
	L"Pegassi",
	L"Pfister",
	L"Principe",
	L"Progen",
	L"Rune",
	L"Schyster",
	L"Shitzu",
	L"Truffade",
	L"Ubermacht",
	L"Vapid",
	L"Vulcar",
	L"Weeny",
	L"Western",
	L"Zirconium"
};

const WCHAR* gVehicleClasses[VC_LAST] = {
	L"Boats",
	L"Commercial",
	L"Compacts",
	L"Coupes",
	L"Cycles",
	L"Emergency",
	L"Helicopters",
	L"Industrial",
	L"Military",
	L"Motorcycles",
	L"Muscle",
	L"Off Road",
	L"Open Wheel",
	L"Planes",
	L"Sedans",
	L"Service",
	L"Sports",
	L"Sports Classics",
	L"Super",
	L"SUV's",
	L"Utility",
	L"Vans"
};

BOOL GlobSetDbPtr(PDatabase ptr)
{
	gDatabase = ptr;
	return TRUE;
}

DatabasePtr GlobGetDbPtr(void)
{
	return gDatabase;
}

BOOL GlobSetConfigPtr(PConfig ptr)
{
	gConfig = ptr;
	return TRUE;
}

PConfig GlobGetConfigPtr(void)
{
	return gConfig;
}

#pragma region Cutom control handles

HWND gCtlLanding = NULL;
HWND gCtlPersons = NULL;
HWND gCtlVehicles = NULL;
HWND gCtlWeapons = NULL;
HWND gCtlCrimes = NULL;

#pragma endregion