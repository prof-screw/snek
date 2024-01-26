#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

// defining the height and width of the board
#define WIDTH 80
#define HEIGHT 40

string playerName;

int x, y, fruitX, fruitY, playerScore; // defining the coordinates of the player

bool gameOver; // defining the game state if its still playable or not

enum class snakesDirection : int // enum scoped type for direction input
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
snakesDirection sDir;

// function to initialize the game
void gameInit()
{
    // srand(time(0));
    gameOver = false;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    sDir = snakesDirection::STOP; // type strict and scoped
}

// function to render the game board
void renderBoard(string playerName)
{
    system("clear"); // for mac
    // system("cls");//for windows

    for (int i = 0; i < WIDTH + 2; i++)
    {
        cout << '=';
    }
    cout << "\n";
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            // print the walls on the left and right side
            if (j == 0 || j == WIDTH - 2)
                cout << "||";

            if (i == y && j == x) // player coordinates
            {
                cout << 'O';
            }
            else if (i == fruitY && j == fruitX) // fruit cordinate
            {
                cout << '$';
            }
            else
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
    for (int i = 0; i < WIDTH + 2; i++)
    {
        cout << "=";
    }
    cout << "\n"
         << "\t\t\t\tplayer  : " << playerName << "\n";
    cout << "\t\t\t\tplayer score : " << playerScore << "\n";
}

// function to take an user input
void userInput()
{
    initscr(); // initialize the library
    cbreak();
    // disables line buffering
    nodelay(stdscr, TRUE); // set getch to non-blocking mode

    int ch = getch(); // read a charecter
    switch (ch)
    {
    case 'w':
        sDir = snakesDirection::UP;
        break;
    case 'a':
        sDir = snakesDirection::LEFT;
        break;
    case 's':
        sDir = snakesDirection::DOWN;
        break;
    case 'd':
        sDir = snakesDirection::RIGHT;
        break;
    case 't':
        gameOver = true;
        break;
    default:
        break;
    }

    endwin(); // end the window
}

// function to update the game with new parameters
void updateGame() //! ----------------> needs the tail rules and logic to be implemented <------------------
{
    switch (sDir)
    {
    case snakesDirection::UP:
        y--;
        break;
    case snakesDirection::DOWN:
        y++;
        break;
    case snakesDirection::LEFT:
        x--;
        break;
    case snakesDirection::RIGHT:
        x++;
        break;
    default:

        break;
    }

    if (x == WIDTH || y == HEIGHT || x == 0 || y == 0)
        gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        playerScore += 5;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

int main()
{
    cout << "welcome to snake:Lite"
         << "\n"
         << "Choose your username : ";
    cin >> playerName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    gameInit();

    while (!gameOver)
    {
        renderBoard(playerName);
        userInput();
        updateGame();

        usleep(100 * 1000); // 500 milliseconds

        if (gameOver)
        {
            system("clear");
            main();
        }
    }
}