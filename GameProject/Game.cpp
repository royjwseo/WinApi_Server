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
	_hwnd = hwnd;//�츮�� ���� ������ â ��ȣ
	_hdc=::GetDC(hwnd);// �츮�� ������ ��ȭ�� ��ȣ

	::GetClientRect(hwnd, &_rect);

	_hdcBack=::CreateCompatibleDC(_hdc);//hdc�� ȣȯ�Ǵ� dc������ش�.
	_bmpBack=::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);//_hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	// hdc�� ȣȯ�ϴ� �ؽ���ó�� �����ϰ� �ϴ� ��Ʈ��
	HBITMAP prev=	(HBITMAP)::SelectObject(_hdcBack, _bmpBack); //�ʱ� hdcback�� ũ�Ⱑ _hdc�� �ƴϹǷ� ��Ʈ���� ũ�⿡ ���� ��ġ������
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
	
	//���� ���۸�
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack,0,0,SRCCOPY);// ��� ��������.
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);//����� �ػ� �ʱ�ȭ

}
