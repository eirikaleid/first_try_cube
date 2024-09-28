#pragma once
#include <Windows.h>
#include <iostream>


class Bypass {
private:

	HANDLE hProcess;
	uintptr_t main_addr; // pointer addr

	uintptr_t ADDR_GUN1AMMO = 0x140;	
	uintptr_t ADDR_GUN2AMMO = 0x12C;
	uintptr_t ADDR_HP = 0xEC; 

	int gun1_ammo;
	int gun2_ammo;
	int heal;


public:

	Bypass();
	~Bypass();

	void offset_update();
	void oku();
	void writeMemory(uintptr_t naddr, int point);

	uintptr_t GET_ADDR_GUN1AMMO();
	uintptr_t GET_ADDR_GUN2AMMO();
	uintptr_t GET_ADDR_HEAL();
	

};