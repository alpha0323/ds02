#pragma once

#include <Windows.h>
#include <d3dx9.h>

#define SCREEN_WIDTH  (1280)              // スクリーン(クライアント領域)の幅
#define SCREEN_HEIGHT  (720)              // スクリーン(クライアント領域)の高さ
#define MATH_PAI	  (3.14)
#define MATH_PAI_0	  (0)
#define MATH_PAI_1_4  (3.14 * 1 / 4)
#define MATH_PAI_2_4  (3.14 * 1 / 2)
#define MATH_PAI_3_4  (3.14 * 3 / 4)
#define MATH_PAI_5_4  (3.14 * 5 / 4)
#define MATH_PAI_6_4  (3.14 * 3 / 2)
#define MATH_PAI_7_4  (3.14 * 7 / 4)
#define MATH_PAI_8_4  (3.14 * 2)

//ウィンドウハンドルのGetter
HWND GetHWND();
double frand();
D3DXVECTOR2 GetAnimTbl(int set, int muki, int anim);