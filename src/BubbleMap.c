#include"BubbleMap.h"
#include<windows.h>
#include<io.h>
#include <direct.h>

bool BmapReader(Map* map,const char* Address) {
	FILE* fp = fopen(Address,"r");
	if (fp == NULL) {
		printf("路径为%s的文件不存在或打开失败\n", Address);
		return false;
	}
	
	fread(map, sizeof(Map), 1, fp);

	fclose(fp);
	return true;
}

void PrintBmap(Map map,RolesList Rlist,BombList Blist) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			
			switch (map.map_object[i][j]) {
				case ROAD:printf(_ROAD); break;
				case WALL:printf(_WALL); break;
				case GRASS:printf(_GRASS); break;
				case PLAYER:printf(_PLAYER"%d ", Rlist.list[0].bd); break;
				case ROBOT:
					for (int k = 1; k < MAX_ROBOT+1; k++) {
						if (Rlist.list[k].pxy.x == i && Rlist.list[k].pxy.y == j) {
							printf(_ROBOT"%d ", Rlist.list[k].bd);
							break;
						}
					}break;
				case EVENT:printf(_EVENT); break;
				case BOMB:
					for (int k = 0; k < MAX_BOMB_COUNT; k++) {
						if (Blist.list[k].bxy.x == i && Blist.list[k].bxy.y == j) {
							printf(_BOMB"%d ", Blist.list[k].step);
							break;
						}
					}
					break;
				case BORN:printf(_BORN); break;
			}
			
		}
		printf(COLOR_END"\n");
	}
	printf(COLOR_END);
}
  
char** SearchDir(const char* path, const char* chRE,int* Num) {
	char* chCurPath = getcwd(NULL, 0); // 当前工作目录  

	if (chCurPath == 0) {
		return NULL;
	}

	int ret = _chdir(path);
	if (ret < 0) {
		perror(path);
		free(chCurPath);
		return NULL; // 直接返回以避免后续错误  
	}

	char** s = (char**)malloc(sizeof(char*) * MAX_MAP_COUNT);
	if (s == NULL) {
		return NULL;
	}

	struct _finddata_t data;
	intptr_t hnd = _findfirst(chRE, &data); // 查找第一个匹配的文件

	if (hnd < 0) {
		perror("文件打开错误\n");
		free(chCurPath);
		return NULL; // 直接返回以避免后续错误  
	}
	

	int nRet = 1; // 这里直接初始化为1  
	do {
		int data_length = (int)strlen(data.name);

		if (data_length > MAX_MAP_ADDRESS) {
			continue;
		}
		char* Data = (char*)malloc(sizeof(char) * MAX_MAP_ADDRESS);
		if (Data == NULL) {
			return NULL;
		}

		for (int i = 0; i < MAX_MAP_ADDRESS; i++) {
			Data[i] = '\0';
		}

		for (int i = 0; i < data_length; i++) {
			Data[i] = data.name[i];
		}
		s[*Num] = Data;
		(*Num)++;
		if (*Num == MAX_MAP_COUNT) {
			printf("文件数量超出最大支持上限20\n");
			break;
		}
		nRet = _findnext(hnd, &data);
	} while (nRet == 0);

	_findclose(hnd); // 关闭当前句柄  
	ret = _chdir(chCurPath); // 切换回之前的工作目录  
	free(chCurPath);
	return s;
}

bool ReSetAddress(char* Address) {
	if (Address == NULL) {
		return false;
	}

	int Add_length = (int)strlen(Address);
	for (int i = 0; i < Add_length; i++) {
		Address[i] = '\0';
	}
	strcpy_s(Address, strlen("./map") + 1, "./map");
	return true;
}

bool ClearConsole() {
	gotoxy(0, 0);
	for (int i = 0; i < 30; i++) {
		printf("                                                                      ");
	}
	gotoxy(0, 0);
	return true;
}

bool StageSelect(char * address,const char order) { 
	const char* chRE = "*.bmap"; // 匹配所有地图文件
	static int ch = 0;
	int StageNum = 0;
	char** data = SearchDir(address, chRE, &StageNum);
	if (data == NULL) {
		return false;
	}

	for (int i = 0; i < StageNum; i++) {
		if (i == ch) {
			printf(BACK_RED"[%s]\n"COLOR_END, data[i]);
			continue;
		}
		printf("[%s]", data[i]);
		for (int j = 0; j < MAX_MAP_ADDRESS; j++) {
			printf(" ");
		}
		printf("\n");
	}


	if (order == 'w' || order == 'W') {
		if (ch - 1 >= 0) {
			ch--;
		}
	}
	else if (order == 's' || order == 'S') {
		if (ch + 1 < StageNum) {
			ch++;
		}
	}
	else if (order == '\r') {
		int add_length = (int)strlen(address);
		int data_length = (int)strlen(data[ch]);
		strcat_s(address, add_length + 2, "/");
		strcat_s(address,add_length+data_length+2,data[ch]);
		return true;
	}
	
	return false;
}

bool ObjectMove(Map* map,XY* pxy, Direction dir) {
	if (map == NULL || pxy == NULL) {
		return false;
	}

	if (dir == FRONT) {
		if (pxy->x - 1 >= 0 && map->map_object[pxy->x - 1][pxy->y] == ROAD) {
			map->map_object[pxy->x - 1][pxy->y] = map->map_object[pxy->x][pxy->y];
			map->map_object[pxy->x][pxy->y] = ROAD;
			pxy->x--;
		}
		else return false;
	}
	else if (dir == BACK ) {
		if (pxy->x+1 < ROW && map->map_object[pxy->x+1][pxy->y] == ROAD) {
			map->map_object[pxy->x + 1][pxy->y] = map->map_object[pxy->x][pxy->y];
			map->map_object[pxy->x][pxy->y] = ROAD;
			pxy->x++;
		}
		else return false;
	}
	else if (dir == RIGHT) {
		if (pxy->y+1 < COL && map->map_object[pxy->x][pxy->y+1] == ROAD) {
			map->map_object[pxy->x][pxy->y + 1] = map->map_object[pxy->x][pxy->y];
			map->map_object[pxy->x][pxy->y] = ROAD;
			pxy->y++;
		}
		else return false;
	}
	else if (dir == LEFT) {
		if (pxy->y-1 >= 0 && map->map_object[pxy->x][pxy->y-1] == ROAD) {
			map->map_object[pxy->x][pxy->y - 1] = map->map_object[pxy->x][pxy->y];
			map->map_object[pxy->x][pxy->y] = ROAD;
			pxy->y--;
		}
		else return false; 
	}
	return true;
}

bool ObjectSet(Map* map, const int x, const int y, const char type) {
	if (map == NULL) {
		return false;
	}
	map->map_object[x][y] = type;
	return true;
}

bool ObjectDrop(Map* map, const int x, const int y) {
	if (map == NULL || x < 0 || x >= ROW || y<0 || y>=COL) {
		return false;
	}
	map->map_object[x][y] = ROAD;
	return true;
}

void gotoxy(const short x, const short y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool getxy(int *x,int *y) {
	if (x == NULL || y == NULL) {
		return false;
	}
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*x = csbi.dwCursorPosition.X;
	*y = csbi.dwCursorPosition.Y;

	return true;
}