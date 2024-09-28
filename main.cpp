#include <iostream>
#include <Windows.h>
#include "bypass.h"
#include <chrono>
#include <thread>

	
int main() {

	Bypass user1;

	// OFFSETS

	uintptr_t gun1_ammo = user1.GET_ADDR_GUN1AMMO();
	uintptr_t gun2_ammo = user1.GET_ADDR_GUN2AMMO();
	uintptr_t heal		= user1.GET_ADDR_HEAL();

	user1.offset_update();
	
	user1.writeMemory(gun1_ammo, 999999);
	user1.writeMemory(gun2_ammo, 999999);
	user1.writeMemory(heal, 999999);
	

	return 0;
	
}	