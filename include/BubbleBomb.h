#ifndef _BUBBLEUI_H_
#define _BUBBLEUI_H_

#include"BubbleDefine.h"
#include"BubbleRoles.h"


/*ը���б��ʼ��*/
bool InitBombList(BombList*);

/*ը������*/
bool BombSet(Map*, BombList*, Role*);

/*��ը�������б�*/
bool AddBombList(Bomb,BombList*);

/*��ը��ɾ���б�*/
bool DelBombList(Bomb, BombList*);

/*ը���Լ�*/
bool CheckBomb(Map*,RolesList*,BombList*);

/*ը���˺��ж�*/
bool BombDamage(Map*,RolesList*,Bomb*);

#endif // !_BUBBLEUI_H_

