#pragma once

/*type define*/
#define false 0
#define true 1
#define bool char
#define Direction int /*方向*/
#define Blood int /*血量*/
#define BType long /*种类*/
typedef long Count; /*数量类型*/
#define MAX_ROBOT 5
#define MAX_MAP_COUNT 20
#define MAX_MAP_ADDRESS 20
#define MAX_BOMB_COUNT 10

/*color define*/
#define COLOR_END           "\033[0m"     
#define BROWN               "\033[0;33m"         //深黄（棕色） 
#define GOLDEN              "\033[1;33m"         //金色（浅黄） 
#define GREEN               "\033[0;32m"         //深绿，暗绿
#define L_GREEN             "\033[1;32m"         //鲜绿
#define BLUE                "\033[0;34m"         //深蓝，暗蓝
#define L_BLUE              "\033[1;34m"         //亮蓝，偏白灰
#define PURPLE              "\033[0;35m"         //深粉，暗粉，偏暗紫
#define L_PURPLE            "\033[1;35m"         //亮粉，偏白灰
#define RED                 "\033[0;31m"         //深红，暗红
#define L_RED               "\033[1;31m"         //鲜红

/*背景填充色*/
#define BACK_BLACK          "\033[0;40m"         //黑 
#define BACK_RED            "\033[0;41m"         //红 
#define BACK_GREEN        "\033[0;42m"           //绿
#define BACK_YELLOW         "\033[0;43m"         //黄 
#define BACK_BLUE           "\033[0;44m"         //蓝 
#define BACK_PURPLE         "\033[0;45m"         //紫 
#define BACK_CYAN          "\033[1;46m"         //青色 
#define BACK_WHITE          "\033[1;47m"         //白 

/*object color define*/
#define ROAD_COLOR			BACK_WHITE
#define WALL_COLOR			BACK_BLACK                       //墙 黑色背景
#define PLAYER_COLOR		BACK_BLUE                    //玩家 蓝色背景 
#define ROBOT_COLOR			BACK_PURPLE   	              //人机 紫色背景
#define GRASS_COLOR			BACK_GREEN                    //草 绿色背景 
#define EVENT_COLOR			BACK_CYAN 				      //事件 青色背景
#define BOMB_COLOR			BACK_RED					//炸弹 红色背景
#define ROBOT_BORN_COLOR 	BACK_YELLOW					//怪物出生点 

/* object output define*/
#define _ROAD		ROAD_COLOR"  "         
#define _WALL		WALL_COLOR "  "     
#define _GRASS		GRASS_COLOR"  "
#define _PLAYER		PLAYER_COLOR""
#define _ROBOT		ROBOT_COLOR""
#define _EVENT		EVENT_COLOR"？"
#define _BOMB		BOMB_COLOR""
#define _BORN		ROBOT_BORN_COLOR"  " 

/*direction define*/
#define LEFT		0x0020
#define RIGHT		0x0021
#define FRONT		0x0022
#define BACK		0x0023

/*buff define*/
#define SPECIAL_BOMB				0x0030	//特殊炸弹buff
#define BD_REPLY_STATIC				0x0031	//血量直接回复buff
#define BD_REPLY_DYNAMIC			0x0032	//血量持续恢复buff

/*bomb define*/
#define ORDINARY_BOMB		0x0040		//步感炸弹
#define CONTROLL_BOMB		0x0041		//遥控炸弹

/*bomb range define*/
#define CROSS		0x0051 //十字

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
#define ROW 12 //12行
#define COL 12 //12列

/*short name define*/
typedef unsigned int u_int;
typedef unsigned char u_char;
