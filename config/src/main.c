#include <stdio.h>
#include<windows.h>
#include<conio.h>
#include"MapManager.h"


int main() {
	
	//���ؿ���̨���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
	
	InitPrint();
	
	char ObjectType = '1';
	while(1){
		
		PrintMap();
		printf("������wasd���Ʋ��÷��飬��enter���в���\n����Ӧ�����л����õ���Ʒ��\n"); 
		printf("0.·\n1.ǽ\n2.��\n3.���\n4.������\n5.�����˳����㣨�̶��������������ˣ�\n");
		printf("\nc������յ�ͼ\ne����д��mapĿ¼�е�map.bmap�ļ�(λ�ڿ�ִ���ļ�����һ��Ŀ¼)\nr������ȡָ��bmap�ļ�\n");
		char order;
		
		printf("\n��ǰ�������ã�");
		switch(ObjectType){
			case ROAD:printf("·��      \n");break;
			case WALL:printf("ǽ��      \n");break;
			case GRASS:printf("�ݴ�      \n");break;
			case PLAYER:printf("���      \n");break;
			case ROBOT:printf("�˻�      \n");break;
			case BORN:printf("�˻�������\n");break;
		}
		
		if (_kbhit()) {
		    order = _getch();
		    UserControll(order,&ObjectType);
		}
		
		gotoxy(0,0);
		
	}
	return 0;
}
