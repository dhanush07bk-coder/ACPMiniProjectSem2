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
            float dx = x - centerX;
            float dy = (y - centerY) * 2;

            float distanceSquared =
            dx * dx + dy * dy;

            float radiusSquared =
                radius * radius;

            if(abs(distanceSquared - radiusSquared)
                <= radius/2)
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

    int x2;
    int y2;

    int x3;
    int y3;

    int radius;

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
    if(shapeCount >= MAX_SHAPES)
    {
    printf("Storage Full!\n");
    return;
    }

    shapes[shapeCount].id = shapeCount + 1;
    shapes[shapeCount].type = 1;

    shapes[shapeCount].x = col;
    shapes[shapeCount].y = row;

    shapes[shapeCount].width = width;
    shapes[shapeCount].height = height;

    shapes[shapeCount].active = 1;

    shapeCount++;
}

void addCircle(int centerX,int centerY,int radius)
{
    if(shapeCount >= MAX_SHAPES)
        return;

    shapes[shapeCount].id = shapeCount + 1;

    shapes[shapeCount].type = 2;

    shapes[shapeCount].x = centerX;
    shapes[shapeCount].y = centerY;

    shapes[shapeCount].radius = radius;

    shapes[shapeCount].active = 1;

    shapeCount++;

    printf("Circle Added!\n");
}

void addTriangle(
    int x1,int y1,
    int x2,int y2,
    int x3,int y3)
{
    if(shapeCount >= MAX_SHAPES)
        return;

    shapes[shapeCount].id = shapeCount + 1;

    shapes[shapeCount].type = 3;

    shapes[shapeCount].x = x1;
    shapes[shapeCount].y = y1;

    shapes[shapeCount].x2 = x2;
    shapes[shapeCount].y2 = y2;

    shapes[shapeCount].x3 = x3;
    shapes[shapeCount].y3 = y3;

    shapes[shapeCount].active = 1;

    shapeCount++;

    printf("Triangle Added!\n");
}

void addLine(
    int x1,int y1,
    int x2,int y2)
{
    if(shapeCount >= MAX_SHAPES)
        return;

    shapes[shapeCount].id = shapeCount + 1;

    shapes[shapeCount].type = 4;

    shapes[shapeCount].x = x1;
    shapes[shapeCount].y = y1;

    shapes[shapeCount].x2 = x2;
    shapes[shapeCount].y2 = y2;

    shapes[shapeCount].active = 1;

    shapeCount++;

    printf("Line Added!\n");
}

void redrawAll()
{
    initializeCanvas();

    drawBorder();

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].active == 1)
        {
            /* Rectangle */

            if(shapes[i].type == 1)
            {
                drawRectangle(
                    shapes[i].y,
                    shapes[i].x,
                    shapes[i].height,
                    shapes[i].width
                );
            }

            /* Circle */

            if(shapes[i].type == 2)
            {
                drawCircle(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].radius
                );
            }

            /* Triangle */

            if(shapes[i].type == 3)
            {
                drawTriangle(
                    shapes[i].x,
                    shapes[i].y,

                    shapes[i].x2,
                    shapes[i].y2,

                    shapes[i].x3,
                    shapes[i].y3
                );
            }
            /*line*/
            if(shapes[i].type == 4)
            {
                drawLine(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].x2,
                    shapes[i].y2
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
            printf("Shape Deleted Successfully!\n");
            return;
        }
    }
    printf("Shape ID Not Found!\n");
}

void displayShapes()
{
    printf("\n===== STORED SHAPES =====\n");

    for(int i=0;i<shapeCount;i++)
    {
        printf("\nID=%d ", shapes[i].id);

        if(shapes[i].type == 1)
            printf("Rectangle ");

        else if(shapes[i].type == 2)
            printf("Circle ");

        else if(shapes[i].type == 3)
            printf("Triangle ");
        
        else if(shapes[i].type == 4)
            printf("Line ");

        printf("Active=%d",
               shapes[i].active);
    }
    int activeCount = 0;

for(int i=0;i<shapeCount;i++)
{
    if(shapes[i].active == 1)
        activeCount++;
}

printf("\nActive Shapes = %d\n", activeCount);
    printf("\n");
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
            printf("Rectangle Modified Successfully!\n");
            return;
        }
    }
    printf("Shape ID Not Found!\n");

}



int main()
{
    int choice;

    while(1)
    {
        printf("\n=================================");
        printf("\n      2D GRAPHICS EDITOR");
        printf("\n=================================\n");

        printf("1. Add Rectangle\n");
        printf("2. Add Circle\n");
        printf("3. Add Triangle\n");
        printf("4. Add Line\n");
        printf("5. Delete Shape\n");
        printf("6. Modify Rectangle\n");
        printf("7. Display Shape List\n");
        printf("8. Show Canvas\n");
        printf("9. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d",&choice);
    

       switch(choice){
            case 1:
                {
                        int row,col,height,width;

                        printf("Enter Row Col Height Width: ");

                        scanf("%d%d%d%d",
                        &row,
                        &col,
                        &height,
                        &width);

                    addRectangle(
                        row,
                        col,
                        height,
                        width);

                    break;
                }

            case 2:
                    {
                    int x,y,r;

                    printf("Enter CenterX CenterY Radius: ");

                    scanf("%d%d%d",
                     &x,
                     &y,
                     &r);

                addCircle(x,y,r);

                 break;
                }

    case 3:
    {
        int x1,y1,x2,y2,x3,y3;

        printf("Enter x1 y1 x2 y2 x3 y3 : ");

        scanf("%d%d%d%d%d%d",
              &x1,&y1,
              &x2,&y2,
              &x3,&y3);

        addTriangle(
            x1,y1,
            x2,y2,
            x3,y3);

        break;
    }

    case 4:
{
    int x1,y1,x2,y2;

    printf("Enter x1 y1 x2 y2 : ");

    scanf("%d%d%d%d",
          &x1,&y1,
          &x2,&y2);

    addLine(
        x1,y1,
        x2,y2);

    break;
}

    case 5:
    {
        int id;

        printf("Enter Shape ID to Delete: ");

        scanf("%d",&id);

        deleteShape(id);

        break;
    }

    case 6:
    {
        int id,width,height;

        printf("Enter ID Width Height: ");

        scanf("%d%d%d",
              &id,
              &width,
              &height);

        modifyRectangle(
            id,
            width,
            height);

        break;
    }

    case 7 :
    {
        displayShapes();

        break;
    }

    case 8:
    {
        redrawAll();

        displayCanvas();

        break;
    }

    case 9 :
    {
        printf("\nThank You For Using 2D Graphics Editor\n");
        printf("Program Terminated Successfully.\n");

        return 0;
    }

    default:
    {
        printf("Invalid Choice!\n");
    }

}
    }


    return 0;
}