#pragma once
#include <string>
#include <windows.h>
typedef unsigned char byte;
typedef unsigned int uint;

class ConfigController
{
public:
	ConfigController();

	// Level Limits
	byte level_cap, level_cap_pet;
	uint mastery_cap_ch, mastery_cap_eu;

	// Disable & Fixes
	bool disable_dumps, disable_green_book, disable_messages, disable_logs;
	bool fix_rates;

	// IP Spoof
	bool ip_spoof;
	std::string spoof_ip;

	// Gold Limits
	INT32 gold_limit_exchange, gold_limit_stall;

	// Job
	DWORD job_mgr_clamp_limit;

	// Capture the Flag
	std::string ctf_reward_item, battle_arena_reward_item;
	int ctf_reward_count, ctf_reward_param1, ctf_reward_param2, ctf_reward_param3, ctf_reward_param4, ctf_reward_param5, ctf_reward_param6, ctf_reward_param7, ctf_reward_param8;

	// Battle Arena
	int guild_arena_win_reward_item_count, guild_arena_lose_reward_item_count, random_party_arena_win_reward_item_count, random_party_arena_lose_reward_item_count;
	int arena_reward_param1, arena_reward_param2, arena_reward_param3, arena_reward_param4, arena_reward_param5, arena_reward_param6, arena_reward_param7, arena_reward_param8;
};
