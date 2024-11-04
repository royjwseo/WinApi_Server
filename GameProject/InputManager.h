#pragma once
enum class KeyState {
	None,
	Press,
	Down,
	Up,
	End
};

enum class KeyType {
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down= VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar= VK_SPACE,

	W= 'W',
	A='A',
	S='S',
	D='D',

};

enum {
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUT = static_cast<int32>(KeyState::End),
};

class InputManager
{
	DECLARE_SINGLETON(InputManager);
public:
	void Init(HWND hwnd);
	void Update();

	//������ ���� ��
	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }
	// �� ó�� ������ ��
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// �� ó�� �����ٰ� �� ��
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }
	//���콺 ��ǥ
	POINT GetMousePos() { return _mousePos; }
private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }
private:
	HWND _hwnd = {};
	vector<KeyState> _states;
	POINT _mousePos;
};

