#pragma once

#include <dinput.h>

int		Init_DirectInput(HWND);
int		Init_Keyboard(HWND);
void	Poll_Keyboard();
void	Poll_Mouse();
int		Key_Down(int);
void	Kill_Keyboard();
int		Init_Mouse(HWND);
int		Mouse_Button(int);
int		Mouse_X();
int		Mouse_Y();
void	Kill_Mouse();

extern LPDIRECTINPUT8		dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8	dikeyboard;
extern DIMOUSESTATE			mouse_state;