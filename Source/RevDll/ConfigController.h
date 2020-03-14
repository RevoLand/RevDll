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

	// Party
	int party_monster_spawn_min_member_count, party_monster_spawn_chance;

	// Academy
	int academy_create_penalty, academy_disband_penalty, academy_graduate_level;

	// Guild
	int guild_union_chat_limit, guild_leaving_penalty;

	// Unique
	byte unique_summon_skill_spawn_limit;

	// Capture the Flag
	std::string ctf_reward_item, battle_arena_reward_item;
	int ctf_reward_count, ctf_reward_param1, ctf_reward_param2, ctf_reward_param3, ctf_reward_param4, ctf_reward_param5, ctf_reward_param6, ctf_reward_param7, ctf_reward_param8;

	// Battle Arena
	int guild_arena_win_reward_item_count, guild_arena_lose_reward_item_count, random_party_arena_win_reward_item_count, random_party_arena_lose_reward_item_count;
	int arena_reward_param1, arena_reward_param2, arena_reward_param3, arena_reward_param4, arena_reward_param5, arena_reward_param6, arena_reward_param7, arena_reward_param8;

	// Job
	int job_mgr_clamp_limit, job_level_cap, job_leaving_penalty;
};
