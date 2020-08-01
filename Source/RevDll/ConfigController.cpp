#include "ConfigController.h"
#include <iostream>
#include "INIReader.h"
#include "Windows.h"

ConfigController::ConfigController()
{
	const INIReader reader(".\\Config\\config.ini");

	if (reader.ParseError() != 0) {
		std::cout << "Can't parse config file!!!\n";
	}

	// Level Limits
	level_cap = reader.GetInteger("level_cap", "ch_eu", 110);
	level_cap_pet = reader.GetInteger("level_cap", "pet", 110);

	mastery_cap_ch = reader.GetInteger("mastery_cap", "ch", 330);
	mastery_cap_eu = reader.GetInteger("mastery_cap", "eu", 220);

	// Disable & Fixes
	fix_rates = reader.GetBoolean("disable_fix", "fix_rates", true);
	null_instance_fix = reader.GetBoolean("disable_fix", "null_instance_fix", true);
	disable_dumps = reader.GetBoolean("disable_fix", "disable_dumps", true);
	disable_green_book = reader.GetBoolean("disable_fix", "disable_green_book", true);
	disable_messages = reader.GetBoolean("disable_fix", "disable_messages", false);
	disable_logs = reader.GetBoolean("disable_fix", "disable_logs", false);
	
	disable_npc_register_gold_price_error = reader.GetBoolean("disable_fix", "npc_register_gold_price_error", true);
	disable_npc_register_silk_price_error = reader.GetBoolean("disable_fix", "npc_register_silk_price_error", true);

	// IP Spoofing
	ip_spoof = reader.GetBoolean("ip", "spoof", true);
	spoof_ip = reader.Get("ip", "ip", "127.0.0.1");

	// Gold Limits
	gold_limit_exchange = reader.GetInteger("gold_limits", "exchange", 1000000000);
	gold_limit_stall = reader.GetInteger("gold_limits", "stall", INT_MAX);

	// Party
	party_monster_spawn_min_member_count = reader.GetInteger("party", "monster_spawn_min_member_count", 2);
	party_monster_spawn_chance = reader.GetInteger("party", "monster_spawn_chance", 50);

	// Academy
	academy_create_penalty = reader.GetInteger("academy", "create_penalty_seconds", 604800);
	academy_disband_penalty = reader.GetInteger("academy", "disband_penalty_seconds", 604800);
	academy_graduate_level = reader.GetInteger("academy", "graduate_level", 40);

	// Guild
	guild_union_chat_limit = reader.GetInteger("guild", "union_chat_limit", 12);
	guild_leaving_penalty = reader.GetInteger("guild", "leaving_penalty", 604800);

	// Unique
	unique_summon_skill_spawn_limit = reader.GetInteger("unique", "summon_skill_spawn_limit", 50);

	// Capture the Flag
	ctf_reward_item = reader.Get("ctf", "reward_item", "ITEM_ETC_ARENA_COIN");
	ctf_reward_count = reader.GetInteger("ctf", "reward_item_count", 1);
	ctf_reward_param1 = reader.GetInteger("ctf", "reward_item_param1", 0);
	ctf_reward_param2 = reader.GetInteger("ctf", "reward_item_param2", 0);
	ctf_reward_param3 = reader.GetInteger("ctf", "reward_item_param3", 1);
	ctf_reward_param4 = reader.GetInteger("ctf", "reward_item_param4", 0);
	ctf_reward_param5 = reader.GetInteger("ctf", "reward_item_param5", 0);
	ctf_reward_param6 = reader.GetInteger("ctf", "reward_item_param6", 0);
	ctf_reward_param7 = reader.GetInteger("ctf", "reward_item_param7", 0);
	ctf_reward_param8 = reader.GetInteger("ctf", "reward_item_param8", 1);

	// Battle Arena
	battle_arena_reward_item = reader.Get("battle_arena", "reward_item", "ITEM_ETC_ARENA_COIN");
	guild_arena_win_reward_item_count = reader.GetInteger("battle_arena", "guild_win_reward_item_count", 7);
	guild_arena_lose_reward_item_count = reader.GetInteger("battle_arena", "guild_lose_reward_item_count", 2);
	random_party_arena_win_reward_item_count = reader.GetInteger("battle_arena", "party_win_reward_item_count", 7);
	random_party_arena_lose_reward_item_count = reader.GetInteger("battle_arena", "party_lose_reward_item_count", 2);
	arena_reward_param1 = reader.GetInteger("battle_arena", "reward_item_param1", 0);
	arena_reward_param2 = reader.GetInteger("battle_arena", "reward_item_param2", 0);
	arena_reward_param3 = reader.GetInteger("battle_arena", "reward_item_param3", 1);
	arena_reward_param4 = reader.GetInteger("battle_arena", "reward_item_param4", 0);
	arena_reward_param5 = reader.GetInteger("battle_arena", "reward_item_param5", 0);
	arena_reward_param6 = reader.GetInteger("battle_arena", "reward_item_param6", 0);
	arena_reward_param7 = reader.GetInteger("battle_arena", "reward_item_param7", 0);
	arena_reward_param8 = reader.GetInteger("battle_arena", "reward_item_param8", 1);

	// Job
	job_mgr_clamp_limit = reader.GetInteger("job", "manager_clamp_limit", 2134217728);
	job_level_cap = reader.GetInteger("job", "level_cap", 7);
	job_leaving_penalty = reader.GetInteger("job", "leaving_penalty", 604800);
}