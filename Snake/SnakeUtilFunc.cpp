#include "stdafx.h"
#include "SnakeFunc's.h"

extern GameInfo gameInfo;

HANDLE g_hOut = gameInfo.hOut;

int SetScreenBuf(int width, int height)
{
    COORD coords = {static_cast<short>(width), static_cast<short>(height)};

    return SetConsoleScreenBufferSize( g_hOut, coords);
}

int SetWindowSize(int width, int height)
{
    if ( width <= 0 || width > GetBufferSizeX() ||
        height <= 0 || height > GetBufferSizeY() )
    {
        return 0;
    }

    SMALL_RECT rect;

    rect.Left = 0;

    rect.Right = width - 1;

    rect.Top = 0;

    rect.Bottom = height - 1;

    return SetConsoleWindowInfo(g_hOut, TRUE, &rect);
}

int GetBufferSizeX()
{
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;

    GetConsoleScreenBufferInfo(g_hOut, &screenInfo);

    return screenInfo.dwSize.X;
}

int GetBufferSizeY()
{
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;

    GetConsoleScreenBufferInfo(g_hOut, &screenInfo);

    return screenInfo.dwSize.Y;
}

void SetCursor(bool bVisible)
{
    CONSOLE_CURSOR_INFO ConsoleCursor;

    ConsoleCursor.bVisible = bVisible; // true 보임, false 안보임

    ConsoleCursor.dwSize = 1; // 커서사이즈

    SetConsoleCursorInfo(g_hOut , &ConsoleCursor); // 설정

}

void SetColor(int color , int bgcolor )
{
    color   &= 0xf;

    bgcolor &= 0xf ;

    SetConsoleTextAttribute(g_hOut, (bgcolor << 4)  | color  );
}

void setPos(int x, int y)
{
    COORD pos = {x-1,y-1};
    SetConsoleCursorPosition(g_hOut,pos);
}

COORD getPos()
{
    CONSOLE_SCREEN_BUFFER_INFO curInfo;
    GetConsoleScreenBufferInfo(g_hOut,&curInfo);
    return curInfo.dwCursorPosition;
}