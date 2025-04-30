#include "framework.h"
#include "thread"
#include "chrono"

enum class Anim {Bed, Cat, Mage};

void paintObj(int x, int y, int end_x, int end_y, HBITMAP bmp, HDC hdc, HDC memdc, int time);
void moveCoords(int& x, int& y, int moveX, int moveY, int startX, int startY);

void DrawBed(HDC hdc) {
    HDC memdc = CreateCompatibleDC(hdc);

    HBITMAP bmw = (HBITMAP)LoadImage(NULL, L"newbed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SelectObject(memdc, bmw);
    BitBlt(hdc, 0, 195, 743, 626, memdc, 0, 0, SRCCOPY);
}

void DrawCat(HDC hdc) {
    HDC memdc = CreateCompatibleDC(hdc);

    HBITMAP catstatbmw = (HBITMAP)LoadImage(NULL, L"catstat2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP catleftbmw = (HBITMAP)LoadImage(NULL, L"catleft2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP catrightbmw = (HBITMAP)LoadImage(NULL, L"catright2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP catleftleftbmw = (HBITMAP)LoadImage(NULL, L"catleftleft.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP catrightrightbmw = (HBITMAP)LoadImage(NULL, L"catrightright.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    int catW = 214;
    int catH = 214;
    int catStartX = 100;
    int catStartY = 60;

    int catDeltaTime = 500000000;

    while (true) {

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catstatbmw, hdc, memdc, catDeltaTime);

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catleftbmw, hdc, memdc, catDeltaTime);

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catleftleftbmw, hdc, memdc, catDeltaTime);

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catleftbmw, hdc, memdc, catDeltaTime);

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catstatbmw, hdc, memdc, catDeltaTime);

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catrightbmw, hdc, memdc, catDeltaTime);

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catrightrightbmw, hdc, memdc, catDeltaTime);

        paintObj(catStartX, catStartY, catStartX + catW, catStartY + catH, catrightbmw, hdc, memdc, catDeltaTime);
    }
}

void paintObj(int x, int y, int end_x, int end_y, HBITMAP bmp, HDC hdc, HDC memdc, int time) {
    SelectObject(memdc, bmp);
    BitBlt(hdc, x, y, end_x, end_y, memdc, 0, 0, SRCINVERT);
    std::this_thread::sleep_for(std::chrono::nanoseconds(time));
    BitBlt(hdc, x, y, end_x, end_y, memdc, 0, 0, SRCINVERT);
}


void DrawMage(HDC hdc) {
    HDC memdc = CreateCompatibleDC(hdc);

    HBITMAP mage1 = (HBITMAP)LoadImage(NULL, L"an1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP mage2 = (HBITMAP)LoadImage(NULL, L"an2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP mage3 = (HBITMAP)LoadImage(NULL, L"an3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP mage4 = (HBITMAP)LoadImage(NULL, L"an4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP mage5 = (HBITMAP)LoadImage(NULL, L"an5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HBITMAP mage6 = (HBITMAP)LoadImage(NULL, L"an6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    int startX = 500;
    int startY = 600;
    int moveX = -3;
    int moveY = 0;

    int x = startX;
    int y = startY;

    int mageX = 35;
    int mageY = 35;

    int mageDeltaTime = 50000000;

    while (true) {
        paintObj(x, y, x + mageX, y + mageY, mage1, hdc, memdc, mageDeltaTime);
        moveCoords(x, y, moveX, moveY, startX, startY);

        paintObj(x, y, x + mageX, y + mageY, mage2, hdc, memdc, mageDeltaTime);
        moveCoords(x, y, moveX, moveY, startX, startY);

        paintObj(x, y, x + mageX, y + mageY, mage3, hdc, memdc, mageDeltaTime);
        moveCoords(x, y, moveX, moveY, startX, startY);

        paintObj(x, y, x + mageX, y + mageY, mage4, hdc, memdc, mageDeltaTime);
        moveCoords(x, y, moveX, moveY, startX, startY);

        paintObj(x, y, x + mageX, y + mageY, mage5, hdc, memdc, mageDeltaTime);
        moveCoords(x, y, moveX, moveY, startX, startY);

        paintObj(x, y, x + mageX, y + mageY, mage6, hdc, memdc, mageDeltaTime);
        moveCoords(x, y, moveX, moveY, startX, startY);
    }
}

void moveCoords(int& x, int& y, int moveX, int moveY, int startX, int startY) {
    x += moveX;

    if (x < 0) {
        x = startX;
    }

    y += moveY;

    if (y < 0) {
        y = startY;
    }
}

void DrawCurrent(HDC hdc, Anim current) {
    switch (current) {
    case Anim::Bed: DrawBed(hdc); break;
    case Anim::Cat: DrawCat(hdc); break;
    case Anim::Mage: DrawMage(hdc); break;
    }
}