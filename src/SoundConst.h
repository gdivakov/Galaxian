#pragma once
#include <iostream>
#include <vector>

using std::string;

const string BLAST_SOUND = "res/audio/blast.mp3";
const string ROCKET_SOUND = "res/audio/blast_enemy.mp3";

const string GAME_OVER_SOUND = "res/audio/game_over.mp3";
const string PIRATE_EXPLOSION_SOUND = "res/audio/pirate_explosion.mp3";

const string PAUSE_SOUND = "res/audio/pause.mp3";
const string SELECT_ITEM_SOUND = "res/audio/select_item.mp3";

const std::vector<string> LEVEL_0_SOUNDS =
{
	SELECT_ITEM_SOUND
};

const std::vector<string> LEVEL_1_SOUNDS =
{
	BLAST_SOUND,
	GAME_OVER_SOUND,
	PIRATE_EXPLOSION_SOUND,
	PAUSE_SOUND,
	SELECT_ITEM_SOUND,
	ROCKET_SOUND
};