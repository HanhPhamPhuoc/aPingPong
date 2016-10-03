#include <d3dx9.h>
#include "dxgraphics.h"

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddv = NULL;
LPDIRECT3DSURFACE9 back_buffer = NULL;

int Init_Direct3D(HWND hwnd, int width, int height, int fullscreen)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hwnd, "Error intializing Direct3D", "Error", MB_OK);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3ddp;
	ZeroMemory(&d3ddp, sizeof(d3ddp));

	d3ddp.Windowed = (!fullscreen);
	d3ddp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3ddp.BackBufferFormat = D3DFMT_X8B8G8R8;
	d3ddp.BackBufferCount = 1;
	d3ddp.BackBufferWidth = width;
	d3ddp.BackBufferHeight = height;
	d3ddp.hDeviceWindow = hwnd;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3ddp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		MessageBox(hwnd, "Error intializing Direct3D device.", "Error", MB_OK);
		return 0;
	}

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer);

	return 1;
}

LPDIRECT3DTEXTURE9	LoadTexture(char* filename, D3DCOLOR trancolor)
{
	//con tro texture
	LPDIRECT3DTEXTURE9 texture = NULL;

	//truct de doc thong tin tep bitmap
	D3DXIMAGE_INFO info;

	//tra ve gia tri window thong thuong
	HRESULT result;

	//lay ra thong tin width va height cua tep bitmap
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return NULL;

	//tao texture moi bang cach tai len tep bitmap
	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		filename,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		trancolor,
		&info,
		NULL,
		&texture);

	//dam bao texture duoc tai len thanh cong
	if (result != D3D_OK)
		return NULL;

	return texture;
}

LPDIRECT3DSURFACE9 LoadSurface(char* filename, D3DCOLOR trancolor)
{
	LPDIRECT3DSURFACE9 image = NULL;

	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return NULL;

	result = d3ddv->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8B8G8R8,
		D3DPOOL_DEFAULT,
		&image,
		NULL);

	if (result != D3D_OK)
		return NULL;

	result = D3DXLoadSurfaceFromFile(
		image,
		NULL,
		NULL,
		filename,
		NULL,
		D3DX_DEFAULT,
		trancolor,
		NULL);

	if (result != D3D_OK)
		return NULL;
	return image;

}