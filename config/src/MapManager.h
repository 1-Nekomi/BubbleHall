#ifndef _MAPMANAGER_H_ 
#define _MAPMANAGER_H_

/*����ʵ�ֵ�ͼ�������Ĺ���*/

#include"BubbleDefine.h"

#define Putter_COLOR BACK_RED
#define _Putter Putter_COLOR"  "COLOR_END

typedef struct {
	char map_object[ROW][COL];//������Ʒ��ʼ����ͼ
}Map;

void InitPrint();//�����ʼ�հ׵�ͼ 

void PrintMap();//��ͼ��� 

//����xy���꣬���������Ķ������ͣ����ĸ�����������ͼָ������,����bool���ͱ�ʾ�Ƿ�ɹ� 
bool CreatObject(Map*,int,int,char); 

//�����û�ָ���������Ӧ����,������������ͷ������� 
void UserControll(char,char*); 

// ���ȫͼ 
bool ClearBMap();

//д������ָ���ļ�,�����ļ���ַ���� 
bool WriteToFile(char*); 

//��ȡ�ļ������,�����ļ���ַ���� 
bool ReadForFile(char*); 

//�ƶ���꺯�����ӿڲ�����
void gotoxy(short, short); 

#endif
