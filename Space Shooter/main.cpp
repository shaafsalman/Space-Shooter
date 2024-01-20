#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include<fstream>

using namespace std;

#define screenHeight 20
#define screenWidth 30

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

const char allien = 232;
const char specialAllien = 233;
const char bullet = 254;
const char ship = 202;
const int alliensLimit = 3;

int hiscore = 0;

int score = 0;

int lives = 3;

int levels = 1;

char screen[screenHeight][screenWidth];

int shipCol = screenWidth / 2;
int shipRow = screenHeight - 1;

void print()
{
	cout << "****************************************************************************" << endl;
	cout << "****************************************************************************" << endl;

	for (int i = 0; i < screenHeight; i++)
	{

		int hiline = screenHeight / 3;
		int scoreline = screenHeight - 6;
		int speedline = screenHeight / 2;


		if (i == 0)
		{
			cout << "*****    Level :" << levels << "    **";
		}
		else if (i == 2 && levels == 3)
		{

			cout << "*****    hard        **";
			system("color 84");
		}
		else if (i == 4 && levels == 2)
		{

			cout << "*****    Medium      **";

			system("color 81");

		}
		else if (i == 7 && levels == 1)
		{

			cout << "*****    Easy        **";
		}
		else if (i == speedline)
		{
			cout << "***********************";
		}

		else
		{
			cout << "*****                **";
		}

		for (int j = 0; j < screenWidth; j++)
		{

			cout << screen[i][j];
		}  //game ui




		if (i == hiline || i == scoreline)
		{
			cout << "***********************" << endl;

		}
		else if (i == 0)
		{
			cout << "*****   High Score   **" << endl;
		}
		else if (i == 3)
		{
			if (hiscore >= 10 && hiscore < 100)
			{
				cout << "*****      " << hiscore << "       **" << endl;
			}
			else if (hiscore >= 100)
			{
				cout << "*****      " << hiscore << "       **" << endl;
			}
			else
			{
				cout << "*****      " << hiscore << "       **" << endl;
			}
		}




		else if (i == hiline + 1)
		{

			cout << "*****     Score      **" << endl;
		}
		else if (i == hiline + 4)
		{
			if (score >= 10 && score < 100)
			{
				cout << "*****      " << score << "         **" << endl;
			}
			else if (score >= 100)
			{
				cout << "*****      " << score << "         **" << endl;
			}

			else
			{
				cout << "*****      " << score << "         **" << endl;
			}
		}


		else if (i == scoreline + 1)
		{

			cout << "*****     lives      **" << endl;
		}
		else if (i == scoreline + 3)
		{

			cout << "*****       " << lives << "        **" << endl;
		}

		else
		{
			cout << "*****                **" << endl;
		}



	}


	cout << "****************************************************************************" << endl;

	cout << "****************************************************************************" << endl;


}

bool widthBoundaryCheck(int num)
{
	if (num >= screenWidth)
	{
		return false;
	}

	else if (num < 0)
	{
		return false;
	}

	return true;

}

bool heightBoundaryCheck(int num)
{
	if (num >= screenHeight)
	{
		return false;
	}

	else if (num < 0)
	{
		return false;
	}

	return true;

}

bool AllienCheck(int row, int col)
{
	if (screen[row][col] == allien || screen[row][col] == specialAllien)
	{
		return false;
	}

	else
	{
		return true;
	}
}

void moveShip(char key)
{

	if (key == 'd' || key == 'D')
	{
		if (widthBoundaryCheck(shipCol + 1))
		{
			if (AllienCheck(shipRow, shipCol + 1))
			{
				screen[shipRow][shipCol] = ' ';
				shipCol++;
				screen[shipRow][shipCol] = ship;
			}

		}

	}

	else if (key == 'w' || key == 'W')
	{
		if (heightBoundaryCheck(shipRow - 1))
		{
			if (AllienCheck(shipRow - 1, shipCol))
			{
				screen[shipRow][shipCol] = ' ';
				shipRow--;
				screen[shipRow][shipCol] = ship;
			}

		}

	}

	else if (key == 'a' || key == 'A')
	{
		if (widthBoundaryCheck(shipCol - 1))
		{
			if (AllienCheck(shipRow, shipCol - 1))
			{
				screen[shipRow][shipCol] = ' ';
				shipCol--;
				screen[shipRow][shipCol] = ship;
			}

		}

	}

	else if (key == 's' || key == 'S')
	{
		if (heightBoundaryCheck(shipRow + 1))
		{
			if (AllienCheck(shipRow + 1, shipCol))
			{
				screen[shipRow][shipCol] = ' ';
				shipRow++;
				screen[shipRow][shipCol] = ship;
			}

		}
	}

}

void hideCursor()
{
	//hiding the blinking cursor
	HANDLE return1 = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursor;

	GetConsoleCursorInfo(return1, &cursor);

	cursor.bVisible = false;

	SetConsoleCursorInfo(return1, &cursor);
}

