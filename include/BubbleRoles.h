#pragma once

/*�ⲿ�����ڴ����ɫ�����Ϣ
	���磺�ƶ���Ѫ����buff�ȵ�*/

#include<stdio.h>
#include"BubbleDefine.h"
#include"BubbleMap.h"



/*---------------------------------------
				ͨ��*/



/*---------------------------------------*/

/*��Ʒ����*/
bool PutObject(Map*, int, int, char);

/*��ɫ�б��ʼ��*/
bool InitRolesList(Map,RolesList*);

/*����ɫ�б������н�ɫ״̬,�������������true,���˻���������ն�Ӧ�б����*/
bool CheckRoleStatus(Map*,RolesList*);

/*--------------------------------------*/



/*---------------------------------------
				���*/

//�ڵ�ͼ��Ѱ����ң���������Ӧ����Ҷ���
bool CreatPlayerObeject(Map,Role*);

/*����ƶ�*/
bool PlayerMove(Map*,Role*,char);

/*�����Ϣ���*/
void PrintPlayer(RolesList);

/*--------------------------------------*/



/*---------------------------------------
				�˻�*/

/*�������꣬�ڽ�ɫ���в��Ҷ�Ӧ�˻������ر����±�*/
int SearchRobot(RolesList,int x,int y);

/*--------------------------------------*/

