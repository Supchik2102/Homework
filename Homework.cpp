#include "TXLib.h"

//----------------------------------------------------------------------------

void drawMan (int x, int y, int hx, int hy, double scale, COLORREF color);

void moveMen (int x00, int y00, double vx0, double vy0,
              double scale00, double scale10,
              int time0, COLORREF color0,
              int x01, int y01, double vx1, double vy1,
              double scale01, double scale11,
              int time1, int delay,
              COLORREF color1,
              int x2, int y2, double vx2, double vy2,
              int time2, COLORREF color2,
              bool wobble, COLORREF bkcolor);

void Clear (COLORREF color);

void drawBackground (COLORREF color);

void drawHouse (int x, int y, COLORREF color, COLORREF bkcolor);

void hi (int delay);

//----------------------------------------------------------------------------

int main()
{

    txCreateWindow (800, 600);

    moveMen (400, 338, 1, 0, 1, 1, 375, TX_GREEN, 1000, 338, 0, 0, 1, 1, 370, 1, TX_LIGHTCYAN, 1000, 300, 0, 0, 370, TX_WHITE, true, TX_BLACK);

    txSleep (500);

    moveMen (775, 338, -1, 0, 1, 1, 200, TX_GREEN, 850, 338, -1, 0, 1, 1, 200, 1, TX_LIGHTCYAN, 835, 400, -1, 0, 200, TX_WHITE, false, TX_BLACK);

    txSleep (500);

    moveMen (575, 338, 0, 0, 1, 1, 100, TX_GREEN, 650, 338, -1, 0, 1, 1, 35, 1, TX_LIGHTCYAN, 635, 400, 0, 0, 100, TX_WHITE, false, TX_BLACK);

    hi (10);

    moveMen (575, 338, -1, 0, 1, 1, 650, TX_GREEN, 615, 338, -1, 0, 1, 1, 650, 1, TX_LIGHTCYAN, 635, 400, 0, 0, 100, TX_WHITE, true, TX_BLACK);

    return 0;

}

//----------------------------------------------------------------------------

void drawMan (int x, int y, int lhx, int lhy, int rhx, int rhy, double scale, COLORREF color)
{

    txSetColor (color, scale);
    txSetFillColor(TX_BLACK);

    txLine (x, y, x, y + scale * 40);

    txLine (x, y + scale * 5, x + scale * 7 + rhy, y + scale * 25 + rhx);
    txLine (x, y + scale * 5, x - scale * 7 + lhy, y + scale * 25 + lhx);

    txLine (x, y + scale * 40, x + scale * 10, y + scale * 40 + scale * 20);
    txLine (x, y + scale * 40, x - scale * 10, y + scale * 40 + scale * 20);

    txCircle (x, y - scale * 5, scale * 10);

}

//----------------------------------------------------------------------------

void moveMen (int x00, int y00, double vx0, double vy0,
              double scale00, double scale10,
              int time0, COLORREF color0,
              int x01, int y01, double vx1, double vy1,
              double scale01, double scale11,
              int time1, int delay,
              COLORREF color1,
              int x02, int y02, double vx2, double vy2,
              int time2, COLORREF color2,
              bool wobble, COLORREF bkcolor)

{

    drawMan (x00, y00, 0, 0, 0, 0, scale00, color0);
    drawMan (x01, y01, 0, 0, 0, 0, scale01, color1);

    double vScale0 = (scale10 - scale00) / time0;
    double vScale1 = (scale11 - scale01) / time1;

    int x10 = x00;
    int y10 = y00;

    int x11 = x01;
    int y11 = y01;

    int x12 = x02;
    int y12 = x02;

    double scale0 = scale00;
    double scale1 = scale01;

    int time = time0;

    if (time < time1)

    {

        time = time1;

    }

    if (time < time2)

    {

        time = time2;

    }


    for (int t = 0; t <= time; t++)

    {

        drawMan (x10, y10, 0, 0, 0, 0, scale0, color0);
        drawMan (x11, y11, 0, 0, 0, 0, scale1, color1);
        drawHouse (x12, y12, color2, bkcolor);

        txSleep (delay);

        Clear (bkcolor);
        drawBackground (TX_WHITE);

        if (t <= time0)

        {

            x10 = x00 + vx0 * t;
            y10 = y00 + vy0 * t;

            if (wobble)

            {

                y10 = y10 + t % 10 - 5;

            }

            scale0 = scale00 + vScale0 * t;
            drawMan (x10, y10, 0, 0, 0, 0, scale0, color0);

        }

        if (t <= time1)

        {

            x11 = x01 + vx1 * t;
            y11 = y01 + vy1 * t;

            if (wobble)

            {

                y11 = y11 - t % 10 + 5;

            }

            scale1 = scale01 + vScale1 * t;
            drawMan (x11, y11, 0, 0, 0, 0, scale1, color1);

        }

        if (t <= time2)

        {

            x12 = x02 + vx2 * t;
            y12 = y02 + vy2 * t;

            drawHouse (x12, y12, color2, bkcolor);

        }


    }

    drawMan (x10, y10, 0, 0, 0, 0, scale10, color0);
    drawMan (x11, y11, 0, 0, 0, 0, scale11, color1);
    drawHouse (x12, y12, color2, bkcolor);

}

//----------------------------------------------------------------------------

void Clear (COLORREF color)

{

    txSetColor (color);
    txSetFillColor (color);

    txRectangle (1, 1, 800, 600);

}

//----------------------------------------------------------------------------

void drawBackground (COLORREF color)

{

    txSetColor (color, 3);

    txLine (1, 400, 800, 400);

}

//----------------------------------------------------------------------------

void drawHouse (int x, int y, COLORREF color, COLORREF bkcolor)

{

    txSetFillColor (bkcolor);
    txSetColor (bkcolor);

    txRectangle (x, y - 110, x + 100, y);

    txSetColor (color, 3);

    txLine (x, y, x, y - 75);
    txLine (x, y, x + 100, y);
    txLine (x + 100, y - 75, x + 100, y);
    txLine (x, y - 75, x + 50, y - 110);
    txLine (x + 100, y - 75, x + 50, y - 110);

}

//----------------------------------------------------------------------------

void hi (int delay)

{

    int hx = 0;
    int hy = 0;

    for (int i = 0; i <= 20; i++)

    {

        Clear (TX_BLACK);

        drawBackground (TX_WHITE);
        drawMan (575, 338, 0, 0, -(i * 1.3), (i * 0.7), 1, TX_GREEN);
        drawMan (615, 338, -(i * 1.3), -(i * 0.7), 0, 0, 1, TX_LIGHTCYAN);
        drawHouse (635, 400, TX_WHITE, TX_BLACK);

        txSleep (delay);

    }

    txSleep (300);

    for (int i = 20; i >= 0; i--)

    {

        Clear (TX_BLACK);

        drawBackground (TX_WHITE);
        drawMan (575, 338, 0, 0, -(i * 1.3), (i * 0.7), 1, TX_GREEN);
        drawMan (615, 338, -(i * 1.3), -(i * 0.7), 0, 0, 1, TX_LIGHTCYAN);
        drawHouse (635, 400, TX_WHITE, TX_BLACK);

        txSleep (delay);

    }


}

