#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include<fstream>

using namespace std;

#define screenHeight 30
#define screenWidth 100
#define shapeRows 3
#define shapeCols 5

char screen[screenHeight][screenWidth];

int scores[screenHeight / shapeRows][screenWidth / shapeCols];

const char ship[shapeRows][shapeCols] = { ' ', ' ', 24, ' ', ' ', 30, 24, 24, 24, 30, 24, 24, 24, 24, 24 };
const char allien[shapeRows][shapeCols] = { 25, 25, 25, 25, 25, 31, 25, 25, 25, 31, ' ', ' ', 25, ' ', ' ' };
const char specialAllien[shapeRows][shapeCols] = { 233, 233, 233, 233, 233, 31, 233, 233, 233, 31, ' ', ' ', 233, ' ', ' ' };

int shipColStart = (screenWidth / 2);
int shipRowStart = screenHeight - shapeRows;


int nextLevelScore = 30;
const char bullet = 254;
const int alliensLimit = 9;

const int simpleScore = 5;
const int specialScore = 10;
bool specialattack = true;


int hiscore = 0;

int score;

int lives = 3;

int levels = 1;

void hideCursor()
{
	//hiding the blinking cursor
	HANDLE return1 = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursor;

	GetConsoleCursorInfo(return1, &cursor);

	cursor.bVisible = false;

	SetConsoleCursorInfo(return1, &cursor);
}

