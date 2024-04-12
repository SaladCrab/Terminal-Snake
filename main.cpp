#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

bool gameRunning = false;
bool won = false;
int width = 50;
int height = 20;
int x, y;
int fruitX, fruitY;
int score;
int bodyLength;
int* bodyX;
int* bodyY;
enum eDirection { STOP = 0, UP, DOWN, RIGHT, LEFT };
eDirection dir;

void Setup() {
    gameRunning = true;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;
    dir = STOP;
    score = 0;
    bodyLength = 1;
    bodyX = new int[width * height];
    bodyY = new int[width * height];
}

void Draw() {
    system("CLS");
    //graphic generation
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {            
            if (j == 0) {
                cout << "#";
            }
            else if (i == fruitY && j == fruitX){
                cout << "$";
            }
            else if (i == y && j == x) {
                cout << "0";
            }
            else {
                bool printBodyPart = false;
                for (int k = 0; k < bodyLength; k++) {
                    if (bodyX[k] == j && bodyY[k] == i) {
                        cout << "o";
                        printBodyPart = true;
                    }
                }
                if (!printBodyPart) {
                    cout << " ";
                }
            }

            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;

    //Snake Pos and Fruit Pos and score
    cout << "Snake X: " << x; cout << setw(15) << "Fruit X: " << fruitX; cout << setw(15) << "Score: " << score << endl;
    cout << "Snake Y: " << y; cout << setw(15) << "Fruit Y: " << fruitY << endl;
}

void Logic() {
    // What direction the snake will use
    if (GetAsyncKeyState('W') & 0x8000 && dir != DOWN) {
        dir = UP;
    }
    if (GetAsyncKeyState('S') & 0x8000 && dir != UP) {
        dir = DOWN;
    }
    if (GetAsyncKeyState('D') & 0x8000 && dir != LEFT) {
        dir = RIGHT;
    }
    if (GetAsyncKeyState('A') & 0x8000 && dir != RIGHT) {
        dir = LEFT;
    }

    // Actually making that direction change its position
    int prevX = x;
    int prevY = y;
    int prev2X, prev2Y;
    int tempX, tempY;
    for (int i = 0; i < bodyLength - 1; i++) {
        tempX = bodyX[i];
        tempY = bodyY[i];
        bodyX[i] = prevX;
        bodyY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    if (dir == UP) {
        y--;
    }
    if (dir == DOWN) {
        y++;
    }
    if (dir == RIGHT) {
        x++;
    }
    if (dir == LEFT) {
        x--;
    }

    // When "colliding" with the fruit do the fruit sht
    if (x == fruitX && y == fruitY) {
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
        score++;
            // Increase body length
        bodyLength++;
            // Add new body segment
        bodyX[bodyLength - 1] = bodyX[bodyLength - 2];
        bodyY[bodyLength - 1] = bodyY[bodyLength - 2];
    }

    
    // When "colliding" with the body die
    for (int i = 0; i < bodyLength; i++) {
        if (x == bodyX[i] && y == bodyY[i]) {
            gameRunning = false;
        }
    }

    // When "colliding" with the edge of the screen die
    if (x < 0 || x >= width - 1 || y < 0 || y >= height - 1) {
        gameRunning = false;
    }

    // WIN
    if (bodyLength == width * height) {
        gameRunning = false;
        won = true;
    }
}

void GameLoop() {
    Setup();
    while (gameRunning) {
        Logic();
        Draw();
        Sleep(10);
    }
}

int main() {
    srand(time(NULL));
    GameLoop();
    delete[] bodyX;
    delete[] bodyY;
    while(!gameRunning){

        if (won == true){
            system("CLS");
            cout << "You Win!" << endl;
            cout << "Type [R] to Restart or [Q] to quit" << endl;
        } else {
            system("CLS");
            cout << "Game Over!" << endl;
            cout << "Type [R] to Restart or [Q] to quit" << endl;
        }

        char choice;
        cin >> choice;

        if ((char)tolower(choice) == 'r'){
            gameRunning = true;
            GameLoop();
        } else {
            break;
        }
    }
    return 0;
}