#include "pch.h"
#include "DevScene.h"
#include "InputManager.h"
#include "TimeManager.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
}

void DevScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	//거리 = 시간 * 속도 -> 모든 환경에서 동일 움직임 구현 위해

	//이렇게 된다면, 동시에 누르는 (대각선) 경우 속도가 두번 더해져 더 빨라지는 오류 생김.
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_playerX -= _speed*deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_playerX += _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_playerY -= _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_playerY += _speed * deltaTime;
	}
}

void DevScene::Render(HDC hdc)
{

	Utils::DrawCircle(hdc, static_cast<Pos>(Pos{ _playerX, _playerY }), 50);
}
