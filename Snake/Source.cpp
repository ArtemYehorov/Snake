#include<iostream>
#include<windows.H>
#include<ctime>
#include<conio.h>
#include<algorithm>

using namespace std;

bool gameOver;

int tailX[100], tailY[100];

int NTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

int main();

void Draw(const int& W, const int& H, int& x, int& y, int& EX, int& EY, int& score)
{
	system("cls");
	for (int i = 0; i < W; i++)
	{
		cout << "#";
	}
	cout << endl;
																					
	for (int i = 0; i < H; i++)														
	{																				
		for (int j = 0; j < W; j++)
		{
			if (j == 0 || j == W - 1)
				cout << "#";

			if (i == y && j == x) 
				cout << "0";

			else if (i == EY && j == EX)
				cout << "F";

			else {
				bool print = false;
				for (int r = 0; r < NTail; r++)
				{
					if (tailX[r] == j && tailY[r] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print) cout << " ";
			}

		}
		cout << endl;
	}

	for (int i = 0; i < W + 1; i++)
	{
		cout << "#";
	}
	cout << endl;
	
	cout << "Score : " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch ())
		{
		case 'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case'x':
			gameOver = true;
			break;
		}
	}
	

	
}

void LOgic(const int &W, const int &H, int &x, int &y, int &EX, int &EY, int &score)
{
	int prewX = tailX[0];
	int prewY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prew2X, prew2Y;

	for (int i = 1; i < NTail; i++)
	{
		prew2X = tailX[i];
		prew2Y = tailY[i];
		tailX[i] = prewX;
		tailY[i] = prewY;
		prewX = prew2X;
		prewY = prew2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;	
	}

	if (x >= W - 1) x = 0;
	else if (x < 0) x = W - 2;

	if (y >= H) y = 0;
	else if (y < 0) y = H - 1;

	for (int i = 1; i < NTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
			system("cls");
			cout << "умер из за того что врезался в хвост" << endl;
		}
	}

	if (x == EX && y == EY)
	{
		NTail++;
		score += 100;
		EX = rand() % 19;
		EY = rand() % 19;
	}
	
}

int Setup();

int main()
{
	int EatX, EatY;
	int score = 0;
	const int WIDTH = 20;
	const int HEIGHT = 20;
	int x, y;

	gameOver = false;
	dir = STOP;
	x = WIDTH / 2 - 1;
	y = HEIGHT / 2;
	EatX = rand() % WIDTH - 1;
	EatY = rand() % HEIGHT;

	setlocale(0, "ru");
	srand(time(0));

	while (!gameOver)
	{
		Draw(WIDTH, HEIGHT, x, y, EatX, EatY, score);
		Input();
		LOgic(WIDTH, HEIGHT, x, y, EatX, EatY, score);
	}
}
