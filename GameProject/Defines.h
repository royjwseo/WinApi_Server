#pragma once

/*#define DECLARE_SINGLETON(classname)			\
public:											\
static classname* GetInstance() {				\
		static classname s_instance;			\
		return &s_instance;						\
	}											\
private:										\
				classname(){}	*/				\



#define DECLARE_SINGLETON(classname)\
public:										\
	static classname* GetInstance() {	\
		if (s_instance == nullptr) {		\
			s_instance = new classname();\
		}									\
		return s_instance;					\
	}										\
private:									\
	classname() {}						\
private:									\
	static classname* s_instance;		\

// 함부로 다른데서 생성못하게, 싱글톤이므로.
	
#define IMPLEMENT_SINGLETON(classname) \
classname* classname::s_instance=nullptr;\


#define GET_SINGLE(classname) classname::GetInstance()