bool moveBulletUp()
{
	int bulletRow = shipRow;
	int bulletCol = shipCol;

	bulletRow--;

	while (screen[bulletRow][bulletCol] != allien && screen[bulletRow][bulletCol] != specialAllien && bulletRow >= 0)
	{
		screen[bulletRow][bulletCol] = bullet;

		//////////////////////////////////////////////////
		if (_kbhit())
		{

			char nkey = _getch();

			if (nkey == 'w' || nkey == 'W' || nkey == 'A' || nkey == 'a' || nkey == 's' || nkey == 'S' || nkey == 'D' || nkey == 'd')
			{
				moveShip(nkey);
			}



		}
		/////////////////////////////////////////////////

		system("cls");

		print();

		screen[bulletRow][bulletCol] = ' ';

		bulletRow--;
	}


	if (screen[bulletRow][bulletCol] == allien)
	{
		score += 5;
		screen[bulletRow][bulletCol] = ' ';
		return true;
	}

	else if (screen[bulletRow][bulletCol] == specialAllien)
	{
		score += 10;
		screen[bulletRow][bulletCol] = ' ';
		return true;
	}

	else
	{
		return false;
	}
}

int shipHitCheck(int allienRow[], int allienCol[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (screen[allienRow[i]][allienCol[i]] == ship)
		{
			return false;
		}
	}
	return true;

}

int findMin(int array[], int n)
{
	int min = 0;

	for (int i = 1; i < n; i++)
	{
		if (array[i] < array[min])
		{
			min = i;
		}
	}

	return min;

}

void blinkingEffect()
{
	for (int i = 0; i <= 5; i++)
	{
		system("cls");

		if (i % 2 == 0)
		{
			screen[shipRow][shipCol] = ' ';
		}

		else
		{
			screen[shipRow][shipCol] = ship;
		}

		print();
		Sleep(200);
	}

}

bool moveBulletsDown(int allienRow[], int allienCol[], int n)
{
	int i;
	int minShooter = findMin(allienRow, n);

	for (i = 0; i < n; i++)
	{
		allienRow[i]++;
	}

	while (allienRow[minShooter] < screenHeight && shipHitCheck(allienRow, allienCol, n))
	{

		for (i = 0; i < n; i++)
		{
			screen[allienRow[i]][allienCol[i]] = bullet;
		}

		////////////////////////////////////////
		if (_kbhit())
		{
			char nkey = _getch();

			if (nkey == 'w' || nkey == 'W' || nkey == 'A' || nkey == 'a' || nkey == 's' || nkey == 'S' || nkey == 'D' || nkey == 'd')
			{
				moveShip(nkey);
			}
		}
		////////////////////////////////////////////////

		system("cls");

		print();

		for (i = 0; i < n; i++)
		{
			screen[allienRow[i]][allienCol[i]] = ' ';
		}

		for (i = 0; i < n; i++)
		{
			allienRow[i]++;
		}

	}

	if (!shipHitCheck(allienRow, allienCol, n))
	{
		blinkingEffect();
		lives--;
		return true;
	}

	return false;

	/*
	for (i = 0; i < n; i++)
	{
	screen[allienRow[i]][allienCol[i]] = ' ';
	}
	*/

}


void allienShooter(int& randomCol, int& rowShooter)
{
	bool check = true;

	while (check)
	{
		randomCol = rand() % screenWidth;

		rowShooter = alliensLimit;


		while (rowShooter >= 0 && screen[rowShooter][randomCol] != allien && screen[rowShooter][randomCol] != specialAllien)
		{
			rowShooter--;
		}

		if (rowShooter >= 0)
		{
			check = false;
		}

	}
}

bool checkRepition(int array1[], int array2[], int limit)
{
	for (int i = 0; i < limit; i++)
	{
		if (array1[limit] == array1[i] && array2[limit] == array2[i])
		{
			return false;
		}
	}

	return true;

}

int alliensCheck()
{
	int count = 0;
	bool check1;
	int i;

	for (int j = 0; j < screenWidth; j++)
	{
		i = alliensLimit;

		check1 = true;
		while (screen[i][j] != allien && screen[i][j] != specialAllien)
		{
			if (i == 0)
			{
				check1 = false;
				break;
			}

			i--;

		}

		if (check1)
		{
			count++;
		}

	}


	return count;


}

bool allienAttack(int allienRow[], int allienCol[], int simpleAttacks, int specialAttacks, int& iterations, int alliens)
{

	if (iterations >= 0)//Simple Attack
	{

		for (int i = 0; i < simpleAttacks; i++)
		{
			allienShooter(allienCol[0], allienRow[0]);
			if (moveBulletsDown(allienRow, allienCol, 1))
			{
				if (lives == 0)
				{
					return true;
				}
			}
		}

	}

	else
	{

		if (alliens < specialAttacks)
		{
			specialAttacks = alliens;
		}

		int i = 0;

		while (i < specialAttacks)
		{
			allienShooter(allienCol[i], allienRow[i]);

			if (checkRepition(allienRow, allienCol, i))
			{
				i++;
			}

		}

		if (moveBulletsDown(allienRow, allienCol, specialAttacks))
		{
			if (lives == 0)
			{
				return true;
			}
		}

	}

	return false;

}

