#include "MemoryAccess.h"

#include <string>

int MemEdit::getMana(std::string* manaWrite)
{
	int mana = 0;
	ReadProcessMemory(processHandle, (LPCVOID)manaAddress, &mana, sizeof(mana), nullptr);
	*manaWrite = "Mana: " + std::to_string(mana);

	return 0;
}

int MemEdit::getManaInt(int* manaWrite)
{
	int mana = 0;
	ReadProcessMemory(processHandle, (LPCVOID)manaAddress, &mana, sizeof(mana), nullptr);
	*manaWrite = mana;
	return 0;
}

int MemEdit::getHp(std::string* hpWrite)
{
	int hp = 0;
	ReadProcessMemory(processHandle, (LPCVOID)hpAddress, &hp, sizeof(hp), nullptr);
	*hpWrite = "HP: " + std::to_string(hp);
	return 0;
}

int MemEdit::getHpInt(int* hpWrite)
{
	int hp = 0;
	ReadProcessMemory(processHandle, (LPCVOID)hpAddress, &hp, sizeof(hp), nullptr);
	*hpWrite = hp;
	return 0;
}

int MemEdit::getDefense(std::string* def)
{
	int defence = 0;
	ReadProcessMemory(processHandle, (LPCVOID)defenceAddress, &defence, sizeof(defence), nullptr);
	*def = "Def: " + std::to_string(defence);
	return 0;
}

int MemEdit::getLifeRegen(std::string* lifeRegen)
{
	int regen = 0;
	ReadProcessMemory(processHandle, (LPCVOID)lifeRegenAddress, &regen, sizeof(regen), nullptr);
	*lifeRegen = "Regen: " + std::to_string(regen);
	return 0;
}

int MemEdit::getXCoords(std::string* xCoords)
{
	float x = 0;
	ReadProcessMemory(processHandle, (LPCVOID)xCoordsAddress, &x, sizeof(x), nullptr);
	*xCoords = "X: " + std::to_string(x);
	return 0;

}

int MemEdit::getYCoords(std::string* yCoords)
{
	float y = 0;
	ReadProcessMemory(processHandle, (LPCVOID)yCoordsAddress, &y, sizeof(y), nullptr);
	*yCoords = "Y: " + std::to_string(y);
	return 0;
}

int MemEdit::setSlotElevenType(int newType)
{
	int setType = newType;
	uintptr_t typeAddy = GetPointerChainAddress(sl11TypeOffsets, processHandle, gamebaseQ);
	WriteProcessMemory(processHandle, (LPVOID)typeAddy, &setType, sizeof(setType), nullptr);
	return 0;
}

int MemEdit::setSlotElevenNetID(int newNetId)
{
	int setNetId = newNetId;
	uintptr_t NetIdAddy = GetPointerChainAddress(sl11NetIdOffsets, processHandle, gamebaseQ);
	WriteProcessMemory(processHandle, (LPVOID)NetIdAddy, &setNetId, sizeof(setNetId), nullptr);
	return 0;
}

int MemEdit::setSlotElevenAmount(int newAmnt)
{

	int setAmnt = newAmnt;
	uintptr_t amntAddy = GetPointerChainAddress(sl11AmntOffsets, processHandle, gamebaseQ);
	WriteProcessMemory(processHandle, (LPVOID)amntAddy, &setAmnt, sizeof(setAmnt), nullptr);
	return 0;
}

void MemEdit::setGhost(int ghostValue)
{
	int ghost = ghostValue;
	WriteProcessMemory(processHandle, (LPVOID)ghostAddress, &ghost, sizeof(ghost), nullptr);
}

void MemEdit::setTpPoint(float* posX, float* posY)
{
	float x = 0;
	ReadProcessMemory(processHandle, (LPCVOID)xCoordsAddress, &x, sizeof(x), nullptr);
	*posX = x;

	float y = 0;
	ReadProcessMemory(processHandle, (LPCVOID)yCoordsAddress, &y, sizeof(y), nullptr);
	*posY = y;
}

