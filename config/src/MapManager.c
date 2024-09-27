#include"MapManager.h"
#include<stdio.h>
#include<windows.h>

Map map;
int x=0,y=0;
bool IsPlayerCreated = false;
Count Tip = 0;
Count Robot = 0,Born = 0; 

void InitPrint() {
	int i,j;
	for(i = 0;i < ROW;i++) {
		for(j = 0;j < COL;j++) {
			map.map_object[i][j] = ROAD;
		}
	}
}

void PrintMap(){
	int i,j;
	for(i = 0;i < ROW;i++) {
		for(j = 0;j < COL;j++) {
			if(i == x && j == y){
				printf(_Putter);
			}
			else if(map.map_object[i][j] == ROAD) { // 路点 （白色背景空格） 
				printf(_ROAD); 
			}
			else if(map.map_object[i][j] == WALL) { // 墙点 （黑色背景空格） 
				printf(_WALL); 
			}
			else if(map.map_object[i][j] == GRASS) { // 草地 （绿色背景空格） 
				printf(_GRASS); 
			}
			else if(map.map_object[i][j] == PLAYER) { // 玩家 （黄色背景人） 
				printf(_PLAYER); 
			}
			else if(map.map_object[i][j] == ROBOT) { // 人机 (蓝色背景妖） 
				printf(_ROBOT); 
			}
			else if(map.map_object[i][j] == BORN) { //人机出生点 （黄色背景） 
				printf(_BORN);
			}
		}
		printf(COLOR_END"\n");
	}
} 

bool CreatObject(Map* map,int x,int y,char type) {
	if(map == NULL) {
		printf("指针为空");
		Tip++;
		return false;
	}
	if(x<0 || x>ROW || y<0 || y>COL){
		printf("坐标无效");
		Tip++;
		return false;
	}
	if(type!=ROAD && map->map_object[x][y]!=ROAD) { // 用于检测该点是否被占用 
		printf("该坐标位置已占用");
		Tip++;
		return false;
	} 
	if(type == PLAYER && IsPlayerCreated == true){
		printf("玩家已存在");
		Tip++;
		return false;
	}
	if(type == ROBOT && Robot >= 5){
		printf("人机数量已达上限");
		Tip++;
		return false;
	}
	if(type == BORN && Born >=3){
		printf("人机出生点设置已达上限");
		Tip++;
		return false;
	}
	
	map->map_object[x][y] = type;
	
	if(type == PLAYER){
		IsPlayerCreated = true;
	}
	if(type == ROBOT){
		Robot++;
	}
	if(type == BORN){
		Born++;
	}
	
	return true;
}

void UserControll(char order,char* type) {
	while(Tip != 0){
		if(Tip == 1){
			//最后一行清空时不输入换行符,回到提示信息开始部分 
			printf("                                                    \n");
			printf("                                                    ");
			gotoxy(0,ROW+15); 
			Tip--;
			continue;
		}
		printf("                                                       \n");
		Tip--;
	}
	
	
	if(order == 'w' || order == 'W') { // 向上 
		if(x>0){
			x--;
		}
	}
	else if(order == 's' || order == 'S') { // 向下 
		if(x<ROW-1){
			x++;
		}
	}
	else if(order == 'd' || order == 'D') { // 向右
		if(y<COL-1){
			y++;
		} 
	}
	else if(order == 'a' || order == 'A') { // 向左 
		if(y>0){
			y--;
		}
	}
	else if(order == ROAD) {
		*type = ROAD;
	}
	else if(order == WALL) {
		*type = WALL;
	}
	else if(order == GRASS) {
		*type = GRASS;
	}
	else if(order == PLAYER) {
		*type = PLAYER;
	}
	else if(order == ROBOT) {
		*type = ROBOT;
	}
	else if(order == BORN) {
		*type = BORN;
	} 
	else if(order == 'c' || order == 'C') {	// 清除全图 
		ClearBMap();
	}
	else if(order == 'e' || order == 'E') { // 写入文件 
		WriteToFile("../map/map.bmap"); 
	}
	else if(order == 'r' || order == 'R') { // 读取已有地图文件 
		char s[256]={'\0'};
		printf("输入文件地址(最多支持256个char):\n"); 
		scanf("%s",s);
		Tip+=2;
		ReadForFile(s);
	}
	else if(order == '\r'){
		//回车键
		CreatObject(&map,x,y,*type);
	}
}

bool ClearBMap() {
	int i,j;
	for(i = 0;i < ROW;i++) {
		for(j = 0;j < COL;j++) {
			map.map_object[i][j] = ROAD;
		}
	}
	IsPlayerCreated = false;
	Robot = 0;
	Born = 0;
}

bool WriteToFile(char* address) {
	char suffix[4];
	
	int slength = strlen(address);
	suffix[0] = address[slength-4];
	suffix[1] = address[slength-3];
	suffix[2] = address[slength-2];
	suffix[3] = address[slength-1];
	
	if(strcmp(suffix,"bmap") != 0){
		printf("文件类型不属于bmap文件");
		Tip++;
		return false;
	}
	
	FILE *fp = fopen(address,"w");
	if(fp == NULL){
		printf("文件无法打开");
		Tip++;
		return false;
	}
	
	fwrite(&map,sizeof(Map),1,fp);
	printf("写入成功");
	Tip++;
	
	fclose(fp);
	
	return true;
}

bool ReadForFile(char* address) {
	char suffix[4];
	
	int slength = strlen(address);
	suffix[0] = address[slength-4];
	suffix[1] = address[slength-3];
	suffix[2] = address[slength-2];
	suffix[3] = address[slength-1];
	
	if(strcmp(suffix,"bmap") != 0){
		printf("文件类型不属于bmap文件");
		Tip++;
		return false;
	}
	
	FILE *fp = fopen(address,"r");
	if(fp == NULL){
		printf("文件无法打开");
		Tip++;
		return false;
	}
	
	fread(&map,sizeof(Map),1,fp);
	printf("读取成功");
	Tip++;
	
	fclose(fp);
	
	return true;
}

void gotoxy(short x, short y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
