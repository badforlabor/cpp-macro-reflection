
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

#pragma message("undefine MACRO_IMPLE")
#undef MACRO_IMPLE
#include "macro_reflection.h"
#include "db2gs_protocol.h"

#pragma message("define MACRO_IMPLE")
#define MACRO_IMPLE
#include "macro_reflection.h"
#include "db2gs_protocol.h"
