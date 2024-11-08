#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "Missile.h"
#include "ObjectManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPos(Pos{ 400,400 });
		GET_SINGLE(ObjectManager)->Add(player);
	}
	
	{
		for (int32 i = 0; i < 5; ++i) {
			Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
			monster->SetPos(Pos(static_cast<float>(i+1)*100,100 ));
			//축소 변환 , 생성자 안만들고 자동 만들어줄땐 i같이 int형 있으면 float로 변환해야함
			GET_SINGLE(ObjectManager)->Add(monster);
		}
	}
	
}

void GameScene::Update()
{

	//const vector<Object*>& objs=GET_SINGLE(ObjectManager)->GetObjects();
	const vector<Object*> objs=GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* objects : objs) {
		objects->Update();
	}
	//현재 문제 발생하는 이유는 오브젝트 컨테이너 벡터를 참조로 받아온 후 순회함과 동시에 플레이어 cpp
	// 에서 미사일을 해당 컨테이너에 추가하려고 시도하는 순간 크래쉬가 난다.
//그러므로 벡터에 추가할땐 벡터를 복사해서 수정하면 문제 생기진 않음.
	// 하지만 마찬가지로 삭제할때는 해당 메모리가 만약 없어진 경우 복사한 영역은 남아있겠지만 의미상 사용되면 안되는 메모리이므로 
	// 문제가 생김.
}

void GameScene::Render(HDC hdc)
{
	const vector<Object*>& objs = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* objects : objs) {
		objects->Render(hdc);
	}
}
