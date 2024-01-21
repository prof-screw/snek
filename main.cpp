#include <iostream>
#include <ctime>
using namespace std;

// defining the height and width of the board
#define WIDTH 80
#define HEIGHT 20

string playerName;

int x, y, fruitX, fruitY; // defining the coordinates of the player

bool gameState; // defining the game state if its still playable or not

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
    gameState = false;
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
         << "\t\t\t\tplayer  : " << playerName << "\n"
         << "\t\t\t\tplayerScore : ";
}

// function to take an user input
void userInput(){};

// function to update the game with new parameters
void updateGame(){};

int main()
{
    cout << "welcome to snake:Lite"
         << "\n"
         << "Choose your username : ";
    cin >> playerName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    gameInit();

    // while (!gameState)
    renderBoard(playerName);
    // userInput();
}