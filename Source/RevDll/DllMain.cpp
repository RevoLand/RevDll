#include "DllMain.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <windows.h>

#include "ChatController.h"
#include "FixController.h"
#include "sql.h"
#include "UniqueController.h"

sql* sql_connection = new sql();
ConfigController* configs = new ConfigController();
memory* memory_helper = new memory();

DLLEXPORT BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason != DLL_PROCESS_ATTACH)
	{
		return true;
	}

	// Debug Console
	AllocConsole();

	// Make console writeable
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	std::cout << "[RevDll] Initializing - v0.1\n";

	// Init fixes
	FixController::initialize();

	// Init unique controller
	UniqueController::initialize();

	// Init chat controller
	ChatController::initialize();

	// Start sql connection & create console thread
	CreateThread(nullptr, NULL, LPTHREAD_START_ROUTINE(initialize), nullptr, NULL, nullptr);
	return true;
}

void initialize()
{
	sql_connection->connect();

	// doesn't works.
	//CloseWindow(::FindWindowW(nullptr, L"SQLAPI++ Registration Reminder"));

	console();
}

void console()
{
	std::cout << "[RevDll] Type your command.\n";
	std::string user_input;
	int user_input_int;
	std::cin >> user_input;

	if (user_input == "exit")
	{
		std::cout << "[RevDll] COMMAND FOUND!\n";
	}

	if (user_input == "party_monster_min_player")
	{
		std::cout << "[RevDll] The current minimum required player count to spawn a party monster is: " << main::getConfig()->party_monster_spawn_min_member_count << std::endl;
		std::cout << "Please input a new setting:";
		std::cin >> user_input_int;
		main::getConfig()->party_monster_spawn_min_member_count = user_input_int;
		FixController::party();
		//std::cout << "[RevDll] Minimum required player count to spawn a party monster is set to: " << Main::getConfig()->party_monster_spawn_min_member_count << " now." <<std::endl;
	}

	console();
}

sql* main::getConnection()
{
	return sql_connection;
}

ConfigController* main::getConfig()
{
	return configs;
}

memory* main::getMemory()
{
	return memory_helper;
}