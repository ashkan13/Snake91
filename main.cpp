// In the Name of Allah
// AD13

#include <ctime>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

/// Options
//-----------------------------------------------------
const int X_SIZE = 65;                  // 20 < X_SIZE < 80
const int Y_SIZE = 24;                  // 10 < Y_SIZE < 25
const char WALL = (char)178;            // 219
const char HEAD_DIR[] = { 16, 31, 17, 30 }; // right, down, left, up
const char BODY = '#';
const char FOOD = '*';
const int FINAL_LEVEL = 29;
/*****************************************************/

int snakeLen;
enum class DirEn
{
    RIGHT, DOWN, LEFT, UP
} direction;
COORD snakePlace[100];

static HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void play();

void gotoxy(COORD cursorLoc)
{
    std::cout.flush();
    SetConsoleCursorPosition(outHandle, cursorLoc);
}
void gotoxy(int x, int y)
{
    COORD cursorLoc = { x, y };
    gotoxy(cursorLoc);
}

char readxy(int x, int y)
{
    char buf[2];
    DWORD num_read;
    COORD c = { x, y };
    ReadConsoleOutputCharacter(outHandle, (LPTSTR)buf, 1, c, (LPDWORD)&num_read);
    return buf[0];
}

/// M A I N
//-----------------------------------------------------
void main()
{
    system("title Snake91 --- ashkan_d13");
    system("color 3f");

    for (int i = 0; i < X_SIZE; i++)
    {
        gotoxy(i, 0);
        cout << WALL;
        gotoxy(i, Y_SIZE - 1);
        cout << WALL;
    }
    for (int i = 1; i < Y_SIZE; i++)
    {
        gotoxy(0, i);
        cout << WALL;
        gotoxy(X_SIZE - 1, i);
        cout << WALL;
    }

    gotoxy(0, 0);

    /// Hide cursor
    CONSOLE_CURSOR_INFO Info;
    Info.dwSize = 1;
    SetConsoleCursorInfo(outHandle, &Info);

    /// Set up the required window size
    SMALL_RECT windowSize = { 0, 0, X_SIZE-1, Y_SIZE-1 };
    SetConsoleWindowInfo(outHandle, TRUE, &windowSize);

    /// Change the internal buffer size
    COORD bufferSize = { X_SIZE, Y_SIZE };
    SetConsoleScreenBufferSize(outHandle, bufferSize);

    SetConsoleTextAttribute(outHandle, 0x3a);

    /// initialize
    srand((unsigned int)time(0));
    direction = DirEn(rand() % 3 + 1);
    // {0 -> right} , 1->down , 2 -> left , 3 -> up
    snakePlace[0].X = rand() % (X_SIZE-15) + 4;
    snakePlace[0].Y = rand() % (Y_SIZE-7) + 3;

    snakePlace[1].X = snakePlace[0].X;
    snakePlace[1].Y = snakePlace[0].Y;

    if (direction == DirEn::DOWN)
    {
        snakePlace[1].Y--;
    }
    else if (direction == DirEn::LEFT)
    {
        snakePlace[1].X++;
    }
    else {
        snakePlace[1].Y++;
    }

    snakeLen = 4;
    for (int i = 2; i < snakeLen; i++)
    {
        snakePlace[i].X = snakePlace[i-1].X + 1;
        snakePlace[i].Y = snakePlace[i-1].Y;
    }

    play();
}

/*****************************************************/

void writeLevel(int l)
{
    SetConsoleTextAttribute(outHandle, 0x3b);
    gotoxy(X_SIZE / 2 - 5, 0);
    cout << " Level ";
    if (l < 10)
    {
        cout << ' ';
    }
    cout << l << ' ';
    SetConsoleTextAttribute(outHandle, 0x3a);
}

void putFood()
{
    SetConsoleTextAttribute(outHandle, 0x3e);
    int x, y;
    do {
        x = rand() % (X_SIZE - 2) + 1;
        y = rand() % (Y_SIZE - 2) + 1;
    } while (readxy(x, y) != ' ');
    gotoxy(x, y);
    cout << FOOD;
    SetConsoleTextAttribute(outHandle, 0x3a);
}

