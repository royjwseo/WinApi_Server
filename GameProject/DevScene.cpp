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
	//�Ÿ� = �ð� * �ӵ� -> ��� ȯ�濡�� ���� ������ ���� ����

	//�̷��� �ȴٸ�, ���ÿ� ������ (�밢��) ��� �ӵ��� �ι� ������ �� �������� ���� ����.
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
