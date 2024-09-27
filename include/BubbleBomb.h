#ifndef _BUBBLEUI_H_
#define _BUBBLEUI_H_

#include"BubbleDefine.h"
#include"BubbleRoles.h"


/*炸弹列表初始化*/
bool InitBombList(BombList*);

/*炸弹放置*/
bool BombSet(Map*, BombList*, Role*);

/*将炸弹加入列表*/
bool AddBombList(Bomb,BombList*);

/*将炸弹删除列表*/
bool DelBombList(Bomb, BombList*);

/*炸弹自检*/
bool CheckBomb(Map*,RolesList*,BombList*);

/*炸弹伤害判定*/
bool BombDamage(Map*,RolesList*,Bomb*);

#endif // !_BUBBLEUI_H_

