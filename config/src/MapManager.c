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
			else if(map.map_object[i][j] == ROAD) { // ·�� ����ɫ�����ո� 
				printf(_ROAD); 
			}
			else if(map.map_object[i][j] == WALL) { // ǽ�� ����ɫ�����ո� 
				printf(_WALL); 
			}
			else if(map.map_object[i][j] == GRASS) { // �ݵ� ����ɫ�����ո� 
				printf(_GRASS); 
			}
			else if(map.map_object[i][j] == PLAYER) { // ��� ����ɫ�����ˣ� 
				printf(_PLAYER); 
			}
			else if(map.map_object[i][j] == ROBOT) { // �˻� (��ɫ�������� 
				printf(_ROBOT); 
			}
			else if(map.map_object[i][j] == BORN) { //�˻������� ����ɫ������ 
				printf(_BORN);
			}
		}
		printf(COLOR_END"\n");
	}
} 

bool CreatObject(Map* map,int x,int y,char type) {
	if(map == NULL) {
		printf("ָ��Ϊ��");
		Tip++;
		return false;
	}
	if(x<0 || x>ROW || y<0 || y>COL){
		printf("������Ч");
		Tip++;
		return false;
	}
	if(type!=ROAD && map->map_object[x][y]!=ROAD) { // ���ڼ��õ��Ƿ�ռ�� 
		printf("������λ����ռ��");
		Tip++;
		return false;
	} 
	if(type == PLAYER && IsPlayerCreated == true){
		printf("����Ѵ���");
		Tip++;
		return false;
	}
	if(type == ROBOT && Robot >= 5){
		printf("�˻������Ѵ�����");
		Tip++;
		return false;
	}
	if(type == BORN && Born >=3){
		printf("�˻������������Ѵ�����");
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
			//���һ�����ʱ�����뻻�з�,�ص���ʾ��Ϣ��ʼ���� 
			printf("                                                    \n");
			printf("                                                    ");
			gotoxy(0,ROW+15); 
			Tip--;
			continue;
		}
		printf("                                                       \n");
		Tip--;
	}
	
	
	if(order == 'w' || order == 'W') { // ���� 
		if(x>0){
			x--;
		}
	}
	else if(order == 's' || order == 'S') { // ���� 
		if(x<ROW-1){
			x++;
		}
	}
	else if(order == 'd' || order == 'D') { // ����
		if(y<COL-1){
			y++;
		} 
	}
	else if(order == 'a' || order == 'A') { // ���� 
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
	else if(order == 'c' || order == 'C') {	// ���ȫͼ 
		ClearBMap();
	}
	else if(order == 'e' || order == 'E') { // д���ļ� 
		WriteToFile("../map/map.bmap"); 
	}
	else if(order == 'r' || order == 'R') { // ��ȡ���е�ͼ�ļ� 
		char s[256]={'\0'};
		printf("�����ļ���ַ(���֧��256��char):\n"); 
		scanf("%s",s);
		Tip+=2;
		ReadForFile(s);
	}
	else if(order == '\r'){
		//�س���
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
		printf("�ļ����Ͳ�����bmap�ļ�");
		Tip++;
		return false;
	}
	
	FILE *fp = fopen(address,"w");
	if(fp == NULL){
		printf("�ļ��޷���");
		Tip++;
		return false;
	}
	
	fwrite(&map,sizeof(Map),1,fp);
	printf("д��ɹ�");
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
		printf("�ļ����Ͳ�����bmap�ļ�");
		Tip++;
		return false;
	}
	
	FILE *fp = fopen(address,"r");
	if(fp == NULL){
		printf("�ļ��޷���");
		Tip++;
		return false;
	}
	
	fread(&map,sizeof(Map),1,fp);
	printf("��ȡ�ɹ�");
	Tip++;
	
	fclose(fp);
	
	return true;
}

void gotoxy(short x, short y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
