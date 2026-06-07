#include <stdio.h>

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


int main()
{
    initializeCanvas();

    drawBorder();

    drawRectangle(5,10,8,20);

    displayCanvas();

    return 0;
}