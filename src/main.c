#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include"BubbleMap.h"
#include"BubbleRoles.h"
#include"BubbleBomb.h"

char Address[25] = { '\0'};//地图文件夹


int main() {
	Map map;
	RolesList Rlist;
	BombList Blist;

	strcpy_s(Address,strlen("./map")+1,"./map");
	
	bool IsCreateObject = false;
	bool IsGaming = false;

	//隐藏控制台光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

	char order;
	while (1) {
		
		while (IsGaming == false) {
			gotoxy(0, 0);
			printf("选择关卡：(ws控制选择)\n");
			char order = '\0';
			if (_kbhit()) {
				order = _getch();
			}
			if (StageSelect(Address, order)) {
				IsGaming = true;
			}
			
		}

		gotoxy(0, 0);

		if (IsCreateObject == false && IsGaming == true) {
			if (!BmapReader(&map, Address)) {
				printf("地图读取失败\n");
				system("pause");
				IsGaming = false;
				continue;
			}
			if (!InitRolesList(map,&Rlist) || !InitBombList(&Blist)) {
				printf("地图配置失败\n");
				system("pause");
				IsGaming = false;
				continue;
			}
			IsCreateObject = true;
			
		}
		
		
		if (IsCreateObject == false || IsGaming == false) {
			IsCreateObject = false;
			IsGaming = false;
			continue;
		}

		
		PrintBmap(map, Rlist, Blist);
		

		printf(BROWN"wsad控制玩家,Ctrl+'+'来放大地图，Ctrl+'-'来缩小地图\n按Enter放置炸弹\n"COLOR_END);
		if (_kbhit()) {
			order = _getch();
			if (order == 27 && IsGaming == true && IsCreateObject == true) {
				//ESC键值
				IsGaming = false;
				IsCreateObject = false;
				ReSetAddress(Address);
				ClearConsole();
				continue;
			}
			if (PlayerMove(&map, &Rlist.list[0], order)) {
				CheckBomb(&map, &Rlist, &Blist);
				gotoxy(0, 14);//提示信息清除
				printf("                                                                    ");
			}
			if (order == '\r' && IsGaming == true && IsCreateObject == true) {
				BombSet(&map, &Blist, &Rlist.list[0]);
			}
			PrintPlayer(Rlist);
		}

		if (CheckRoleStatus(&map,&Rlist)) {
			printf(L_RED"\n玩家死亡,按回车重新开始\n"COLOR_END);
			gotoxy(0, 0);
			PrintBmap(map, Rlist, Blist);
			order = _getch();
			if (order == '\r') {
				IsCreateObject = false;
				ClearConsole();
			}
			else {
				IsGaming = false;
				IsCreateObject = false;
				ReSetAddress(Address);
				ClearConsole();
				continue;
			}
			
		}
	}
	return 0;
}