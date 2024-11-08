#include "pch.h"
#include "Missile.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Monster.h"




Missile::Missile() :Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;


}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_pos.y -= deltaTime * _stat.speed;

	// 충돌
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {

		if (object == this)continue;

		if (object->GetObjectType() != ObjectType::Monster)
			continue;

		Pos p1 = GetPos();
		Pos p2 = object->GetPos();

		const float dx = p1.x - p2.x;
		const float dy = p1.y - p2.y;
		float dist = sqrt(dx * dx + dy * dy);

		if (dist < 25) {
			GET_SINGLE(ObjectManager)->Remove(object);
			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
		
			
		/*	if (dynamic_cast<Monster*>(object)) {
			if (_pos.x <= object->GetPos().x + 25 && _pos.x >= object->GetPos().x - 25
				&& _pos.y <= object->GetPos().y + 25 && _pos.y >= object->GetPos().y - 25) {
				GET_SINGLE(ObjectManager)->Remove(object);
				GET_SINGLE(ObjectManager)->Remove(this);
				return;
			}
		}*/
		
	}

	// TODO
	if (_pos.y < -200) {
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
		// ?
		// 현재 자기 자신을 제거하였으므로, 해당 코드 Remove
		// 이후 Missile의 멤버변수를 건드리면 메모리 오염 일어남.
		// 그러므로 바로 return 때려주는게 안전함.
		// 실행함에 있어서는 루프를 끝내는 것까진 돌음 코드영역 코드 실행상
		
	}

}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