void move(char ch = ' ')
{
    gotoxy(snakePlace[0]);
    cout << BODY;
    if (ch == ' ')
    {
        gotoxy(snakePlace[snakeLen-1]);
    }
    else {
        gotoxy(snakePlace[snakeLen-2]);
    }
    cout << ch;
    for (int i = snakeLen-1; i > 0; i--)
    {
        snakePlace[i] = snakePlace[i-1];
    }

    switch (direction)
    {
    case DirEn::RIGHT:
        snakePlace[0].X++;
        break;

    case DirEn::DOWN:
        snakePlace[0].Y++;
        break;

    case DirEn::LEFT:
        snakePlace[0].X--;
        break;

    case DirEn::UP:
        snakePlace[0].Y--;
    }
    gotoxy(snakePlace[0]);
    cout << HEAD_DIR[(int)direction];
}

void win()
{
    Beep(220, 200);
    Beep(233, 300);
    Beep(262, 100);
    Beep(233, 400);
    Beep(220, 300);
    Beep(233, 100);
    Beep(220, 200);
    Beep(233, 300);
    Beep(262, 100);
    Beep(294, 400);
    Beep(262, 300);
    Beep(350, 100);
    Beep(330, 200);
    Beep(294, 300);
    Beep(262, 100);
    Beep(300, 200);
    Beep(350, 200);
    Beep(294, 200);
    Beep(262, 200);
    Beep(233, 200);
    Beep(220, 400);
    Beep(196, 400);
    Beep(175, 200);
    Beep(100, 100);

    char str[] = "color 01";
    for (int i = 0; i < 60; i++)
    {
        int x = rand()%16, y = rand()%16;
        if (x > 9)
        {
            x = 'a'+x-10;
        }
        else
        {
            x += 48;
        }
        if (y > 9)
        {
            y = 'a'+y-10;
        }
        else
        {
            y += 48;
        }
        str[6] = x;
        str[7] = y;
        int z = 8;//i<20?10:(i<40?8:(i<60?28:43));
        system(str);
        Sleep(z);
    }
    exit(0);
}

void play()
{
    int level = 1;

    for (int i = 0; i < snakeLen; i++)
    {
        gotoxy(snakePlace[i]);
        cout << (i == 0 ? HEAD_DIR[(int)direction] : BODY);
    }
    writeLevel(level);
    putFood();

    /// play start sound
    {
        int a = 60, b = 50;
        int i = 200, j = 150;
        for ( ; i < 500; i += a, j += b)
        {
            Beep(i, j);
        }
        for ( ; i > 200; i -= a, j += b)
        {
            Beep(i, j);
        }
    }

    int x, y;
    int stopTime = 200;
    bool goSleep = true;
    while (true)
    {
        if (goSleep)
        {
            Sleep(stopTime);
        }
        else {
            Sleep(10);
        }
        goSleep = true;

        x = snakePlace[0].X, y = snakePlace[0].Y;
        if (kbhit())
        {
            char ch = getch();

            if (ch == 27) //Esc
            {
                exit(0);
            }
            else if (ch == 'à' || unsigned char(ch) == 224) // Arrow Keys
            {
                ch = getch();
                if (ch == 'M' || ch == 77) // Right
                {
                    if (direction != DirEn::LEFT)
                    {
                        direction = DirEn::RIGHT;
                    }
                }
                else if (ch == 'K' || ch == 75)  // Left
                {
                    if (direction != DirEn::RIGHT)
                    {
                        direction = DirEn::LEFT;
                    }
                }
                else if (ch == 'P' || ch == 80)  // Down
                {
                    if (direction != DirEn::UP)
                    {
                        direction = DirEn::DOWN;
                    }
                }
                else if (ch == 'H' || ch == 72)  // Up
                {
                    if (direction != DirEn::DOWN)
                    {
                        direction = DirEn::UP;
                    }
                }
            }
        }

        switch (direction)
        {
        case DirEn::RIGHT:
            x++;
            break;

        case DirEn::DOWN:
            y++;
            break;

        case DirEn::LEFT:
            x--;
            break;

        case DirEn::UP:
            y--;
        }

        char ch = readxy(x, y);
        if ((ch == ' ') && (y > 0))
        {
            move();
        }
        else if (ch == FOOD)
        {
            if (stopTime > 150)
            {
                stopTime -= 25;
            }
            else if (stopTime > 120)
            {
                stopTime -= 18;
            }
            else if (stopTime > 90)
            {
                stopTime -= 12;
            }
            else
            {
                stopTime -= 6;
            }
            if (stopTime < 50)
            {
                stopTime = 50;
            }
            snakeLen++;
            move(BODY);
            if (level == FINAL_LEVEL)
            {
                win();
            }
            writeLevel(++level);
            putFood();
            goSleep = false;
            Beep(1000, 70);
        }
        else // lose
        {
            system("color 1e");
            Beep(200, 800);
            Sleep(500);
            exit(0);
        }
    }
}
