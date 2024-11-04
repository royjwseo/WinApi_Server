#include "pch.h"
#include "TimeManager.h"

IMPLEMENT_SINGLETON(TimeManager);

void TimeManager::Init()
{
	//���� ms ��ȯ
	::GetTickCount64();

	::GetTickCount64();

	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(& _frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>( & _prevCount));
}

void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime+=_deltaTime;

	if (_frameTime >= 1.f) {
		//���ʸ��� ��� ���ŵ����� fps�̹Ƿ� 
		_fps = static_cast<uint32>(_frameCount / _frameTime);
		_frameTime = 0.f;
		_frameCount = 0;
	}
}