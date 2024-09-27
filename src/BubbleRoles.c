#include"BubbleRoles.h"
#include<windows.h>


bool PutObject(Map* map,int x, int y, char type) {
	if (map == NULL) {
		return false;
	}
	ObjectSet(map, x, y,type);
	return true;
}

bool InitRolesList(Map map,RolesList* list) {
	if (list == NULL) {
		return false;
	}

	list->count = 0;
	
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map.map_object[i][j] == PLAYER) {
				//寻找玩家
				list->list[0].identity = (BType)PLAYER;
				list->list[0].index = 0;

				list->list[0].pxy.x = i;
				list->list[0].pxy.y = j;
				
				//玩家属性初始化
				list->list[0].bd = 5;//血量
				list->list[0].bomb = 1;//炸弹数量	
				list->list[0].Buff_Num = 0; //buff数量

				list->count++;
			}
			if (map.map_object[i][j] == ROBOT) {
				//寻找人机
				list->list[list->count].identity = (BType)ROBOT;
				list->list[list->count].index = list->count;

				list->list[list->count].pxy.x = i;
				list->list[list->count].pxy.y = j;

				//人机属性初始化
				list->list[list->count].bd = 1;//血量
				list->list[list->count].bomb = 0;//炸弹数量
				list->list[list->count].Buff_Num = 0; //buff数量

				list->count++;
			}
		}
	}
	for (int i = list->count; i < MAX_ROBOT + 1; i++) {
		list->list[i].identity = (BType)NULL;
		list->list[i].bd = -1;
		list->list[i].bomb = NULL;
	}

	return true;
}

bool CheckRoleStatus(Map* map,RolesList* list) {

	for (int i = 0; i < MAX_ROBOT+1; i++) {
		if (list->list[i].bd == 0) {
			if (i == 0) {
				return true;
			}
			else {
				//置空
				list->list[i].identity = (BType)NULL;
				list->list[i].bd = -1;
				list->list[i].bomb = NULL;

				//清除地图上对应的人机
				ObjectDrop(map, list->list[i].pxy.x, list->list[i].pxy.y);

				list->count--;
			}
		}
	}
	return false;
}

bool CreatPlayerObeject(Map map,Role* role) {
	if (role == NULL) {
		return false;
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map.map_object[i][j] == PLAYER) {
				role->pxy.x = i;
				role->pxy.y = j;

				role->bd = 5;//初始血量
				role->bomb = 1;

				for (int i = 0; i < 5; i++) {
					role->buff[i].name = -1;
					role->buff[i].range = -1;
				}

				return true;
			}
		}
	}
	
	return false;
}

bool PlayerMove(Map* map,Role* role,char order) {
	if (map == NULL || role == NULL) {
		return false;
	}

	if (order == 'w' || order == 'W') {
		return ObjectMove(map,&role->pxy,FRONT);
	}
	else if (order == 's' || order == 'S') {
		return ObjectMove(map,&role->pxy, BACK);
	}
	else if (order == 'd' || order == 'D') {
		return ObjectMove(map,&role->pxy, RIGHT);
	}
	else if (order == 'a' || order == 'A') {
		return ObjectMove(map,&role->pxy, LEFT);
	}
	return false;
}

void PrintPlayer(RolesList Rlist) {

	int x = 0;
	int y = 0;
	if (!getxy(&x, &y)) {
		return;
	}

	gotoxy(30, 1);
	printf("玩家信息:        ");
	gotoxy(30, 2);
	printf("\t血量剩余：%d         ", Rlist.list[0].bd);
	gotoxy(30, 3);
	printf("\t炸弹剩余：%d         ",Rlist.list[0].bomb);
	gotoxy(30, 4);
	printf("\t坐标：(%d,%d)        ", Rlist.list[0].pxy.x,Rlist.list[0].pxy.y);
	gotoxy(x, y);
	
}

int SearchRobot(RolesList Rlist, int x, int y) {
	for (int i = 1; i < MAX_ROBOT+1; i++) {
		if (Rlist.list[i].pxy.x == x && Rlist.list[i].pxy.y == y) {
			return i;
		}
	}
	return EOF;
}

