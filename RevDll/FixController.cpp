#include "FixController.h"
#include <exception>

#include "DllMain.h"
#include "hook.h"
#include "memhelp.h"

void FixController::initialize()
{
	level_cap();
	mastery_cap();
	disable_fix();
	ip();
	gold_limits();
	ctf();
	arena_rewards();
	job();
}

void FixController::level_cap()
{
	try
	{
		if (Main::getConfig()->level_cap > 0)
		{
			// 0x6e = 110
			// 004d641b 80 7e 58 6e     CMP        byte ptr [ESI + 0x58],0x6e
			Main::getMemory()->WriteByte(0x004D641B + 3, Main::getConfig()->level_cap);
			// 004e52c7 80 f9 6e        CMP        CL,0x6e
			Main::getMemory()->WriteByte(0x004E52C7 + 2, Main::getConfig()->level_cap);
			// 004e5471 81 7c 24 20 b6 01 00 00        CMP dword ptr [ESP + 0x20],0x1b6
			Main::getMemory()->WriteByte(0x004E5471 + 4, 0xFF); // 0x1b6 = 438?

			printf("[RevDll] Character Level Cap set to: %d\n", Main::getConfig()->level_cap);
		}

		if (Main::getConfig()->level_cap_pet > 0)
		{
			// 004d641b 80 7e 58 6e     CMP        byte ptr [ESI + 0x58],0x6e
			Main::getMemory()->WriteByte(0x004D641B + 3, Main::getConfig()->level_cap_pet);

			printf("[RevDll] Pet Level Cap set to: %d\n", Main::getConfig()->level_cap_pet);
		}
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to set character or pet level cap: %s\n", ex.what());
	}
}

void FixController::mastery_cap()
{
	try
	{
		if (Main::getConfig()->mastery_cap_ch > 0)
		{
			// 0x14a = 330
			// 0059c5e6 3d 4a 01 00 00        CMP        EAX,0x14a
			Main::getMemory()->WriteNumber(0x0059C5E6 + 1, Main::getConfig()->mastery_cap_ch);
			printf("[RevDll] CH Mastery Level Cap set to: %d\n", Main::getConfig()->mastery_cap_ch);
		}

		if (Main::getConfig()->mastery_cap_eu > 0)
		{
			/*
			 * #define EU_MASTERY_MAX_LEVEL_OFFSET       0x00B46130
				DOUBLE dblTmpMaxEuroMastery = static_cast<LDOUBLE>(pstGameServerConfig->dwMaxEuropeMasteryLevel);
				MEMUTIL_WRITE_VALUE(LDOUBLE, 0x00B46130, dblTmpMaxEuroMastery);
			 */

			 // 00b46136
			//Main::getMemory()->WriteNumber(0x00b46134, Main::getConfig()->mastery_cap_eu);

			//Main::getMemory()->WriteDouble(0x00B46130, Main::getConfig()->mastery_cap_eu);
			//Main::getMemory()->WriteString(0x00B46130, Main::getConfig()->mastery_cap_eu);

			//printf("[RevDll] EU Mastery Level Cap set to: %d\n", Main::getConfig()->mastery_cap_eu);
		}
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to set mastery cap: %s\n", ex.what());
	}
}

void FixController::disable_fix()
{
	try
	{
		if (Main::getConfig()->fix_rates)
		{
			// exp
			// 0042714c f6 c4 41        TEST       AH,0x41
			Main::getMemory()->WriteByte(0x0042714C + 2, 0x42);

			// exp - party
			// 004271f5 f6 c4 41        TEST       AH,0x41
			Main::getMemory()->WriteByte(0x004271F5 + 2, 0x42);

			// item/drop
			// 004272a0 f6 c4 41        TEST       AH,0x41
			Main::getMemory()->WriteByte(0x004272A0 + 2, 0x42);

			// gold
			// 00427349 f6 c4 41        TEST       AH,0x41
			Main::getMemory()->WriteByte(0x00427349 + 2, 0x42);

			printf("[RevDll] Rates fixed.\n");
		}

		if (Main::getConfig()->disable_green_book)
		{
			// 004142e2 81 e9 22 31 00 00        SUB        ECX,0x3122
			Main::getMemory()->WriteNumber(0x004142e2 + 2, 0x999999);
			//Main::getMemory()->SetNop(0x004142E2, 8);
			// 0041474d e8 ee 1e 52 00        CALL        FUN_00936640        undefined FUN_00936640(undefined
			//Main::getMemory()->SetNop(0x0041474D, 5);

			printf("[RevDll] Green Book disabled.\n");
		}

		if (Main::getConfig()->disable_dumps)
		{
			/*
			 * 0096412c e8 3f 1e ac ff        CALL       FUN_00425f70 undefined FUN_00425f70(undefined (char *param_1))
			 */
			 // Alternative fix is calling a custom made function and returning 1.
			  //CALLFunction(0x0096412c, DWORD(on_dump_function));

			  // 00964134 85 c0           TEST       EAX,EAX
			Main::getMemory()->WriteByte(0x00964134 + 1, 0xFF);

			printf("[RevDll] Dumps disabled.\n");
		}

		if (Main::getConfig()->disable_messages)
		{
			Main::getMemory()->SetRetn(0x00936640);

			printf("[RevDll] GameServer Window Messages disabled.\n");
		}

		if (Main::getConfig()->disable_logs)
		{
			// undefined __thiscall FUN_0043a350 - CALL _ADDLOGCHAR
			Main::getMemory()->SetRetnVal(0x0043A350, 4);
			// undefined __thiscall FUN_0043a470 - CALL _ADDLOGSIEGEFORTRESS
			Main::getMemory()->SetRetnVal(0x0043A470, 4);
			// undefined __thiscall FUN_0043a590 - CALL _ADDLOGITEM
			Main::getMemory()->SetRetnVal(0x0043A590, 4);
			// undefined __thiscall FUN_0043a6d0 - CALL _AddLogServerEvent
			Main::getMemory()->SetRetnVal(0x0043A6D0, 4);
			// undefined __thiscall FUN_0043a7f0 - CALL _AddLogSchedule
			Main::getMemory()->SetRetnVal(0x0043A7F0, 4);
			printf("[RevDll] Log Database transactions disabled.\n");
		}
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to apply selected fixes: %s\n", ex.what());
	}
}

