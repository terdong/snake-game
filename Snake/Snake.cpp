// Snake.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Snake.h"

int _tmain(int argc, _TCHAR* argv[])
{
    srand((unsigned)time(NULL));

    init();

    loop();

    endMsg();

	return 0;
}

