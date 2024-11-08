#pragma once

using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;


struct Pos {
	float x = 0;
	float y = 0;
	Pos(float _x, float _y) { x = _x; y = _y; }
	Pos() = default;
};

struct Stat {
	int hp;
	int maxHp;
	int speed;
};