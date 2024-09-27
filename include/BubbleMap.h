#ifndef BUBBLEMAP_H  
#define BUBBLEMAP_H 

/*�ò������ڴ��������õ�ͼ�йز���
	���磺��ͼ��ȡ����ͼ�������ɫ�ƶ�
	��Ʒ���õȵ�*/

#include<stdio.h>
#include"BubbleDefine.h"

typedef struct {
	char map_object[ROW][COL];//������Ʒ��ʼ����ͼ
}Map;

/*-----------------------------------
			ͨ��*/

typedef struct {
	int x;
	int y;
}XY;//����

typedef struct {
	BType name;/*buff����*/
	Count range;/*buff����*/
}Buff;

typedef struct {
	BType identity;//���
	int index;//λ���б��е��±�
	XY pxy;//����
	Blood bd;//Ѫ��
	Count bomb;//ը������
	Buff buff[5];//������������buff
	Count Buff_Num;
}Role;//��ɫ����

typedef struct {
	BType bomb;//ը������
	int power;//ը���˺�
	XY bxy;//ը������
	int range;//ը����ը��Χ
	Count distance;//ը����ը����
	Count step;//ը����ը����
	BType Owner;//ը��������
	int Owner_index;//�������ڽ�ɫ�б��е��±�
}Bomb;

typedef struct {
	Bomb list[MAX_BOMB_COUNT];//��ͼը���б�
	int bomb_count;//��ͼը������
}BombList;

typedef struct {
	Role list[MAX_ROBOT + 1];//��ɫ�б�0�±�Ĭ��Ϊ���,��ͼ���������˻�
	Count count;//�˻�����
}RolesList;

/*---------------------------------*/


/*���ڶ�ȡbmap�ļ��ĵ�ͼ*/
bool BmapReader(Map*,const char*);

/*���bmap�ļ�����*/
void PrintBmap(Map,RolesList,BombList);

// ����: �ռ�Ŀ¼path����ģʽchREƥ��������ļ���������������intָ�����Ӧ��ά����ָ��
char** SearchDir(const char*, const char*,int*);

/*���ù����ļ���ַ*/
bool ReSetAddress(char*);

/*����̨���*/
bool ClearConsole();

/*�ؿ�ѡ��*/
bool StageSelect(char * address,const char order);

/*��Ʒ����Ķ�*/
bool ObjectMove(Map*,XY*, Direction);

/*��Ʒ����*/
bool ObjectSet(Map*, const int x, const int y, const char type);

/*�����Ӧ�����ϵ���Ʒ*/
bool ObjectDrop(Map*, const int x, const int y);

//����̨�����ƺ���
void gotoxy(const short x, const short y);

/*��ȡ����̨���λ��*/
bool getxy(int *x,int *y);

#endif