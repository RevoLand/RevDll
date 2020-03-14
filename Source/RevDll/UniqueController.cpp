#include "UniqueController.h"
#include "DllMain.h"
#include <iostream>
#include <string>
#include "hook.h"
#include <cstdio>

DWORD on_unique_enter = 0x00936640;
DWORD on_unique_kill = 0x00936640;

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

// FUN_00936640(0x2000001, "Unique Monster Killed! UNIQUE[%s] by [%s]");
void UniqueController::on_kill_message(DWORD a, char* message_string, char* unique_codename, char* character_name)
{
	/*
	 * unique_codename = Unique CodeName128 --> _RefObjCommon
	 * character_name = CharacterName128 --> _Char
	 */
	 //CALL(on_unique_kill);

	printf("[RevDll] Unique monster [%s] killed by [%s]\n", unique_codename, character_name);
	char buf2[1000];
	sprintf(buf2, "exec _LogUniqueKill '%s', '%s'", unique_codename, character_name);
	Main::getConnection()->execute(buf2);
}

// FUN_00936640(0x2000001, "Unique Monster Entered! UNIQUE[%s] POS[rid:%d (%.2f,%.2f,%.2f)]", ppppuVar6, (uint)local_f4, (double)local_f0, (double)local_ec);
// FUN_00936640(0x2000001, "Unique Monster Entered! UNIQUE[MOB_CH_TIGERWOMAN] POS[rid:region_id (PosX,PosY,PosZ)]", ppppuVar6, (uint)local_f4, (double)local_f0, (double)local_ec);
void UniqueController::on_enter_message(DWORD param_0, char* message_string, char* unique_codename, uint region_id, double PosX, double PosY, double PosZ)
{
	try
	{
		//CALL(on_unique_enter);
		printf(message_string, unique_codename, region_id, PosX, PosY, PosZ);
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to parse: [on_unique_enter_message] %s\n", ex.what());
	}
}