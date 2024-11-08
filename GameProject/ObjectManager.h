#pragma once

class Object;

class ObjectManager
{
	DECLARE_SINGLETON(ObjectManager);
public:
	~ObjectManager();

	void Add(Object* object);
	void Remove(Object* object);
	void Clear();
	const vector<Object*>& GetObjects() { return _objects; }

public:
	template<typename T>
	T* CreateObject() {

		//type trait
		static_assert(std::is_convertible_v<T*, Object*>);
		//컴파일 타임에 해당 타입 T가 Init함수 가 있는지 확인해주는

		T* object = new T();
		object->Init();
		return object;
	}


private:
	vector<Object*> _objects;
};

