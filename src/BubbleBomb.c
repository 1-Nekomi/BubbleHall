#include"BubbleBomb.h"
#include<string.h>

bool InitBombList(BombList* Blist) {
	if (Blist == NULL) {
		return false;
	}

	Blist->bomb_count = 0;
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		Blist->list[i].bomb = NULL;
		Blist->list[i].bxy.x = EOF;
		Blist->list[i].bxy.y = EOF;
	}
	return true;
}

bool BombSet(Map* map, BombList* Blist, Role* role) {
	if (map == NULL || Blist == NULL || Blist->bomb_count > MAX_BOMB_COUNT || role->bomb<=0) {
		return false;
	}

	Bomb bomb;
	bomb.bomb = NULL;

	for (int i = 0; i < role->Buff_Num; i++) {
		if (role->buff[i].name == SPECIAL_BOMB) {
			switch (role->buff[i].range) {
			case CONTROLL_BOMB + CROSS:
				bomb.bomb = CONTROLL_BOMB;
				bomb.range = CROSS;
				bomb.step = -1;
			}
		}
	}

	if (bomb.bomb == NULL) {
		bomb.bomb = ORDINARY_BOMB;
		bomb.range = CROSS;
		bomb.step = 3;
	}
	
	bomb.bxy.x = role->pxy.x;
	bomb.bxy.y = role->pxy.y;//坐标
	bomb.Owner = role->identity;//布置者
	bomb.Owner_index = role->index;
	bomb.distance = 1;
	bomb.power = 1;

	AddBombList(bomb, Blist);
	role->bomb--;
	printf("炸弹放置成功\n");
	
	return true;
}

bool AddBombList(Bomb bomb, BombList* Blist) {
	if (Blist == NULL) {
		return false;
	}
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (Blist->list[i].bomb == NULL && Blist->list[i].bxy.x == EOF && Blist->list[i].bxy.y == EOF) {
			Blist->list[Blist->bomb_count] = bomb;
			Blist->bomb_count++;
			return true;
		}
	}
	
	return false;
}

bool DelBombList(Bomb bomb, BombList* Blist) {
	if (Blist == NULL) {
		return false;
	}

	int Bcount = Blist->bomb_count;
	for (int i = 0; i < Bcount; i++) {
		if (Blist->list[i].bxy.x == bomb.bxy.x && Blist->list[i].bxy.y == bomb.bxy.y) {

			Blist->list[i].bomb = NULL;
			Blist->list[i].bxy.x = EOF;
			Blist->list[i].bxy.y = EOF;
			Blist->bomb_count--;

			return true;
		}
	}
	return false;
}

bool CheckBomb(Map* map,RolesList* Rlist,BombList* Blist) {
	if (map == NULL || Rlist == NULL || Blist == NULL) {
		return false;
	}
	//用于玩家移动后自检
	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (Blist->list[i].bomb == ORDINARY_BOMB && Blist->list[i].step > 0) {
			Blist->list[i].step--;
		}
	}//步距自检

	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (map->map_object[Blist->list[i].bxy.x][Blist->list[i].bxy.y] == ROAD) {
			PutObject(map, Blist->list[i].bxy.x, Blist->list[i].bxy.y, BOMB);
		}
	}//布置检测

	for (int i = 0; i < MAX_BOMB_COUNT; i++) {
		if (Blist->list[i].bomb == ORDINARY_BOMB && Blist->list[i].step == 0) {
			//炸弹伤害判定
			BombDamage(map, Rlist, &Blist->list[i].bomb);
			DelBombList(Blist->list[i], Blist);
		}
	}
}

static void BombDamage_helper(Map* map,RolesList* Rlist,Bomb* bomb,int x,int y) {
	if (x>=ROW || y>=COL || x<0 || y<0 ) {
		return;
	}
	else {
		if (map->map_object[x][y] == WALL || map->map_object[x][y] == ROAD) {
			return;
		}

		int index;
		switch (map->map_object[x][y]) {
		case PLAYER:Rlist->list[0].bd -= bomb->power; break;
		case ROBOT:
			if (bomb->Owner == PLAYER) {
				index = SearchRobot(*Rlist, x, y);
				Rlist->list[index].bd -= bomb->power;
				break;
			}
			break;
		case GRASS:
			if (bomb->Owner == PLAYER) {
				ObjectDrop(map,x,y); 
				break;
			}
			break;
		}
	}
	
	
}

bool BombDamage(Map* map, RolesList* Rlist, Bomb* bomb) {
	if (map == NULL || Rlist == NULL || bomb == NULL) {
		return false;
	}

	int bx = bomb->bxy.x;
	int by = bomb->bxy.y;

	//上下左右依次检测
	int temp_distance = 1;
	while (temp_distance <= bomb->distance) {
		BombDamage_helper(map,Rlist,bomb,bx-1,by);
		BombDamage_helper(map, Rlist, bomb, bx + 1, by);
		BombDamage_helper(map, Rlist, bomb, bx, by - 1);
		BombDamage_helper(map, Rlist, bomb, bx, by + 1);
		temp_distance++;
	}
	ObjectDrop(map, bx, by);
	Rlist->list[bomb->Owner_index].bomb++;//归还炸弹

	return true;
}