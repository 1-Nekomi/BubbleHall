#pragma once

/*这部分用于处理角色相关信息
	例如：移动，血量，buff等等*/

#include<stdio.h>
#include"BubbleDefine.h"
#include"BubbleMap.h"



/*---------------------------------------
				通用*/



/*---------------------------------------*/

/*物品放置*/
bool PutObject(Map*, int, int, char);

/*角色列表初始化*/
bool InitRolesList(Map,RolesList*);

/*检查角色列表中所有角色状态,若玩家死亡返回true,若人机死亡则清空对应列表格子*/
bool CheckRoleStatus(Map*,RolesList*);

/*--------------------------------------*/



/*---------------------------------------
				玩家*/

//在地图上寻找玩家，并创建相应的玩家对象
bool CreatPlayerObeject(Map,Role*);

/*玩家移动*/
bool PlayerMove(Map*,Role*,char);

/*玩家信息输出*/
void PrintPlayer(RolesList);

/*--------------------------------------*/



/*---------------------------------------
				人机*/

/*给定坐标，在角色表中查找对应人机并返回表中下标*/
int SearchRobot(RolesList,int x,int y);

/*--------------------------------------*/

