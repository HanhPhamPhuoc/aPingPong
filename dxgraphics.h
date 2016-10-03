#pragma once
//#include <d3d9.h>
//#include <d3dx9.h>

//#include <windows.h>
//#include <time.h>
//#include <stdio.h>
//#include <stdlib.h>

int Init_Direct3D(HWND, int, int, int);
LPDIRECT3DSURFACE9 LoadSurface(LPCWSTR, D3DCOLOR);
LPDIRECT3DTEXTURE9	LoadTexture(LPCWSTR, D3DCOLOR);

extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddv;
extern LPDIRECT3DSURFACE9 back_buffer;