void print()
{

	int hiline = screenHeight / 3;
	int scoreline = screenHeight - 6;
	int speedline = screenHeight / 2;
	bool half = 0;

	cout << "****************************************************************************************************************************************************************************************" << endl;
	cout << "****************************************************************************************************************************************************************************************" << endl;
	for (int i = 0; i < screenHeight; i++)
	{
		//cout << "***              ***";
		/*
		if (i % shapeRows == 0 && i != 0)
		{
			cout << endl;
		}*/




		if (i == 0)
		{
			cout << "*****    Level :" << levels << "    **";
		}
		else if (i == 2 && levels == 3)
		{

			cout << "*****    hard        **";
			system("color 04");
		}
		else if (i == 4 && levels == 2)
		{

			cout << "*****    Medium      **";

			system("color 01");

		}
		else if (i == 7 && levels == 1)
		{

			cout << "*****    Easy        **";
		}
		else if (i == speedline)
		{
			cout << "***********************";
		}
		else if (i == 11)
		{

			cout << "*****next level Score**";

		}
		else if (i == 14)
		{
			if (nextLevelScore < 100)
			{
				cout << "*****      " << nextLevelScore << "        **";
			}

		}


		else if ((i == 16) && (specialattack == true))
		{
			cout << "***** special attack **";
		}
		else if ((i == 18) && (specialattack == true))
		{
			cout << "*****   incoming!    **";

		}
		else if ((i == 16) && (specialattack == false))
		{
			cout << "*****    status      **";


		}
		else if ((i == 18) && (specialattack == false))
		{
			cout << "*****    active      **";

		}
		else
		{
			cout << "*****                **";
		}












		for (int j = 0; j < screenWidth; j++)
		{

			if (j != 0 && j % shapeCols == 0)
			{
				cout << "  ";
			}
			cout << screen[i][j];


		}


















		if (i == hiline || i == scoreline)
		{
			cout << "***********************" << endl;

		}

		else if (i == 0)
		{
			cout << "*****   High Score   **" << endl;
		}
		else if (i == 4)
		{
			if (hiscore >= 10 && hiscore < 100)
			{
				cout << "*****      " << hiscore << "        **" << endl;
			}
			else if (hiscore >= 100)
			{
				cout << "*****      " << hiscore << "       **" << endl;
			}
			else
			{
				cout << "*****      " << hiscore << "         **" << endl;
			}
		}


		else if (i == hiline + 3)
		{

			cout << "*****     Score      **" << endl;
		}
		else if (i == hiline + 4)
		{
			if (score >= 10 && score < 100)
			{
				cout << "*****      " << score << "        **" << endl;
			}
			else if (score >= 100)
			{
				cout << "*****      " << score << "       **" << endl;
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
	cout << "****************************************************************************************************************************************************************************************" << endl;
	cout << "****************************************************************************************************************************************************************************************" << endl;

	/*cout << "Lives: " << lives << endl;
	cout << "High Score: " << hiscore << endl;
	cout << "Score: " << score << endl;
	cout << "Levels: " << levels << endl;
	*/

}

//////////////////////////////////////////////////////////

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
	char temp = 233;

	if (screen[row][col] == temp || screen[row][col] == 25)
	{
		return false;
	}

	return true;

}

void shiftShip(int startRow, int startCol)
{
	int k, l;

	k = startRow;
	for (int i = 0; i < shapeRows; i++)
	{
		l = startCol;
		for (int j = 0; j < shapeCols; j++)
		{
			screen[k][l] = ship[i][j];
			l++;
		}
		k++;
	}
}

void moveShip(char key)
{
	if (key == 'd' || key == 'D')
	{
		if (widthBoundaryCheck(shipColStart + shapeCols))
		{
			if (AllienCheck(shipRowStart, shipColStart + shapeCols))
			{

				for (int i = shipRowStart; i < shipRowStart + shapeRows; i++)
				{
					for (int j = shipColStart; j < (shipColStart + shapeCols); j++)
					{
						screen[i][j] = ' ';
					}
				}
				shipColStart += shapeCols;
				shiftShip(shipRowStart, shipColStart);
			}

		}

	}

	else if (key == 'w' || key == 'W')
	{
		if (heightBoundaryCheck(shipRowStart - shapeRows))
		{
			if (AllienCheck(shipRowStart - 1, shipColStart + 2))
			{
				for (int i = shipRowStart; i < shipRowStart + shapeRows; i++)
				{
					for (int j = shipColStart; j < (shipColStart + shapeCols); j++)
					{
						screen[i][j] = ' ';
					}
				}
				shipRowStart -= shapeRows;
				shiftShip(shipRowStart, shipColStart);
			}

		}

	}

	else if (key == 'a' || key == 'A')
	{
		if (widthBoundaryCheck(shipColStart - shapeCols))
		{
			if (AllienCheck(shipRowStart, shipColStart - 1))
			{
				for (int i = shipRowStart; i < shipRowStart + shapeRows; i++)
				{
					for (int j = shipColStart; j < (shipColStart + shapeCols); j++)
					{
						screen[i][j] = ' ';
					}
				}
				shipColStart -= shapeCols;
				shiftShip(shipRowStart, shipColStart);
			}

		}

	}

	else if (key == 's' || key == 'S')
	{
		if (heightBoundaryCheck(shipRowStart + shapeRows))
		{

			for (int i = shipRowStart; i < shipRowStart + shapeRows; i++)
			{
				for (int j = shipColStart; j < (shipColStart + shapeCols); j++)
				{
					screen[i][j] = ' ';
				}
			}
			shipRowStart += shapeRows;
			shiftShip(shipRowStart, shipColStart);


		}
	}

}

////////////////////////////////////////////////////////

int checkAllienHit(int bulletRow, int bulletCol)
{
	int scoreRow;
	int scoreCol;

	if (bulletRow < alliensLimit)
	{

		scoreRow = (bulletRow / shapeRows);
		scoreCol = (bulletCol / shapeCols);

		return scores[scoreRow][scoreCol];

	}

	return 0;

}

void vanishAllien(int bulletRow, int bulletCol)
{
	bulletRow -= 2;
	for (int i = bulletRow; i < bulletRow + shapeRows; i++)
	{
		for (int j = bulletCol; j < bulletCol + shapeCols; j++)
		{
			screen[i][j] = ' ';
		}
	}
}

bool moveBulletUp()
{
	int totalScore;

	int bulletRow = shipRowStart + 1;
	int bulletCol1 = shipColStart;
	int bulletCol2 = shipColStart + 4;

	do
	{
		bulletRow--;

		screen[bulletRow][bulletCol1] = bullet;
		screen[bulletRow][bulletCol2] = bullet;
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

		screen[bulletRow][bulletCol1] = ' ';
		screen[bulletRow][bulletCol2] = ' ';

		totalScore = checkAllienHit(bulletRow, bulletCol1);

	} while ((totalScore) == 0 && bulletRow >= 0);

	if (totalScore > 0)
	{
		score += totalScore;
		scores[bulletRow / shapeRows][bulletCol1 / shapeCols] = 0;
		vanishAllien(bulletRow, bulletCol1);
		return true;
	}

	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////

int shipHitCheck(int allienRow[], int allienCol[], int n)
{
	char target = 30;

	for (int i = 0; i < n; i++)
	{
		if (screen[allienRow[i]][allienCol[i]] == target && screen[allienRow[i]][allienCol[i] + 4] == target)
		{
			return false;
		}
	}

	return true;

}

void blinkingEffect()
{
	for (int lcv = 0; lcv <= 5; lcv++)
	{

		if (lcv % 2 == 0)
		{
			for (int i = shipRowStart; i < shipRowStart + shapeRows; i++)
			{
				for (int j = shipColStart; j < shipColStart + shapeCols; j++)
				{
					screen[i][j] = ' ';
				}
			}
		}

		else
		{
			int k, l;
			k = shipRowStart;
			for (int i = 0; i < shapeRows; i++)
			{
				l = shipColStart;
				for (int j = 0; j < shapeCols; j++)
				{
					screen[k][l] = ship[i][j];
					l++;
				}
				k++;
			}
		}

		system("cls");
		print();
		Sleep(200);
	}

}

int findMax(int array[], int n)
{
	int max = 0;

	for (int i = 1; i < n; i++)
	{
		if (array[i] > array[max])
		{
			max = i;
		}
	}

	return max;

}

void eliminateMaxShooter(int allienRow[], int allienCol[], int& n, int maxShooter)
{
	int max = allienRow[maxShooter];

	for (int i = 0; i < n; i++)
	{
		if (allienRow[i] == max)
		{
			for (int j = i; j < n - 1; j++)
			{
				allienRow[j] = allienRow[j + 1];
				allienCol[j] = allienCol[j + 1];
			}
			n--;
			i--;
		}
	}

}

bool moveBulletsDown(int allienRow[], int allienCol[], int n)
{
	int maxShooter;
	bool hitCheck;

	//Translate scores into screen
	for (int i = 0; i < n; i++)
	{
		allienRow[i] = allienRow[i] * 3 + 2;
		allienCol[i] = allienCol[i] * 5;
	}

	maxShooter = findMax(allienRow, n);

	do
	{
		for (int i = 0; i < n; i++)
		{
			screen[allienRow[i]][allienCol[i]] = bullet;
			screen[allienRow[i]][allienCol[i] + 4] = bullet;
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

		for (int i = 0; i < n; i++)
		{
			screen[allienRow[i]][allienCol[i]] = ' ';
			screen[allienRow[i]][allienCol[i] + 4] = ' ';
		}


		for (int i = 0; i < n; i++)
		{
			allienRow[i]++;
		}

		hitCheck = shipHitCheck(allienRow, allienCol, n);

		if (allienRow[maxShooter] >= 30)
		{
			eliminateMaxShooter(allienRow, allienCol, n, maxShooter);
			maxShooter = findMax(allienRow, n);
		}


	} while (n > 0 && hitCheck);



	if (!hitCheck)
	{
		blinkingEffect();
		lives--;
		return true;
	}

	return false;


}

bool scoresAllienCheck(int row, int col)
{
	if (scores[row][col] == simpleScore || scores[row][col] == specialScore)
	{
		return false;
	}

	return true;

}

void allienShooter(int& randomCol, int& rowShooter)
{
	bool check = true;

	while (check)
	{
		randomCol = rand() % (screenWidth / shapeCols);

		rowShooter = alliensLimit / shapeRows;

		while (rowShooter >= 0 && scoresAllienCheck(rowShooter, randomCol))
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

bool allienAttack(int allienRow[], int allienCol[], int simpleAttacks, int specialAttacks, int& iterations, int alliens)
{

	for (int i = 0; i < 20; i++)
	{
		allienRow[i] = 0;
		allienCol[i] = 0;
	}

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
		/// <summary>
		/// /
		/// </summary>
		/// <param name="allienRow"></param>
		/// <param name="allienCol"></param>
		/// <param name="simpleAttacks"></param>
		/// <param name="specialAttacks"></param>
		/// <param name="iterations"></param>
		/// <param name="alliens"></param>
		/// <returns></returns>

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

//////////////////////////////////////////////////////////////////////

int alliensCheck()
{
	int count = 0;
	bool check1;
	int i;

	for (int j = 0; j < screenWidth / shapeCols; j++)
	{
		i = alliensLimit / shapeRows;//alliensLimit

		check1 = true;
		while (scores[i][j] != 5 && scores[i][j] != 10)
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

void initializeScreen()
{

	int i = 0, j = 0, k = 0, l = 0;

	for (i = 0; i < screenHeight; i++)
	{
		for (j = 0; j < screenWidth; j++)
		{
			screen[i][j] = ' ';
			if (((i + 1) % shapeRows == 0) && ((j + 1) % shapeCols == 0))
			{
				scores[i / shapeRows][j / shapeCols] = 0;
			}
		}
	}

	k = shipRowStart;
	for (i = 0; i < shapeRows; i++)
	{
		l = shipColStart;
		for (int j = 0; j < shapeCols; j++)
		{
			screen[k][l] = ship[i][j];
			l++;
		}
		k++;
	}

	for (int row = 0; row < alliensLimit; row += 3)
	{
		for (int col = 0; col < screenWidth; col += 5)
		{
			k = row;
			for (i = 0; i < shapeRows; i++)
			{
				l = col;
				for (j = 0; j < shapeCols; j++)
				{
					screen[k][l] = allien[i][j];
					if (((k + 1) % shapeRows == 0) && ((l + 1) % shapeCols == 0))
					{
						scores[k / shapeRows][l / shapeCols] = simpleScore;
					}

					l++;
				}
				k++;

			}
		}

	}


	int randomRow;
	int randomCol;
	for (int i = 0; i < ((screenWidth / shapeCols) / 2); i++)//10 number of random special alliens
	{
		randomCol = rand() % (screenWidth / shapeCols);
		randomRow = rand() % shapeRows;

		k = randomRow * shapeRows;
		for (int i = 0; i < shapeRows; i++)
		{
			l = randomCol * shapeCols;
			for (int j = 0; j < shapeCols; j++)
			{
				screen[k][l] = specialAllien[i][j];
				if (((k + 1) % shapeRows == 0) && ((l + 1) % shapeCols == 0))
				{
					scores[k / shapeRows][l / shapeCols] = specialScore;
				}
				l++;
			}
			k++;
		}

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

////////////////////////////////////////////////////////////////////////

int main()
{
	srand(time(0));
	hideCursor();

	int option;

	option = menu();

	ifstream inFile;
	ofstream outFile;

	inFile.open("highscore.txt");
	inFile >> hiscore;
	inFile.close();

	do
	{

		if (option == 1)
		{
			initializeScreen();

			int allienRow[10];
			int allienCol[10];

			char key;

			int simpleAttack = 1;
			int specialAttacks = 3;
			int specialAttackTime = 5;

			int iterations = 0;



			int alliens;

			lives = 3;
			score = 0;
			levels = 1;

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
