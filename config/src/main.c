#include <stdio.h>
#include<windows.h>
#include<conio.h>
#include"MapManager.h"


int main() {
	
	//隐藏控制台光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	
	InitPrint();
	
	char ObjectType = '1';
	while(1){
		
		PrintMap();
		printf("请输入wasd控制布置方块，按enter进行布置\n按相应数字切换布置的物品：\n"); 
		printf("0.路\n1.墙\n2.草\n3.玩家\n4.机器人\n5.机器人出生点（固定产出三个机器人）\n");
		printf("\nc键：清空地图\ne键：写入map目录中的map.bmap文件(位于可执行文件的上一级目录)\nr键：读取指定bmap文件\n");
		char order;
		
		printf("\n当前正在设置：");
		switch(ObjectType){
			case ROAD:printf("路径      \n");break;
			case WALL:printf("墙体      \n");break;
			case GRASS:printf("草丛      \n");break;
			case PLAYER:printf("玩家      \n");break;
			case ROBOT:printf("人机      \n");break;
			case BORN:printf("人机出生点\n");break;
		}
		
		if (_kbhit()) {
		    order = _getch();
		    UserControll(order,&ObjectType);
		}
		
		gotoxy(0,0);
		
	}
	return 0;
}
