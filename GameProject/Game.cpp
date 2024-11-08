#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

Game::Game()
{
}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;//우리가 만든 윈도우 창 번호
	_hdc=::GetDC(hwnd);// 우리의 윈도우 도화지 번호

	::GetClientRect(hwnd, &_rect);

	_hdcBack=::CreateCompatibleDC(_hdc);//hdc와 호환되는 dc만들어준다.
	_bmpBack=::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);//_hdc와 호환되는 비트맵 생성
	// hdc와 호환하는 텍스쳐처럼 저장하게 하는 비트맵
	HBITMAP prev=	(HBITMAP)::SelectObject(_hdcBack, _bmpBack); //초기 hdcback은 크기가 _hdc가 아니므로 비트맵의 크기에 따라 일치시켜줌
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();

}

void Game::Render()
{
	uint32 fps=GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);

		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));

	}

	{
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<uint32>(deltaTime * 1000));

		::TextOut(_hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	GET_SINGLE(SceneManager)->Render(_hdcBack);
	
	//더블 버퍼링
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack,0,0,SRCCOPY);// 고속 복사해줌.
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);//백버퍼 휜색 초기화

}
