#ifndef _MAPMANAGER_H_ 
#define _MAPMANAGER_H_

/*用于实现地图管理器的功能*/

#include"BubbleDefine.h"

#define Putter_COLOR BACK_RED
#define _Putter Putter_COLOR"  "COLOR_END

typedef struct {
	char map_object[ROW][COL];//各个物品初始坐标图
}Map;

void InitPrint();//输出初始空白地图 

void PrintMap();//地图输出 

//传递xy坐标，创建给定的对象类型（第四个参数）到地图指定区域,返回bool类型表示是否成功 
bool CreatObject(Map*,int,int,char); 

//接受用户指令，并作出相应操作,传递命令参数和放置种类 
void UserControll(char,char*); 

// 清除全图 
bool ClearBMap();

//写入结果到指定文件,给定文件地址参数 
bool WriteToFile(char*); 

//读取文件入程序,给定文件地址参数 
bool ReadForFile(char*); 

//移动光标函数，接口不开放
void gotoxy(short, short); 

#endif