void initializeScreen()
{
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			screen[i][j] = ' ';
		}
	}

	screen[shipRow][shipCol] = ship;

	for (int i = 0; i < alliensLimit; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			screen[i][j] = allien;
		}
	}

	int randomRow;
	int randomCol;
	for (int i = 0; i < 30; i++)
	{
		randomCol = rand() % screenWidth;
		randomRow = rand() % alliensLimit;

		screen[randomRow][randomCol] = specialAllien;

	}

	system("cls");
	print();

}

void gameOverMessage() {
	system("cls");
	cout << endl;

	cout << "                 ****       ******      **         ***    *********              ****                           **********      ********                 \n";
	cout << "               **          **     **    ** **   **  **    *                    **     **     **           **    *               *      *                 \n";
	cout << "               **          **     **    **   ***    **    *                    **     **      **         **     *               *     *                  \n";
	cout << "               **   ****   *********    **   ***    **    *****      ________  **     **       **       **      *********       * * *                    \n";
	cout << "               **     **   **     **    **    **    **    *                    **     **         **    **       *               *    *                   \n";
	cout << "                *******    **     **    **    *     **    ********              *******            ***          *********       *      *                 \n";
	Sleep(5000);
}

void instructions()
{
	cout << "\n\n\Hello!\n\n\nWelcome to Instructions\n\nPress A to move left\nPress D to move right\nPress space bar to fire\n\nYou  will have " << lives << " \nEach life eliminates after being shot\n\nThanks! Good Luck\n";

}

int  menu()
{

	system("cls");


	cout << "                                  -------------------------- \n";
	cout << "                                 |     Space Shooter        | \n";
	cout << "                                  --------------------------\n";
	cout << "                                 1. Start Game\n";
	cout << "                                 2. Instructions\n";
	cout << "                                 3. Quit\n";
	cout << "                                 Select option: \n";


	int option = 0;
	cin >> option;

	while (option < 0 && option > 4)
	{
		cout << "invalid choice \n";
		cin >> option;


	}

	return option;

}

void updateLevel(int& nextLevelScore, int& simpleAttack, int& specialAttacks, int& specialAttackTime, int& iterations)
{
	nextLevelScore += 30;
	levels++;
	simpleAttack++;
	specialAttacks += 2;
	specialAttackTime--;
	iterations = 0;
}

int main()
{
	srand(time(0));
	hideCursor();

	int option;

	option = menu();

	int nextLevelScore = 30;

	ifstream inFile;
	ofstream outFile;

	inFile.open("highscore.txt");
	inFile >> hiscore;
	inFile.close();

	do
	{


		if (option == 1)
		{

			lives = 3;
			score = 0;
			levels = 1;

			initializeScreen();

			int allienRow[10];
			int allienCol[10];

			char key;

			int shipCol = screenWidth / 2;
			int shipRow = screenHeight - 1;

			int simpleAttack = 1;
			int specialAttacks = 3;
			int specialAttackTime = 5;

			int iterations = 0;

			int alliens;

			do
			{

				key = _getch();

				if (key == 'w' || key == 'W' || key == 'A' || key == 'a' || key == 's' || key == 'S' || key == 'D' || key == 'd')
				{
					moveShip(key);
				}

				else if (key == ' ')
				{
					if (moveBulletUp())
					{
						if (hiscore <= score)
						{
							hiscore = score;
						}

						if (score > nextLevelScore && levels < 5)
						{
							updateLevel(nextLevelScore, simpleAttack, specialAttacks, specialAttackTime, iterations);
						}

						if (iterations == specialAttackTime)
						{
							iterations = -1;

						}

						alliens = alliensCheck();

						if (alliens)
						{
							if (allienAttack(allienRow, allienCol, simpleAttack, specialAttacks, iterations, alliens))
							{
								gameOverMessage();
								option = menu();
								break;
							}
						}

						else
						{
							initializeScreen();
						}

						iterations++;

					}

				}

				else
				{

				}

				system("cls");

				print();

			} while (true);


			outFile.open("highscore.txt");
			outFile << hiscore;
			outFile.close();


		}

		else if (option == 2)
		{
			instructions();

			cout << "press 1 to start game\n";
			cout << "press 3 to  exit \n ";
			cin >> option;

			while (option < 0 || option >= 4)
			{
				cout << "\nInvalid Option!\n";
				cin >> option;
			}
		}


	} while (option != 3);


	system("pause");
	return 0;
}