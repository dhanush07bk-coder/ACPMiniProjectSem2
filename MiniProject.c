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

void drawCircle(int centerX, int centerY, int radius)
{
    for(int y = centerY - radius;
        y <= centerY + radius;
        y++)
    {
        for(int x = centerX - radius;
            x <= centerX + radius;
            x++)
        {
            int dx = x - centerX;
            int dy = y - centerY;

            int distanceSquared =
                dx * dx + dy * dy;

            int radiusSquared =
                radius * radius;

            if(abs(distanceSquared - radiusSquared)
                <= radius)
            {
                plotPixel(y, x);
            }
        }
    }
}

#define MAX_SHAPES 100

typedef struct
{
    int id;
    int type;

    int x;
    int y;

    int width;
    int height;

    int active;

} Shape;
Shape shapes[MAX_SHAPES];
int shapeCount = 0;

void addRectangle(
    int row,
    int col,
    int height,
    int width)
{
    shapes[shapeCount].id = shapeCount + 1;
    shapes[shapeCount].type = 1;

    shapes[shapeCount].x = col;
    shapes[shapeCount].y = row;

    shapes[shapeCount].width = width;
    shapes[shapeCount].height = height;

    shapes[shapeCount].active = 1;

    shapeCount++;
}

void redrawAll()
{
    initializeCanvas();

    drawBorder();

    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].active == 1)
        {
            if(shapes[i].type == 1)
            {
                drawRectangle(
                    shapes[i].y,
                    shapes[i].x,
                    shapes[i].height,
                    shapes[i].width
                );
            }
        }
    }
}

void deleteShape(int id)
{
    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id == id)
        {
            shapes[i].active = 0;
            return;
        }
    }
}

void displayShapes()
{
    printf("\nStored Shapes\n");

    for(int i=0;i<shapeCount;i++)
    {
        printf(
            "\nID=%d Type=%d Active=%d",
            shapes[i].id,
            shapes[i].type,
            shapes[i].active
        );
    }
} 

void modifyRectangle(
    int id,
    int newWidth,
    int newHeight)
{
    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id == id)
        {
            shapes[i].width = newWidth;
            shapes[i].height = newHeight;
            return;
        }
    }
}




int main()
{
    initializeCanvas();

    drawBorder();

  addRectangle(5,10,8,20);

  addRectangle(2,40,6,15);

  addRectangle(15,30,5,25); 

  deleteShape(2);

  modifyRectangle(1,30,12);

  redrawAll();

  displayCanvas();
    
  return 0;
}