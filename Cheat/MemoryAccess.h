#pragma once

#include <Windows.h>
#include<TlHelp32.h>
#include <iostream>
#include <string>
#include <tchar.h> // _tcscmp
#include <vector>
#include "ShObjIdl.h";
#include <strsafe.h>
#include "FindModule.h";
#include <vector>

#define NOP 0x90

class MemEdit
{

public:
	MemEdit();
	int setMana(int newMana);
	int getMana(std::string* mana);
	int getManaInt(int* mana);
	int setHp(int newHp);
	int getHp(std::string* hp);
	int getHpInt(int *hp);
	int getDefense(std::string* def);
	int getLifeRegen(std::string* lifeRegen);
	int getXCoords(std::string* xCoords);
	int getYCoords(std::string* yCoords);
	int setSlotElevenType(int newType);
	int setSlotElevenNetID(int newNetId);
	int setSlotElevenAmount(int newAmnt);
	void setGhost(int ghostValue);
	void setTpPoint(float* posX, float* posY);
	void tpToPoint(float X, float Y);
	HANDLE processHandle;
	HWND hGameWindow;
	uintptr_t baseAddress;
	uintptr_t manaAddress;
	uintptr_t gamebaseQ;
	uintptr_t hpAddress;
	uintptr_t defenceAddress;
	uintptr_t lifeRegenAddress;
	uintptr_t xCoordsAddress;
	uintptr_t yCoordsAddress;
	uintptr_t ghostAddress;
	std::vector<DWORD> sl11TypeOffsets;
	std::vector<DWORD> sl11NetIdOffsets;
	std::vector<DWORD> sl11AmntOffsets;
	std::vector<DWORD> playerBaseOffsets;
};