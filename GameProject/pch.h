#pragma once
//pch�� ����� ó�� �� �ѹ� ���� �ڵ忡�� �߰����ָ� ��𿡼��� �ش� ��ɵ��� ��밡��.

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Utils.h"

#include <windows.h>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <format>
using namespace std;

#define _CRTDEBUG_MAP_ALLOG
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

//// C�� ��Ÿ�� ��� �����Դϴ�.
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <math.h>
//#include <array>
//#include <vector>
//#include <numeric>
//#include <random>
//#include <cstdlib>
//
//#include <string>