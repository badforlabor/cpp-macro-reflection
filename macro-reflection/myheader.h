
/************************************************************************/
/* 例子！
	用macro_reflection.h包裹两遍my_struct.h即可。
*/
/************************************************************************/

#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include "raw.h"

#undef MACRO_IMPLE
#include "macro_reflection.h"
#include "my_struct.h"

#define MACRO_IMPLE
#include "macro_reflection.h"
#include "my_struct.h"
