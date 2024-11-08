#include "pch.h"
#include "ObjectManager.h"
#include "Object.h"


IMPLEMENT_SINGLETON(ObjectManager);

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Add(Object* object)
{
	if (object == nullptr)return;

	auto findIt=std::find(_objects.begin(), _objects.end(), object);
	if (findIt != _objects.end()) {
		return;
	}
	_objects.push_back(object);
}

void ObjectManager::Remove(Object* object)
{
	if (object == nullptr)return;
	_objects.erase(remove(_objects.begin(), _objects.end(), object),_objects.end());

	//TODO:±¦ÂúÀ»±î?
	delete object;
}

void ObjectManager::Clear()
{
	for_each(_objects.begin(), _objects.end(), [=](Object* obj) {delete obj; });

		_objects.clear();
}
