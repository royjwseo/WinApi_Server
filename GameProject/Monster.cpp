#include "pch.h"
#include "Monster.h"
#include "InputManager.h"
#include "TimeManager.h"



Monster::Monster() :Object(ObjectType::Monster)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

void Monster::Update()
{
	
}

void Monster::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 50);
}
