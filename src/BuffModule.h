#pragma once
#include <vector>
#include <map>

#include "Consts.h"
#include "SpecialsConsts.h"
#include "Ship.h"
#include "SoundConst.h"

struct BuffParams;
const enum BuffType;
class Ship;

class BuffModule
{
public:
	typedef std::map<std::string, BuffParams> Buffs;

	BuffModule(Ship* p_ship);
	~BuffModule();

	std::map<std::string, BuffParams>* getBuffs() { return &appliedBuffs; };
	void updateBuffs();
	void addBuff(BuffType nextBuff);
	void removeBuff(BuffType buff);
	bool hasBuff(BuffType buff);
private:
	Buffs appliedBuffs;
	Ship* ship;
};