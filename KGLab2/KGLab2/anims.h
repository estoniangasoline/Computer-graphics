#pragma once

#include "framework.h"

enum class Anim { Bed, Cat, Mage };

void paintObj(int x, int y, int end_x, int end_y, HBITMAP bmp, HDC hdc, HDC memdc, int time);
void moveCoords(int& x, int& y, int moveX, int moveY, int startX, int startY);
void DrawBed(HDC hdc);
void DrawCat(HDC hdc);
void DrawMage(HDC hdc);
void DrawCurrent(HDC hdc, Anim current);
