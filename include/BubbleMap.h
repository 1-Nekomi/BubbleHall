#ifndef BUBBLEMAP_H  
#define BUBBLEMAP_H 

/*该部分用于处理泡泡堂地图有关部分
	例如：地图读取、地图输出、角色移动
	物品放置等等*/

#include<stdio.h>
#include"BubbleDefine.h"

typedef struct {
	char map_object[ROW][COL];//各个物品初始坐标图
}Map;

/*-----------------------------------
			通用*/

typedef struct {
	int x;
	int y;
}XY;//坐标

typedef struct {
	BType name;/*buff种类*/
	Count range;/*buff幅度*/
}Buff;

typedef struct {
	BType identity;//身份
	int index;//位于列表中的下标
	XY pxy;//坐标
	Blood bd;//血量
	Count bomb;//炸弹数量
	Buff buff[5];//最多五个持续性buff
	Count Buff_Num;
}Role;//角色属性

typedef struct {
	BType bomb;//炸弹种类
	int power;//炸弹伤害
	XY bxy;//炸弹坐标
	int range;//炸弹爆炸范围
	Count distance;//炸弹爆炸距离
	Count step;//炸弹爆炸步距
	BType Owner;//炸弹布置者
	int Owner_index;//布置者在角色列表中的下标
}Bomb;

typedef struct {
	Bomb list[MAX_BOMB_COUNT];//地图炸弹列表
	int bomb_count;//地图炸弹个数
}BombList;

typedef struct {
	Role list[MAX_ROBOT + 1];//角色列表，0下标默认为玩家,地图上最多五个人机
	Count count;//人机数量
}RolesList;

/*---------------------------------*/


/*用于读取bmap文件的地图*/
bool BmapReader(Map*,const char*);

/*输出bmap文件内容*/
void PrintBmap(Map,RolesList,BombList);

// 功能: 收集目录path中与模式chRE匹配的所有文件名，并返回数量int指针和相应二维数组指针
char** SearchDir(const char*, const char*,int*);

/*重置工作文件地址*/
bool ReSetAddress(char*);

/*控制台清除*/
bool ClearConsole();

/*关卡选择*/
bool StageSelect(char * address,const char order);

/*物品坐标改动*/
bool ObjectMove(Map*,XY*, Direction);

/*物品放置*/
bool ObjectSet(Map*, const int x, const int y, const char type);

/*清除对应坐标上的物品*/
bool ObjectDrop(Map*, const int x, const int y);

//控制台光标控制函数
void gotoxy(const short x, const short y);

/*获取控制台光标位置*/
bool getxy(int *x,int *y);

#endif