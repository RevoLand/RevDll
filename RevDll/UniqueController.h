#pragma once
#include "DllMain.h"

class UniqueController
{
public:
	static void initialize();
	static void on_kill_message(DWORD a, char* message_string, char* unique_codename, char* character_name);
	static void on_enter_message(DWORD param_0, char* message_string, char* unique_codename, uint region_id, double PosX, double PosY, double PosZ);
};
