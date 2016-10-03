#include "game.h"
#include "dxinput.h"
#include "dxgraphics.h"

#define BALL_IMAGE_FILE L"ball.bmp"
#define BALL_WIDTH 25
#define BALL_HEIGHT 25

LPDIRECT3DSURFACE9	back;

LPD3DXSPRITE sprite_handler;

LPDIRECT3DTEXTURE9 ball_image;
SPRITE ball;

LPDIRECT3DTEXTURE9 paddle_image;
SPRITE paddle;

#define APP_CLASS L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Sample"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FRAME_RATE 30

//CSOUND_SYSTEM **sound_bounce;
//CSound *sound_hit;

long start = GetTickCount();
HRESULT result;

int Game_Init(HWND hwnd)
{
	srand(time(NULL));

	if (!Init_Mouse(hwnd))
	{
		MessageBox(hwnd, "Error intializing the mouse.", "Error", MB_OK);
		return 0;
	}

	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error intializing the keyboard.", "Error", MB_OK);
		return 0;
	}

	result = D3DXCreateSprite(d3ddv, &sprite_handler);

	if (result != D3D_OK)
		return 0;

	//load the background image
	//int back = D3DXLoadSurfaceFromFile(
	//	surface, 		// surface
	//	NULL,			// destination palette	
	//	NULL,			// destination rectangle 
	//	BALL_IMAGE_FILE,
	//	NULL,			// source rectangle
	//	D3DX_DEFAULT, 	// filter image
	//	D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
	//	NULL);
	back = LoadSurface(BALL_IMAGE_FILE, NULL);
	if (back == NULL)
		return 0;

	//load the balls sprite
	ball_image = LoadTexture(BALL_IMAGE_FILE, D3DCOLOR_XRGB(255, 0, 255));
	if (ball_image == NULL)
		return 0;

	//set ball's properties
	ball.x = 400;
	ball.y = 200;
	ball.width = 12;
	ball.height = 12;
	ball.moveX = 8;
	ball.moveY = -8;

	//load the paddle sprite
	paddle_image = LoadTexture(BALL_IMAGE_FILE, D3DCOLOR_XRGB(255, 0, 255));

	if (paddle_image == NULL)
		return 0;

	paddle.x = 300;
	paddle.y = SCREEN_HEIGHT - 50;
	paddle.width = 90;
	paddle.height = 26;


	/*LOAD SOUND AND WAVE*/

	return 1;
}

int Collision(SPRITE spr1, SPRITE spr2)
{
	RECT rect1;
	rect1.left = spr1.x + 1;
	rect1.top = spr1.y + 1;
	rect1.right = spr1.x + spr1.width - 1;
	rect1.bottom = spr1.y + spr1.height - 1;

	RECT rect2;
	rect2.left = spr2.x + 1;
	rect2.top = spr2.y + 1;
	rect2.right = spr2.x + spr2.width - 1;
	rect2.bottom = spr2.y + spr2.height - 1;

	RECT dest;
	return IntersectRect(&dest, &rect1, &rect2);
}

void Game_Run(HWND hwnd)
{
	D3DXVECTOR3 position(0, 0, 0);

	if (d3ddv == NULL)
		return;

	Poll_Mouse();
	Poll_Keyboard();

	if (GetTickCount() - start >= 30)
	{
		start = GetTickCount();

		ball.x += ball.moveX;
		ball.y += ball.moveY;

		if (ball.x > SCREEN_WIDTH - ball.width)
		{
			ball.x -= ball.width;
			ball.moveX *= -1;
			//PlaySound(sound_bounce);
		}
		else if (ball.x < 0)
		{
			ball.x += ball.width;
			ball.moveX *= -1;
		}

		if (ball.y > SCREEN_HEIGHT - ball.height)
		{
			ball.y -= ball.height;
			ball.moveY *= -1;
		}
		else if (ball.y < 0)
		{
			ball.y += ball.height;
			ball.moveY *= -1;
		}

		paddle.x += Mouse_X();
		if (paddle.x > SCREEN_WIDTH - paddle.width)
			paddle.x = SCREEN_WIDTH - paddle.width;
		else if (paddle.x < 0)
			paddle.x = 0;

		if (Key_Down(DIK_LEFT))
			paddle.x -= 5;

		if (Key_Down(DIK_RIGHT))
			paddle.x += 5;

		if (Collision(paddle, ball))
		{
			ball.y -= ball.moveY;
			ball.moveY *= -1;
		}
	}

	if (d3ddv->BeginScene())
	{
		d3ddv->StretchRect(back, NULL, back_buffer, NULL, D3DTEXF_NONE);

		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

		position.x = (float)ball.x;
		position.y = (float)ball.y;
		sprite_handler->Draw(ball_image, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));

		position.x = (float)paddle.x;
		position.y = (float)paddle.y;
		sprite_handler->Draw(paddle_image, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));

		d3ddv->Present(NULL, NULL, NULL, NULL);

		if (Mouse_Button(0))
			PostMessage(hwnd, WM_DESTROY, 0, 0);

		if (Key_Down(DIK_ESCAPE))
			PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
}

void Game_End(HWND hwnd)
{
	if (ball_image != NULL)
		ball_image->Release();

	if (paddle_image != NULL)
		paddle_image->Release();

	if (back != NULL)
		back->Release();

	if (sprite_handler != NULL)
		sprite_handler->Release();
}
