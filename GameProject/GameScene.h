#pragma once
#include "Scene.h" //상속을 할땐 무조건 추가

class GameScene :public Scene
{
public:
	GameScene();
	virtual	~GameScene()override;


	virtual void Init()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
private:

};

