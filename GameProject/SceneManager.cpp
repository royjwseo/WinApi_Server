#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "GameScene.h"

IMPLEMENT_SINGLETON(SceneManager);

void SceneManager::Init()
{
	if (_scene)_scene->Init();
}

void SceneManager::Update()
{
	if (_scene)_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)_scene->Render(hdc);
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (sceneType == _sceneType) {
		return;
	}

	Scene* newScene = nullptr;

	switch (sceneType) {
	case SceneType::DevScene:
		newScene = new DevScene();
		_sceneType = SceneType::DevScene;
		break;
	case SceneType::GameScene:
		newScene = new GameScene();
		_sceneType = SceneType::GameScene;
		break;
	}
	SAFE_DELETE(_scene);
	_scene = newScene;
	newScene->Init();
}