void MemEdit::tpToPoint(float X, float Y)
{
	float xCoords = X;
	float yCoords = Y;
	WriteProcessMemory(processHandle, (LPVOID)xCoordsAddress, &xCoords, sizeof(xCoords), nullptr);
	WriteProcessMemory(processHandle, (LPVOID)yCoordsAddress, &yCoords, sizeof(yCoords), nullptr);
}


MemEdit::MemEdit()
{
	using namespace std;

	HWND hGameWindow = FindWindow(L"SDL_app", nullptr);

	DWORD pID = NULL; // Game ID
	GetWindowThreadProcessId(hGameWindow, &pID);
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	uintptr_t dllBaseAddress = dwGetModuleBaseAddress(pID, L"coreclr.dll");
	uintptr_t offsetGameToBaseAddress = 0x004A24C8;

	uintptr_t dllBaseAddressQ = dwGetModuleBaseAddress(pID, L"System.Private.CoreLib.dll");
	uintptr_t offsetGameToBaseAddressQ = 0x009DA9F0;

	vector<DWORD> playerBaseOffsets{ 0x8, 0x758, 0x1E8, 0x8, 0x840, 0x0 };


	uintptr_t baseAddress = NULL;
	// Get value at gamebase + offset => store it in baseAddress
	BOOL rpmReturn = ReadProcessMemory(processHandle, (LPCVOID)(dllBaseAddress + offsetGameToBaseAddress), &baseAddress,
		sizeof(baseAddress), nullptr);

	uintptr_t baseAddressQ = NULL;
	ReadProcessMemory(processHandle, (LPCVOID)(dllBaseAddressQ + offsetGameToBaseAddressQ), &baseAddressQ,
		sizeof(baseAddressQ), nullptr);
	this->gamebaseQ = baseAddressQ;


	uintptr_t hpAddress = GetPointerChainAddress(playerBaseOffsets, processHandle, baseAddress) + 0x548;
	uintptr_t manaAddress = GetPointerChainAddress(playerBaseOffsets, processHandle, baseAddress) + 0x54c;
	uintptr_t defenceAddress = GetPointerChainAddress(playerBaseOffsets, processHandle, baseAddress) + 0x53c;
	uintptr_t lifeRegenAddress = GetPointerChainAddress(playerBaseOffsets, processHandle, baseAddress) + 0x558;
	uintptr_t xCoordsAddress = GetPointerChainAddress(playerBaseOffsets, processHandle, baseAddress) + 0x0030;
	uintptr_t yCoordsAddress = GetPointerChainAddress(playerBaseOffsets, processHandle, baseAddress) + 0x0034;
	uintptr_t ghostAddress = GetPointerChainAddress(playerBaseOffsets, processHandle, baseAddress) + 0x7c4;

	this->processHandle = processHandle;
	this->baseAddress = baseAddress;
	this->manaAddress = manaAddress;
	this->hpAddress = hpAddress;
	this->defenceAddress = defenceAddress;
	this->lifeRegenAddress = lifeRegenAddress;
	this->yCoordsAddress = yCoordsAddress;
	this->xCoordsAddress = xCoordsAddress;
	this->sl11NetIdOffsets = { 0x38, 0x70, 0x178, 0xb0, 0x0, 0x10, 0x120, 0x60, 0xd8 };
	this->sl11TypeOffsets = { 0x38, 0x70, 0x178, 0xb0, 0x0, 0x10, 0x120, 0x60, 0x178 };
	this->sl11AmntOffsets = { 0x38, 0x70, 0x178, 0xb0, 0x0, 0x10, 0x120, 0x60, 0xec };
	this->playerBaseOffsets = playerBaseOffsets;
	this->ghostAddress = ghostAddress;
	this->hGameWindow = hGameWindow;

}

int MemEdit::setMana(int newMana)
{
	int setmana = newMana;
	WriteProcessMemory(processHandle, (LPVOID)manaAddress, &setmana, sizeof(newMana), nullptr);
	return 0;
}

int MemEdit::setHp(int newHp)
{
	int setHp = newHp;
	WriteProcessMemory(processHandle, (LPVOID)hpAddress, &setHp, sizeof(newHp), nullptr);
	return 0;
}
