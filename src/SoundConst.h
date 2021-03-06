#pragma once
#include <iostream>
#include <vector>

const std::string LEVEL_1_MUSIC = "res/audio/lvl1.mp3";

const std::string BLAST_SOUND = "res/audio/blast.mp3";
const std::string ROCKET_SOUND = "res/audio/blast_enemy.mp3";
const std::string PJ_EXPLOSION_SOUND = "res/audio/pj_explosion.mp3";

const std::string GAME_OVER_SOUND = "res/audio/game_over.mp3";
const std::string PIRATE_EXPLOSION_SOUND = "res/audio/pirate_explosion.mp3";

const std::string PAUSE_SOUND = "res/audio/pause.mp3";
const std::string SELECT_ITEM_SOUND = "res/audio/select_item.mp3";
const std::string BUFF_SPEED_UP_SOUND = "res/audio/speed_up.mp3";
const std::string BUFF_APPLIED_SOUND = "res/audio/buff_applied.mp3";
const std::string REACH_THE_FINISH = "res/audio/reach_the_finish.mp3";
const std::string BOSS_DEFEATED_SOUND = "res/audio/boss_defeated.mp3";

const std::vector<std::string> LEVEL_0_SOUNDS =
{
	SELECT_ITEM_SOUND
};

const std::vector<std::string> LEVEL_1_SOUNDS =
{
	BLAST_SOUND,
	PJ_EXPLOSION_SOUND,
	GAME_OVER_SOUND,
	PIRATE_EXPLOSION_SOUND,
	PAUSE_SOUND,
	SELECT_ITEM_SOUND,
	ROCKET_SOUND,
	BUFF_SPEED_UP_SOUND,
	BUFF_APPLIED_SOUND,
	REACH_THE_FINISH,
	BOSS_DEFEATED_SOUND,
};