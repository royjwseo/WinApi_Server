#pragma once
#include "Scene.h" //����� �Ҷ� ������ �߰�

class GameScene :public Scene
{
public:
	GameScene();
	virtual	~GameScene()override;


	virtual void Init()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
};
