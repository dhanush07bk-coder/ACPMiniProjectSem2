#include <stdio.h>
#include<stdlib.h>

#define ROWS 25
#define COLS 80

char canvas[ROWS][COLS];

void initializeCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}
void plotPixel(int row, int col)
{
    if(row >= 0 && row < ROWS &&
       col >= 0 && col < COLS)
    {
        canvas[row][col] = '*';
    }
}

void drawBorder()
{
    for(int j=0; j<COLS; j++)
    {
        plotPixel(0, j);
        plotPixel(ROWS - 1, j);
    }

    for(int i=0; i<ROWS; i++)
    {
        plotPixel(i, 0);
        plotPixel(i, COLS - 1);
    }
}
void drawRectangle(int row, int col, int height, int width)
{
    for(int j = col; j < col + width; j++)
    {
        plotPixel(row, j);
        plotPixel(row + height - 1, j);
    }

    for(int i = row; i < row + height; i++)
    {
        plotPixel(i, col);
        plotPixel(i, col + width - 1);
    }
}
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;

    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for(int i = 0; i <= steps; i++)
    {
        plotPixel((int)(y + 0.5), (int)(x + 0.5));

        x += xInc;
        y += yInc;
    }
}
void drawTriangle(
    int x1,int y1,
    int x2,int y2,
    int x3,int y3)
{
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}


int main()
{
    initializeCanvas();

    drawBorder();

    drawRectangle(5,10,8,20);

    drawLine(5,20,50,15);

    drawTriangle(20,5,10,15,30,15);

    displayCanvas();

    return 0;
}