int FixController::on_dump_function(const char* a)
{
	printf("Dump function called: [%s]\n", a);

	return 1;
}

void FixController::ip()
{
	try
	{
		if (Main::getConfig()->ip_spoof)
		{
			// Free memory space : 0x00ad8210
			Main::getMemory()->WriteString(0x00ad8200, &Main::getConfig()->spoof_ip[0]);
			// 009365b9 68 a0 02 b4 00        PUSH        s_%d.%d.%d.%d_00b402a0        = "%d.%d.%d.%d"
			Main::getMemory()->WriteNumber(0x009365B9 + 1, 0x00ad8200);
			// 0093660d 68 a0 02 b4 00        PUSH        s_%d.%d.%d.%d_00b402a0        = "%d.%d.%d.%d"
			Main::getMemory()->WriteNumber(0x0093660D + 1, 0x00ad8200);

			std::cout << "[RevDll] IP Address spoofed as: [" << &Main::getConfig()->spoof_ip[0] << "]" << std::endl;
		}
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to spoof ip: %s\n", ex.what());
	}
}

void FixController::gold_limits()
{
	try
	{
		if (Main::getConfig()->gold_limit_exchange > 0)
		{
			// 00480f5e 81 7c 24 20 00 ca 9a 3b       CMP        dword ptr [ESP + param_1],0x3b9aca00
			Main::getMemory()->WriteNumber(0x00480F5E + 4, Main::getConfig()->gold_limit_exchange);
			// 004d8f1a 81 ff 00 ca 9a 3b       CMP        EDI,0x3b9aca00
			Main::getMemory()->WriteNumber(0x004D8F1A + 2, Main::getConfig()->gold_limit_exchange);
			// 004d8f22 bf 00 ca 9a 3b       MOV        EDI,0x3b9aca00 TODO: +2 idi +1 YAPILDI?
			Main::getMemory()->WriteNumber(0x004D8F22 + 1, Main::getConfig()->gold_limit_exchange);
			// 004f7734 81 f9 00 ca 9a 3b       CMP        ECX,0x3b9aca00
			Main::getMemory()->WriteNumber(0x004F7734 + 2, Main::getConfig()->gold_limit_exchange);
			// 004f7746 c7 44 24 10 00 ca 9a 3b       MOV        dword ptr [ESP + local_14],0x3b9aca00
			Main::getMemory()->WriteNumber(0x004F7746 + 4, Main::getConfig()->gold_limit_exchange);

			printf("[RevDll] Exchange gold limit set to: [%lu].\n", Main::getConfig()->gold_limit_exchange);
		}

		// Static 500B limit.
		if (Main::getConfig()->gold_limit_stall > 0)
		{
			// 00471b00 83 fe 02        CMP        ESI,0x2
			Main::getMemory()->WriteByte(0x00471b00 + 2, 0x74);
			// 00472ff5 83 fa 02        CMP        param_2,0x2
			Main::getMemory()->WriteByte(0x00472ff5 + 2, 0x74);
			// 0047abd8 83 f8 02        CMP        EAX,0x2
			Main::getMemory()->WriteByte(0x0047abd8 + 2, 0x74);

			// 00471b07 3d ff e3 0b 54       CMP        EAX,0x540be3ff
			Main::getMemory()->WriteNumber(0x00471B07 + 1, 0x6A528800);
			// 00473008 3d ff e3 0b 54       CMP        EAX,0x540be3ff
			Main::getMemory()->WriteNumber(0x00473008 + 1, 0x6A528800);
			// 0047abe3 81 f9 ff e3 0b 54       CMP        ECX,0x540be3ff
			Main::getMemory()->WriteNumber(0x0047ABE3 + 2, 0x6A528800);

			printf("[RevDll] Stall gold limit set to ! 500B STATIC !: .\n");
		}
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to set gold limits: %s\n", ex.what());
	}
}

