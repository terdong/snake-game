#define ESC     0x1B
#define ENTER   0x0D
#define UP      0x48
#define DOWN    0x50
#define LEFT    0x4B
#define RIGHT   0x4D

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 50

#define MAP_SIZE_HEIGHT 46
#define MAP_SIZE_WIDTH 49

#define INIT_STAGE_DELAY 300

#define DEFAULT_TEXT_HEIGHT SCREEN_HEIGHT - 2
#define DEFAULT_SNAKE_POS_X 50
#define DEFAULT_SNAKE_POS_Y 25
#define DEFAULT_SNAKE_LENGTH 0
#define DEFAULT_SNAKE_LIFE 3
#define DEFAULT_SNAKE_SCORE_POINT 10

#define ADD_X 2
#define ADD_Y 1

typedef bool (*KeyEvent)(int);

typedef enum _MapState {
	EMPTY = 0,
	WALL,
	ITEM
}MapState;

typedef struct _GameInfo {
	HANDLE hOut;
	bool isGame;
	int key_ch;
	time_t delay;

	_GameInfo()
	{
	}

	_GameInfo(HANDLE _hOut, bool _isGame)
	{
		hOut = _hOut;
		isGame = _isGame;
		init();
	}

	void init()
	{
		delay = INIT_STAGE_DELAY;
	}

}GameInfo;

typedef struct _Snake {
	COORD pos_snake[2068];
	PCOORD pos_head;
	PCOORD pos_del;
	int pos_map[MAP_SIZE_WIDTH][MAP_SIZE_HEIGHT];
	int life;
	int score;
	int scoreHigh;
	int length;

	_Snake()
	{
		score = 0;
		pos_head = &pos_snake[0];
		life = DEFAULT_SNAKE_LIFE;
		init();
		init_map();
	}

	void init()
	{
		length = DEFAULT_SNAKE_LENGTH;    // 몸통이 1개면, 배열 1 위치를 삭제
		scoreHigh = score;
		score = 0;
		init_snake();
		add_tail();
	}

	void init_snake()
	{
		pos_head->X = DEFAULT_SNAKE_POS_X;
		pos_head->Y = DEFAULT_SNAKE_POS_Y;
		for (int i = 1; i < 2068; ++i) {
			pos_snake[i].X = -1;
			pos_snake[i].Y = -1;
		}
	}

	void init_map()
	{
		for (int i = 0; i < 46; ++i)
			for (int j = 0; j < 49; ++j) {
				pos_map[i][j] = EMPTY;
			}

	}

	void add_tail()
	{
		pos_del = &pos_snake[++length];
	}

	void add_tail(int num)
	{
		pos_del = &pos_snake[length += num];
	}

	void setSnakePos(bool t, int op)
	{

		for (int i = length; i > 0; --i)
		{
			pos_snake[i].X = pos_snake[i - 1].X;
			pos_snake[i].Y = pos_snake[i - 1].Y;
		}
		if (t)
		{
			pos_head->X += op;
		}
		else
		{
			pos_head->Y += op;
		}
	}

}Snake;

void init();
void sub_init();
void restart_init();

void loop();

void update();
void render();

void endMsg();                              // 종료시 메세지
void endIsGame();                           // 게임 루프 종료

void checkMap();                           // 충돌 체크
void checkItem();                           // 아이템 체크
void setRandItem(int num);                  // 아이템 리스폰

bool keyEvent(int ch);
void printStatus();
void printMsg(int x, int y, char* msg);
void printMsg(int x, int y, int num);
void printMsg(int x, int y, long num);