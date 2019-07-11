
/*
	全局通用头文件
	注意！请勿轻易格式化该代码！因为每行的前后有关联
	新增的头文件应当补写在最下方
	切记！切记！
 */

#ifndef _HEADER
#define _HEADER
#include <io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>
#include <process.h>
 // 自建头文件
#include "unistd.h"
#include "structure.h"
#include "../Functions/creatList.h" // 该文件必须放在consts.h前面，structure.h后面！！！
#include "consts.h"
#include "../Functions/listOperation.h" // 该文件为工具函数集，优先级较高，应放在上面
#include "init.h"
#include "../Functions/gameOver.h"
#include "../Functions/algorithm.h"
#include "../Functions/orderFunctions.h"
#include "../Functions/riderFunctions.h"
#include "../IO/input.h"
#include "../IO/output.h"
#include "../Functions/pairtest.h"

#endif