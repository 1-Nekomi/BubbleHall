#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include"BubbleMap.h"
#include"BubbleRoles.h"
#include"BubbleBomb.h"

char Address[25] = { '\0'};//��ͼ�ļ���


int main() {
	Map map;
	RolesList Rlist;
	BombList Blist;

	strcpy_s(Address,strlen("./map")+1,"./map");
	
	bool IsCreateObject = false;
	bool IsGaming = false;

	//���ؿ���̨���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬

	char order;
	while (1) {
		
		while (IsGaming == false) {
			gotoxy(0, 0);
			printf("ѡ��ؿ���(ws����ѡ��)\n");
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
				printf("��ͼ��ȡʧ��\n");
				system("pause");
				IsGaming = false;
				continue;
			}
			if (!InitRolesList(map,&Rlist) || !InitBombList(&Blist)) {
				printf("��ͼ����ʧ��\n");
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
		

		printf(BROWN"wsad�������,Ctrl+'+'���Ŵ��ͼ��Ctrl+'-'����С��ͼ\n��Enter����ը��\n"COLOR_END);
		if (_kbhit()) {
			order = _getch();
			if (order == 27 && IsGaming == true && IsCreateObject == true) {
				//ESC��ֵ
				IsGaming = false;
				IsCreateObject = false;
				ReSetAddress(Address);
				ClearConsole();
				continue;
			}
			if (PlayerMove(&map, &Rlist.list[0], order)) {
				CheckBomb(&map, &Rlist, &Blist);
				gotoxy(0, 14);//��ʾ��Ϣ���
				printf("                                                                    ");
			}
			if (order == '\r' && IsGaming == true && IsCreateObject == true) {
				BombSet(&map, &Blist, &Rlist.list[0]);
			}
			PrintPlayer(Rlist);
		}

		if (CheckRoleStatus(&map,&Rlist)) {
			printf(L_RED"\n�������,���س����¿�ʼ\n"COLOR_END);
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