#include <iostream>
#include <conio.h> //for input sign WASD
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

bool gameover;
const int height = 26, width = 56;
int fruitx, fruity, headx, heady, score;
int tailx[150], taily[150], taillen;

enum direction
{
    stop = 0,
    Left,
    Right,
    up,
    down
};
direction dir;

void setup();
void boundary();
void input();
void logic();

int main()
{
    setup();
    while (!gameover)
    {
        boundary();
        input();
        logic();
        Sleep(100);
    }
    return 0;
}

void setup()
{
    gameover = false;
    dir = stop;
    headx = width / 2; // center the head at start
    heady = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

void boundary()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0}); // remove flicker
    
    int i, j;
    for (i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == heady && j == headx)
                cout << "C";
            else if (i == fruity && j == fruitx)
                cout << "*";
            else
            {
                bool print = false;
                for (int k = 0; k < taillen; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "+";
                        print = true;   
                    }
                }
                if (!print)   //since adding extra tails increases the amount of spaces, we remove the spaces using this part
                {
                    cout << " ";
                }
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl
         << "SCORE=" << score;
}

void input()
{
    if (kbhit())
    { // kbhit returns 1 when program senses a keyboard hit
        switch (getch())
        {
        case 'a':
            dir = Left;
            break;
        case 'w':
            dir = up;
            break;
        case 's':
            dir = down;
            break;
        case 'd':
            dir = Right;
            break;
        case 'l':
            gameover = true;
            break;
        case KEY_UP:
            dir = up;
            break;
        case KEY_DOWN:
            dir = down;
            break;
        case KEY_RIGHT:
            dir = Right;
            break;
        case KEY_LEFT:
            dir = Left;
            break;
        default:
            break;
        }
    }
}

void logic()
{
    for (int i = taillen; i > 0; i--)
    {
        tailx[i] = tailx[i - 1];
        taily[i] = taily[i - 1];
    }
    tailx[0] = headx;
    taily[0] = heady;
    switch (dir)
    { // moving the head
    case up:
        heady--;
        Sleep(60.5);
        break;
    case down:
        heady++;
        Sleep(60.5);
        break;
    case Left:
        headx--;
        Sleep(10.5);
        break;
    case Right:
        headx++;
        Sleep(10.5);
        break;
    default:
        break;
    }
    // if (headx > width || headx < 0 || heady > height || heady < 0) // setting boundary limit
    //     gameover = true;
    if (headx>=width)   //reach opposite ends from the boundary
        headx=0;
    else if (headx<0)
        headx=width-1;
    if (heady>=height)
        heady=0;
    else if (heady<0)
        heady=height-1;
    for (int i=0; i<taillen; i++){  //bite your body and die
        if (tailx[i]==headx && taily[i]==heady)
            gameover=true;
    }
    if (headx == fruitx && heady == fruity)
    {
        score++;
        fruitx = rand() % width; // new place for fruit
        fruity = rand() % height;
        taillen++; // increase tail length after eating fruit
    }
}