void FixController::ctf()
{
	try
	{
		if (Main::getConfig()->ctf_reward_count <= 0)
		{
			return;
		}

		// _ctfRewardOffset
		Main::getMemory()->WriteByte(0x00646C93 + 4, Main::getConfig()->ctf_reward_count);
		// _ctfRewardItemStrOffset
		Main::getMemory()->WriteString(0x00AD8FC0, &Main::getConfig()->ctf_reward_item[0]);

		// _ctfRewardItemPushOffset_1-2-3
		Main::getMemory()->WriteNumber(0x00646D42 + 1, 0x00AD8FC0);
		Main::getMemory()->WriteNumber(0x005F19A9 + 1, 0x00AD8FC0);
		Main::getMemory()->WriteNumber(0x00876935 + 6, 0x00AD8FC0);

		// _pCtfRewardParamOffsets 1-8
		Main::getMemory()->WriteByte(0x00646D25 + 1, Main::getConfig()->ctf_reward_param1);
		Main::getMemory()->WriteByte(0x00646D2D + 1, Main::getConfig()->ctf_reward_param2);
		Main::getMemory()->WriteByte(0x00646D2F + 1, Main::getConfig()->ctf_reward_param3);
		Main::getMemory()->WriteByte(0x00646D31 + 1, Main::getConfig()->ctf_reward_param4);
		Main::getMemory()->WriteByte(0x00646D33 + 1, Main::getConfig()->ctf_reward_param5);
		Main::getMemory()->WriteByte(0x00646D35 + 1, Main::getConfig()->ctf_reward_param6);
		Main::getMemory()->WriteByte(0x00646D37 + 1, Main::getConfig()->ctf_reward_param7);
		Main::getMemory()->WriteByte(0x00646D39 + 1, Main::getConfig()->ctf_reward_param8);
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to set Capture The Flag rewards: %s\n", ex.what());
	}
}

void FixController::arena_rewards()
{
	try
	{
		if (Main::getConfig()->guild_arena_win_reward_item_count > 0)
		{
			Main::getMemory()->WriteByte(0x00669158 + 4, Main::getConfig()->guild_arena_win_reward_item_count);
		}

		if (Main::getConfig()->guild_arena_lose_reward_item_count > 0)
		{
			Main::getMemory()->WriteByte(0x00669173 + 4, Main::getConfig()->guild_arena_lose_reward_item_count);
		}

		if (Main::getConfig()->random_party_arena_win_reward_item_count > 0)
		{
			Main::getMemory()->WriteByte(0x0066915F + 4, Main::getConfig()->random_party_arena_win_reward_item_count);
		}

		if (Main::getConfig()->random_party_arena_lose_reward_item_count > 0)
		{
			Main::getMemory()->WriteByte(0x0066917A + 4, Main::getConfig()->random_party_arena_lose_reward_item_count);
		}

		Main::getMemory()->WriteString(0x00AD8F49, &Main::getConfig()->battle_arena_reward_item[0]);
		Main::getMemory()->WriteNumber(0x006691C6 + 1, 0x00AD8F49);

		// _pArenaRewardParamOffsets 1-8
		Main::getMemory()->WriteByte(0x006691A7 + 1, Main::getConfig()->arena_reward_param1);
		Main::getMemory()->WriteByte(0x006691AF + 1, Main::getConfig()->arena_reward_param2);
		Main::getMemory()->WriteByte(0x006691B1 + 1, Main::getConfig()->arena_reward_param3);
		Main::getMemory()->WriteByte(0x006691B3 + 1, Main::getConfig()->arena_reward_param4);
		Main::getMemory()->WriteByte(0x006691B5 + 1, Main::getConfig()->arena_reward_param5);
		Main::getMemory()->WriteByte(0x006691B7 + 1, Main::getConfig()->arena_reward_param6);
		Main::getMemory()->WriteByte(0x006691B9 + 1, Main::getConfig()->arena_reward_param7);
		Main::getMemory()->WriteByte(0x006691BB + 1, Main::getConfig()->arena_reward_param8);
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to set Battle Arena rewards: %s\n", ex.what());
	}
}

void FixController::job()
{
	try
	{
		// 0060e126 81 ff 00 94 35 77       CMP        EDI,0x77359400
		Main::getMemory()->WriteNumber(0x0060E126 + 2, Main::getConfig()->job_mgr_clamp_limit);
		// 0060e182 81 f9 00 94 35 77       CMP        ECX,0x77359400
		Main::getMemory()->WriteNumber(0x0060E182 + 2, Main::getConfig()->job_mgr_clamp_limit);
		// 0060e18a b9 00 94 35 77       MOV        ECX,0x77359400
		Main::getMemory()->WriteNumber(0x0060E18A + 1, Main::getConfig()->job_mgr_clamp_limit);
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to set job clamp manager limit: %s\n", ex.what());
	}
}