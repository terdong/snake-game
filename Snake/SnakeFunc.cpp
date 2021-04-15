#include "stdafx.h"
#include "SnakeFunc's.h"

GameInfo gameInfo(GetStdHandle(STD_OUTPUT_HANDLE), true);
Snake snake;

KeyEvent ke;

void init()
{
	//  printMsg(10,10,"Hello Snake");
	COORD bfSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	SetConsoleScreenBufferSize(gameInfo.hOut, bfSize);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetCursor(false);
	sub_init();

	ke = (KeyEvent)keyEvent;

}
void sub_init()
{
	int mapCount = 0;
	for (int i = SCREEN_HEIGHT - 5; i > 1; --i)
	{
		//세로벽 ( 46개 )
		printMsg(2, i, "■");
		printMsg(SCREEN_WIDTH - 2, i, "■");
		snake.pos_map[0][mapCount] = MapState::WALL;
		snake.pos_map[48][mapCount] = MapState::WALL;
		++mapCount;
	}
	mapCount = 0;
	for (int i = 2; i < SCREEN_WIDTH; i += 2)
	{
		//가로벽 ( 49개 )
		printMsg(i, 1, "■");
		printMsg(i, SCREEN_HEIGHT - 4, "■");
		snake.pos_map[mapCount][0] = MapState::WALL;
		snake.pos_map[mapCount][45] = MapState::WALL;
		++mapCount;
	}
	printMsg(2, DEFAULT_TEXT_HEIGHT, "x :\n y :");

	printMsg(12, DEFAULT_TEXT_HEIGHT, "Life   :        ");


	printMsg(12, DEFAULT_TEXT_HEIGHT + 1, "Length :");

	printMsg(32, DEFAULT_TEXT_HEIGHT, "High Score :                 ");

	printMsg(32, DEFAULT_TEXT_HEIGHT + 1, "Score      :                 ");

	printMsg(50, DEFAULT_TEXT_HEIGHT, "Del_X :");
	printMsg(50, DEFAULT_TEXT_HEIGHT + 1, "Del_Y :");

	printStatus();

	setRandItem(1);
}

void restart_init()
{
	gameInfo.key_ch = NULL;
	if (snake.life-- != 0)
	{
		system("cls");
		sub_init();
		snake.init();
		gameInfo.init();
	}
	else
		endIsGame();
}

void loop()
{
	while (gameInfo.isGame)
	{
		Sleep(gameInfo.delay);
		update();
		render();
	}
}

void update()
{

	if (_kbhit())
	{
		gameInfo.key_ch = _getch();
		// 확장 아스키코드(방향키 등)
		if (gameInfo.key_ch == 0xE0 || gameInfo.key_ch == 0)
		{
			gameInfo.key_ch = _getch();
		}
	}
	//    keyEvent(gameInfo.key_ch);
	ke(gameInfo.key_ch);
	//time(&ltime);
	checkMap();


}

void render()
{
	COORD* pos = snake.pos_head;
	COORD* pos_del = snake.pos_del;
	printMsg(pos->X, pos->Y, "○");
	if (pos_del->X != -1 && pos_del->Y != -1)
	{
		printMsg(pos_del->X, pos_del->Y, "  ");
	}

	printStatus();
}

bool keyEvent(int ch)
{
	switch (ch)
	{
	case ESC:
		endIsGame();
		break;
	case ENTER:
		//setRandItem(1);
	 //   snake.add_tail();
		//SetColor(RED,BLACK);
		gameInfo.key_ch = NULL;
		break;
	case UP:
		snake.setSnakePos(false, -ADD_Y);
		break;
	case DOWN:
		snake.setSnakePos(false, ADD_Y);
		break;
	case LEFT:
		snake.setSnakePos(true, -ADD_X);
		break;
	case RIGHT:
		snake.setSnakePos(true, ADD_X);
		break;
	default:
		return false;
	}
	return true;
}

static int g_item_count = 0;
void checkMap()
{
	// 맵 상태(벽 or 아이템)과의 충돌부분
	int sizeA = MAP_SIZE_WIDTH;
	int sizeB = MAP_SIZE_HEIGHT;
	for (int i = 0; i < sizeA; ++i)
	{
		for (int j = 0; j < sizeB; ++j)
		{
			if (snake.pos_head->X / 2 == i + 1 && snake.pos_head->Y == j + 1)
			{
				int* state = &snake.pos_map[i][j];
				if (*state == MapState::WALL)
				{
					restart_init();
				}
				else if (*state == MapState::ITEM)
				{
					snake.add_tail();
					*state = MapState::EMPTY;

					setRandItem(1);
					//snake.pos_map[10 + g_item_count][10] = MapState::ITEM;
					//int item_w = (10 + g_item_count) * 2 + 2;
					//int item_h = 10 + 1;
					//printMsg(item_w, item_h, "★");
					//++g_item_count;

					if (gameInfo.delay >= 100)
						gameInfo.delay -= snake.length;
					else if (gameInfo.delay > 50)
						gameInfo.delay--;

					snake.score += DEFAULT_SNAKE_SCORE_POINT;
				}
			}

		}
	}

	// 자기 자신과의 충돌부분
	for (int i = 1; i < snake.length; ++i)
	{
		if (snake.pos_head->X == snake.pos_snake[i].X
			&& snake.pos_head->Y == snake.pos_snake[i].Y)
		{
			restart_init();
		}
	}

}

void setRandItem(int num)
{
	bool reMake = false;
	for (int i = 0; i < num; ++i)
	{
		int w = rand() % (MAP_SIZE_WIDTH - 2) + 1;
		int h = rand() % (MAP_SIZE_HEIGHT - 2) + 1;

		for (int j = 0; j < snake.length; ++j)
		{
			if (snake.pos_snake[j].X == w * 2 + 2 && snake.pos_snake[j].Y == h + 1)
			{
				reMake = true;
				break;
			}
		}
		if (reMake)
		{
			reMake = false;
			continue;
		}
		snake.pos_map[w][h] = MapState::ITEM;
		int item_w = w * 2 + 2;
		int item_h = h + 1;
		printMsg(item_w, item_h, "★");
	}
}

void printStatus()
{
	printMsg(6, DEFAULT_TEXT_HEIGHT, snake.pos_head->X / 2);
	printMsg(6, DEFAULT_TEXT_HEIGHT + 1, snake.pos_head->Y);
	printMsg(58, DEFAULT_TEXT_HEIGHT, snake.pos_del->X / 2);
	printMsg(58, DEFAULT_TEXT_HEIGHT + 1, snake.pos_del->Y);
	printMsg(21, DEFAULT_TEXT_HEIGHT + 1, snake.length);
	printMsg(45, DEFAULT_TEXT_HEIGHT, snake.scoreHigh);
	printMsg(45, DEFAULT_TEXT_HEIGHT + 1, snake.score);

	for (size_t i = 0; i < snake.life; i++)
	{
		printMsg(21 + i, DEFAULT_TEXT_HEIGHT, "* ");
	}
}

void endMsg()
{
	setPos(30, 30);
	printMsg(0, 0, "Bye~\t");
}

void endIsGame()
{
	gameInfo.isGame = false;
}

void printMsg(int x, int y, char* msg)
{
	setPos(x, y);
	printf("%s", msg);
}

void printMsg(int x, int y, int num)
{
	setPos(x, y);
	printf("%03d", num);
}

void printMsg(int x, int y, long num)
{
	setPos(x, y);
	printf("%lu", num);
}