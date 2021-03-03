class WeaponSystem;
class CUnknown;
class PlayerHealth;
class PlayerPosData;
class PlayerCount;
class ANet_player;

int Dec(int i)
{
	return i / 4;
}
class WeaponSystem
{
public:
	CUnknown* m_Unknown; //0x0000 
	char pad_0x0004[0x4]; //0x0004
	__int32 bilmem; //0x0008 
	__int32 _bilmem; //0x000C 
	char pad_0x0010[0x20]; //0x0010
	__int32 unkn_degisken; //0x0030 
	char pad_0x0034[0x2C]; //0x0034
	__int32 wp1ammo; //0x0060 
	__int32 gunammo; //0x0064 
	__int32 knife; //0x0068 
	__int32 bomb_count; //0x006C 
	char pad_0x0070[0x8]; //0x0070
	__int32 wp1ammo_max; //0x0078 
	__int32 gunammo_max; //0x007C 
	__int32 knife_m; //0x0080 
	__int32 bomb_count_max; //0x0084 
	char pad_0x0088[0x8]; //0x0088
	__int32 wp1_mgznmax; //0x0090 
	__int32 gun_mgznmax; //0x0094 
	char pad_0x0098[0x10]; //0x0098
	__int32 wp1_mgzn; //0x00A8 
	__int32 gun_mgzn; //0x00AC 
	char pad_0x00B0[0x30]; //0x00B0
	__int32 isAimAt; //0x00E0 
	__int32 isAimAt_1; //0x00E4 
	char pad_0x00E8[0x358]; //0x00E8
}; //Size=0x00E0

class CUnknown
{
public:
	char pad_0x0000[0x10]; //0x0000
}; //Size=0x0010

class PlayerHealth
{
public:
	char pad_0x0000[0x100]; //0x0000
	__int32 Health; //0x0100 
	char pad_0x0104[0x94]; //0x0104
	__int32 MaxHealth; //0x0198 
}; //Size=0x019C

class PlayerPosData
{
public:
	char pad_0x0000[0x778]; //0x0000
	__int32 msx; //0x0778 
	__int32 msy; //0x077C 
	__int32 msz; //0x0780 
	char pad_0x0784[0x4]; //0x0784
	__int32 myposx; //0x0788 
	__int32 myposy; //0x078C 
	__int32 myposz; //0x0790 
	char pad_0x0794[0xAC]; //0x0794
}; //Size=0x0840

class ANet_player
{
public:
	__int32 inGame; //0x0000 
	char pad_0x0004[0x114]; //0x0004
	__int32 PlayerCount; //0x0118 
	char pad_0x011C[0x10]; //0x011C
};

namespace MyTable
{
	WeaponSystem* mWeaponSystem = NULL;
	CUnknown* mCUnknown = NULL;
	PlayerHealth* mPlayerHealth = NULL;
	PlayerPosData* mPlayerPosData = NULL;
	ANet_player* mANet_Player = NULL;
	//InGameControl* mInGameControl = NULL;
};
using namespace MyTable;

namespace __myoffs
{
	DWORD MemBaseAddr = (DWORD)GetModuleHandleA(/*acknex.dll*/XorStr<0x29, 11, 0xAB8B2B8C>("\x48\x49\x40\x42\x48\x56\x01\x54\x5D\x5E" + 0xAB8B2B8C).s) + 0x215580;
	DWORD PlayerCountAddr = (DWORD)GetModuleHandleA(/*ANet.dll*/XorStr<0x82, 9, 0x93D758E7>("\xC3\xCD\xE1\xF1\xA8\xE3\xE4\xE5" + 0x93D758E7).s) + 0x307EC;

	int CheckEnemyOffset = 0x01816930;
	int PlayerSystemOffset = 0x187CBB5;

	/*---------# No Recoil #---------*/

	char norec_bytes[] = "\x89\x83\xB0\xD2\x87\x01\x8B\x85\x50\x00\x00\x00\x89\x83\xB4\xD2\x87\x01\x8B\x85\x50\x00\x00\x00\x50\x8B\x83\x88";
	char norec2_bytes[] = "\x89\x83\xB0\xD2\x87\x01\x8B\x85\x50\x00\x00\x00\x89\x83\xB4\xD2\x87\x01\x8B\x85\x50\x00\x00\x00\x50\x8B\x83\x08";
	char norec_mask[] = "xxxxxxxxx???xxxxxxxxx???xxxx";

	/*---------# No Spread #---------*/
	char nospread_bytes[] = "\xDB\x83\xB4\xD2\x87\x01";//Db 83 b4 d2 87 01
	char nospread_mask[] = "xxxxxx";

	/*---------# Sniper Rapid #---------*/
	char sniper_rapid[] = "\x8B\x85\x60\x08\x00\x00\x89\x83\x50\xD3\x87\x01"; // + 0x6
	char sniper_rapid_mask[] = "xxxx??xxxxxx";

	/*---------# Gun Rapid #---------*/
	char gun_rapid[] = "\x8B\x85\x64\x08\x00\x00\x89\x83\x50\xD3\x87\x01"; // + 0x6
	char gun_rapid_mask[] = "xxxx??xxxxxx";
};