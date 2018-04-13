
/************************************************************************/
/* 例子！
	用macro_reflection.h包裹两遍my_struct.h即可。
*/
/************************************************************************/

#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include "inside_type.h"

#include "binary.h"

#undef MACRO_IMPLE
#undef MACRO_ZERO 
#include "macro_reflection.h"
#include "my_struct.h"

#define MACRO_IMPLE
#undef MACRO_ZERO
#include "macro_reflection.h"
#include "my_struct.h"

#define MACRO_IMPLE
#define MACRO_ZERO
#include "macro_reflection.h"
#include "my_struct.h"
