#include "UniqueController.h"
#include "DllMain.h"
#include <iostream>
#include <string>
#include "hook.h"
#include <cstdio>

DWORD gs_unique_message = 0x00936640;

void UniqueController::initialize()
{
	std::cout << "======================== [Unique Controller] ========================" << std::endl;
	// Unique Monster Entered!
	CALLFunction(0x00414db0, DWORD(on_enter_message));

	// Unique Monster Killed!
	CALLFunction(0x00414BA9, DWORD(on_kill_message));

	// Console
	std::cout << "[RevDll] UniqueController hooked.\n";
	std::cout << "======================== [Unique Controller] ========================" << std::endl;
}

// FUN_00936640(0x2000001, "Unique Monster Entered! UNIQUE[%s] POS[rid:%d (%.2f,%.2f,%.2f)]", ppppuVar6, (uint)local_f4, (double)local_f0, (double)local_ec);
// FUN_00936640(0x2000001, "Unique Monster Entered! UNIQUE[MOB_CH_TIGERWOMAN] POS[rid:region_id (PosX,PosY,PosZ)]", unique_codename, (uint)region_id, (double)PosX, (double)PosY, (double)PosZ);
void UniqueController::on_enter_message(DWORD param_0, char* message_string, char* unique_codename, uint region_id, double PosX, double PosY, double PosZ)
{
	char output[1000];
	sprintf(output, message_string, unique_codename, region_id, PosX, PosY, PosZ);

	std::cout << output << std::endl;
}

// FUN_00936640(0x2000001, "Unique Monster Killed! UNIQUE[%s] by [%s]");
void UniqueController::on_kill_message(DWORD a, char* message_string, char* unique_codename, char* character_name)
{
	SACommand cmd;
	try
	{
		cmd.setConnection(&main::getConnection()->connection);
		cmd.setCommandText("_LogUniqueKill");
		cmd.Param("UniqueCodeName").setAsString() = unique_codename;
		cmd.Param("KillerCharacterName").setAsString() = character_name;
		cmd.Execute();
#ifdef DEBUG
		std::cout << "[SQL-DEBUG] -> [_LogUniqueKill] procedure executed" << std::endl;
#endif
	}
	catch (SAException & e)
	{
#ifdef DEBUG
		printf("[SQL-DEBUG] -> failed to execute procedure  [_LogUniqueKill]\nException:[%s]\n", static_cast<const char*>(e.ErrText()));
#endif
	}

#ifdef DEBUG
	printf("[RevDll] Unique monster [%s] killed by [%s]\n", unique_codename, character_name);
#endif
}