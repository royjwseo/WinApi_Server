#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Missile.h"

Player::Player():Object(ObjectType::Player)
{
}

Player::~Player()
{
}

void Player::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	//거리 = 시간 * 속도 -> 모든 환경에서 동일 움직임 구현 위해

	//이렇게 된다면, 동시에 누르는 (대각선) 경우 속도가 두번 더해져 더 빨라지는 오류 생김.
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_pos.x -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_pos.x += _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_pos.y-= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_pos.y+= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar)) {
		//TODO:미사일 발사
		Missile* missile=GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(_pos);
		GET_SINGLE(ObjectManager)->Add(missile);

	}
}

void Player::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 50);
}
