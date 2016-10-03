#ifndef _GAME_H
#define _GAME_H 1

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <dsound.h>
#include <dinput.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "dxgraphics.h"
//#include <dxaudio.h>
#include "dxinput.h"

#include <dsound.h>
#include <dinput.h>

#define APPTITLE "Paddle_Game"

#define FULLSCREEN 0
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480	

typedef struct{
	int x, y;
	int width, height;
	int moveX, moveY;
	int curframe, lastframe;
	int animdelay, animcount;
	int scaleX, scaleY;
	int rotation, rotaterate;
}SPRITE;

int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);
int Collision(SPRITE, SPRITE);

#endif