#pragma once
#include "point.h"
#include <mutex>
#include <Windows.h>
#include <iostream>

using namespace std;

class tool
{
public:
	static mutex mtx;
	static void ShowConsoleCursor(bool);
	static void GotoXY(int x, int y);
	static void Draw(char*, int, point[], point&);
};

