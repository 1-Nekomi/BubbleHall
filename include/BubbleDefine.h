#pragma once

/*type define*/
#define false 0
#define true 1
#define bool char
#define Direction int /*����*/
#define Blood int /*Ѫ��*/
#define BType long /*����*/
typedef long Count; /*��������*/
#define MAX_ROBOT 5
#define MAX_MAP_COUNT 20
#define MAX_MAP_ADDRESS 20
#define MAX_BOMB_COUNT 10

/*color define*/
#define COLOR_END           "\033[0m"     
#define BROWN               "\033[0;33m"         //��ƣ���ɫ�� 
#define GOLDEN              "\033[1;33m"         //��ɫ��ǳ�ƣ� 
#define GREEN               "\033[0;32m"         //���̣�����
#define L_GREEN             "\033[1;32m"         //����
#define BLUE                "\033[0;34m"         //����������
#define L_BLUE              "\033[1;34m"         //������ƫ�׻�
#define PURPLE              "\033[0;35m"         //��ۣ����ۣ�ƫ����
#define L_PURPLE            "\033[1;35m"         //���ۣ�ƫ�׻�
#define RED                 "\033[0;31m"         //��죬����
#define L_RED               "\033[1;31m"         //�ʺ�

/*�������ɫ*/
#define BACK_BLACK          "\033[0;40m"         //�� 
#define BACK_RED            "\033[0;41m"         //�� 
#define BACK_GREEN        "\033[0;42m"           //��
#define BACK_YELLOW         "\033[0;43m"         //�� 
#define BACK_BLUE           "\033[0;44m"         //�� 
#define BACK_PURPLE         "\033[0;45m"         //�� 
#define BACK_CYAN          "\033[1;46m"         //��ɫ 
#define BACK_WHITE          "\033[1;47m"         //�� 

/*object color define*/
#define ROAD_COLOR			BACK_WHITE
#define WALL_COLOR			BACK_BLACK                       //ǽ ��ɫ����
#define PLAYER_COLOR		BACK_BLUE                    //��� ��ɫ���� 
#define ROBOT_COLOR			BACK_PURPLE   	              //�˻� ��ɫ����
#define GRASS_COLOR			BACK_GREEN                    //�� ��ɫ���� 
#define EVENT_COLOR			BACK_CYAN 				      //�¼� ��ɫ����
#define BOMB_COLOR			BACK_RED					//ը�� ��ɫ����
#define ROBOT_BORN_COLOR 	BACK_YELLOW					//��������� 

/* object output define*/
#define _ROAD		ROAD_COLOR"  "         
#define _WALL		WALL_COLOR "  "     
#define _GRASS		GRASS_COLOR"  "
#define _PLAYER		PLAYER_COLOR""
#define _ROBOT		ROBOT_COLOR""
#define _EVENT		EVENT_COLOR"��"
#define _BOMB		BOMB_COLOR""
#define _BORN		ROBOT_BORN_COLOR"  " 

/*direction define*/
#define LEFT		0x0020
#define RIGHT		0x0021
#define FRONT		0x0022
#define BACK		0x0023

/*buff define*/
#define SPECIAL_BOMB				0x0030	//����ը��buff
#define BD_REPLY_STATIC				0x0031	//Ѫ��ֱ�ӻظ�buff
#define BD_REPLY_DYNAMIC			0x0032	//Ѫ�������ָ�buff

/*bomb define*/
#define ORDINARY_BOMB		0x0040		//����ը��
#define CONTROLL_BOMB		0x0041		//ң��ը��

/*bomb range define*/
#define CROSS		0x0051 //ʮ��

/*object define*/
#define ROAD		'0'
#define WALL		'1'
#define GRASS		'2'
#define PLAYER		'3'
#define ROBOT		'4'
#define BORN		'5'
#define BOMB		'6'
#define EVENT		'7'


/*map attribute define*/
#define ROW 12 //12��
#define COL 12 //12��

/*short name define*/
typedef unsigned int u_int;
typedef unsigned char u_char;
