#include "bypass.h"


using namespace std;
Bypass::Bypass() {

	// Asýl Addr Çekmek için kullanýcaðýmýz Pointer
	uintptr_t base = 0x57B0B8;

	// HWND ile PID çekiyoruz
	HWND hwnd = FindWindowA("NVOpenGLPbuffer", nullptr);

	DWORD PID = 0;

	GetWindowThreadProcessId(hwnd, &PID);

	if (PID == NULL) {

		cout << "PID is NULL" << endl;
		system("pause>nul");
		exit(0);
	}

	DWORD Access = PROCESS_ALL_ACCESS;

	hProcess = OpenProcess(Access, FALSE, PID);
	
	if (hProcess == NULL) {
		cout << "hProcess is NULL" << endl;
		system("pause>nul");
		exit(0);
	}

	uintptr_t mainBaseAddry; // bu adrese kayýt edicez asýl pointer adresini
	BOOL hMainAddr = ReadProcessMemory(hProcess, (LPCVOID)base, &mainBaseAddry, sizeof(mainBaseAddry), NULL);

	if (hMainAddr == false) {
		cout << "hMainAddr is NULL" << endl;
		system("pause>nul");
		exit(0);
	}

	main_addr = mainBaseAddry;

}

Bypass::~Bypass() {


	if (hProcess != NULL) CloseHandle(hProcess);

}

void Bypass::offset_update() {

	// GUN1 bilgisi
	
	BOOL gun1 = ReadProcessMemory(hProcess, (LPCVOID)(main_addr+ ADDR_GUN1AMMO), &gun1_ammo, sizeof(gun1_ammo), NULL);
	if (gun1 == false) {
		cerr << "Gun_1 Addr could not be Read!" << endl;
		system("pause>nul");
		exit(0);
	}

	// GUN2 bilgisi
	BOOL gun2 = ReadProcessMemory(hProcess, (LPCVOID)(main_addr + ADDR_GUN2AMMO), &gun2_ammo, sizeof(gun2_ammo), NULL);
	if (gun2 == false) {
		cerr << "Gun_2 Addr could not be Read!" << endl;
		system("pause>nul");
		exit(0);
	}

	// Heal bilgisi
	BOOL heal = ReadProcessMemory(hProcess, (LPCVOID)(main_addr + ADDR_HP), &heal, sizeof(heal), NULL);
	if (heal == false) {
		cerr << "heal Addr could not be Read!" << endl;
		system("pause>nul");
		exit(0);
	}

}

void Bypass::oku() {

	cout << "Gun1 Ammo: " << gun1_ammo << endl;
	cout << "Gun2 Ammo: " << gun2_ammo << endl;
	cout << "Heal: " << heal << endl;

}

void Bypass::writeMemory(uintptr_t naddr, int point) {

	BOOL cont = WriteProcessMemory(hProcess, (LPVOID)(main_addr + naddr), &point, sizeof(point), NULL);

	if (!cont) {
		cerr << "Cheat could not be write!" << endl;
		system("pause>nul");
		exit(0);
	}


}

uintptr_t Bypass::GET_ADDR_GUN1AMMO() {
	return ADDR_GUN1AMMO;
}

uintptr_t Bypass::GET_ADDR_GUN2AMMO() {
	return ADDR_GUN2AMMO;
}

uintptr_t Bypass::GET_ADDR_HEAL() {
	return ADDR_HP;
}