#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Wypełnienie tablicy zerami "Wyczyszczenie jej"
void generate_battlefield(int battlefiled[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			battlefiled[i][j] = 0;
		}
	}
}

//Generowanie planszy
//0 - Wolne miejsce
//5 - "fale"
//11-14 - statek jednomasztowy
//21-13 - statek dwumasztowy
//31-12 - statek trzymasztowy
//41 - statek czteromasztowy
//ponad 100 - trafiony
//2- zatopiony

void generate_playground(int battlefield[10][10], int counter, int number_of_shoot)
{
	int y_sign = 65, i, j;
	printf_s("\nPozostalo do zestrzelenia %d statkow", counter);
	printf_s("\nOddanych zostalo %d strzalow", number_of_shoot);
	printf_s("\n--------------------------------------------------------------------");
	printf_s("\n|     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |");
	printf_s("\n--------------------------------------------------------------------");

	for (i = 0; i < 10; i++)
	{
		printf_s("\n|  %c  |", y_sign++);
		for (j = 0; j < 10; j++)
		{
			if (battlefield[i][j] == 0)
			{
				printf_s("     |");
			}
			else if (battlefield[i][j] >109 && battlefield[i][j] < 152)
			{
				printf_s("  x  |");

			}
			else if (battlefield[i][j] == 2)
			{
				printf_s("  S  |");

			}
			else if (battlefield[i][j] == 99)
			{
				printf_s("  *  |");

			}
			else
			{
				printf_s("     |");
			}
		}
		printf_s("\n--------------------------------------------------------------------");
	}
}void clear_input()
{
	while (getchar() != '\n');
}
int check(int battlefield[10][10], int x, int y,int length,int direction)
{
	//sprawdzenie poziomu
	if (direction == 3)
	{
		if ((y - length) < 0)
		{
			return 1;
		}
		for (int j = y; j > (y - length); j--)
		{
			if (battlefield[x][j] != 0)
			{
				return 1;
			}
		}
	}
	else if (direction == 1)
	{
		if ((y + length) > 9)
		{
			return 1;
		}
		for (int j = y; j < (y + length); j++)
		{
			if (battlefield[x][j] != 0)
			{
				return 1;
			}
		}
	}

	//sprawdzenie pionu
	else if (direction == 2)
	{
		if ((x + length) > 9)
		{
			return 1;
		}
		for (int i = x; i < (x + length); i++)
		{
			if (battlefield[i][y] != 0)
			{
				return 1;
			}
		}
	}
	else if (direction == 0)
	{
		if ((x - length) < 0)
		{
			return 1;
		}
		for (int i = x; i > (x - length); i--)
		{
			if (battlefield[i][y] != 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

void place_warships(int battlefield[10][10], int x, int y, int length, int direction,int type)
{
	if (direction == 0)
	{
		for (int i = x - length; i <= x+1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (i >= 0 && j <= 9 && i <= 9 && j >= 0)
				{
					battlefield[i][j] = 5;
				}
			}
		}
		for (int i = x; i > (x - length); i--)
		{
			battlefield[i][y] = type;
		}
	}
	else if (direction == 2)
	{
		for (int i = x - 1; i <= x + length; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (i >= 0 && j <= 9 && i <= 9 && j >= 0)
				{
					battlefield[i][j] = 5;
				}
			}
		}
		for (int i = x; i < (x + length); i++)
		{
			battlefield[i][y] = type;
		}
	}
	else if (direction == 1)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + length; j++)
			{
				if (i >= 0 && j <= 9 && i <= 9 && j >= 0)
				{
					battlefield[i][j] = 5;
				}
			}
		}
		for (int j = y; j < (y + length); j++)
		{
			battlefield[x][j] = type;
		}
	}
	else if (direction == 3)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - length; j <= y + 1; j++)
			{
				if (i >= 0 && j <= 9 && i <= 9 && j >= 0)
				{
					battlefield[i][j] = 5;
				}
			}
		}
		for (int j = y; j > (y - length); j--)
		{
			battlefield[x][j] = type;
		}
	}
	
}
void generate_warships(int battlefield[10][10])
{
	int length,type;
	int x = 0, y = 0, direction = 0;
	for (int cm = 1; cm > 0; cm--)
	{
		length = 4;
		type = 40 + cm;
		for (int i = 0; i < 1; i++)
		{
			x = ((double)rand() / RAND_MAX) * (10);
			y = ((double)rand() / RAND_MAX) * (10);
			direction = ((double)rand() / RAND_MAX) * 4;
			if (!check(battlefield, x, y, length, direction))
			{
				place_warships(battlefield, x, y, length, direction,type);
			}
			else
			{
				i--;
			}
		}
	}
	for (int tm = 2; tm > 0; tm--)
	{
		length = 3;	
		type = 30 + tm;
		for (int i = 0; i < 1; i++)
		{
			x = ((double)rand() / RAND_MAX) * (10);
			y = ((double)rand() / RAND_MAX) * (10);
			direction = ((double)rand() / RAND_MAX) * 4;
			if (!check(battlefield, x, y, length, direction))
			{
				place_warships(battlefield, x, y, length, direction, type);
			}
			else
			{
				i--;
			}
		}
	}
	for (int dm = 3; dm > 0; dm--)
	{
		length = 2;
		type = 20 + dm;
		for (int i = 0; i < 1; i++)
		{
			x = ((double)rand() / RAND_MAX) * (10);
			y = ((double)rand() / RAND_MAX) * (10);
			direction = ((double)rand() / RAND_MAX) * 4;
			if (!check(battlefield, x, y, length, direction))
			{
				place_warships(battlefield, x, y, length, direction, type);
			}
			else
			{
				i--;
			}
		}
	}
	for (int jm = 4; jm > 0; jm--)
	{
		length = 1;
		type = 10 + jm;
		for (int i = 0; i < 1; i++)
		{
			x = ((double)rand() / RAND_MAX) * (10);
			y = ((double)rand() / RAND_MAX) * (10);
			direction = ((double)rand() / RAND_MAX) * 4;
			if (!check(battlefield, x, y, length, direction))
			{
				place_warships(battlefield, x, y, length, direction, type);
			}
			else
			{
				i--;
			}
		}
	}

}

int check_sunk(int battlefield[10][10], int x, int y, int shoot)
{
	int range=0;
	if (shoot > 9 && shoot < 20)
	{
		range = 1;
	}
	else if (shoot >= 20 && shoot < 30)
	{
		range = 2;
	}
	else if (shoot >= 30 && shoot < 40)
	{
		range = 3;
	}
	else if (shoot >= 40 && shoot < 50)
	{
		range = 4;
	}

	for (int i = x - range; i <= x + range; i++)
	{
		for (int j = y - range; j <= y + range; j++)
		{
			if (i >= 0 && j <= 9 && i <= 9 && j >= 0)
			{
				if (battlefield[i][j] == shoot)
				{
					return 1;
				}
			}
		}
	}
	return 0;

}
void sunk(int battlefiled[10][10], int shoot)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			if (battlefiled[i][j] == shoot+100)
			{
				battlefiled[i][j] = 2;
			}
		}
	}
}
void check_win(int counter)
{
	if (counter <= 0)
	{
		printf_s("\nGratulacje wygrales\n");
		system("pause");
	}
}
void hit(int battlefield[10][10], int counter, int number_of_shoot)
{
	int shoot;
	char coordtmp;
	int coord[2] = { 0,0 };
	counter = 10;
	for (counter; counter > 0; )
	{
		printf_s("\nPodaj koordynarty: ");
		scanf_s("%c", &coordtmp, 2);
		scanf_s("%d", &coord[1]);
		coord[0] = (int)coordtmp;
		clear_input();
		if (coord[0] >= 65 && coord[0] <= 74)
		{
			coord[0] -= 65;
		}
		else if (coord[0] >= 97 && coord[0] <= 106)
		{
			coord[0] -= 97;
		}
		else
		{
			coord[0] = -1;
		}
		if (coord[1] < 1 || coord[1]>10)
		{
			coord[1] = -1;
		}
		if (coord[0] == -1 || coord[1] == -1)
		{
			printf_s("\nWprowadzono bledne dane!");
			generate_playground(battlefield, counter, number_of_shoot);
		}
		else
		{
			coord[1] --;
			shoot = battlefield[coord[0]][coord[1]];
			if (shoot == 2 || (shoot > 109 && shoot < 152))
			{
				printf_s("\nStrzal w to miejsce juz zostal oddany wczesniej");
				generate_playground(battlefield, counter,number_of_shoot);
			}
			else if (shoot >9 && shoot<52)
			{
				number_of_shoot++;
				printf_s("\nGratulacje, trafiles w okret");
				battlefield[coord[0]][coord[1]] = shoot+100;
				if(!check_sunk(battlefield, coord[0],coord[1],shoot))
				{
					printf_s("\nTrafiony zatopiony");
					sunk(battlefield, shoot);
					counter--;
				}
				generate_playground(battlefield, counter, number_of_shoot);
			}
			else if(shoot == 0 || shoot == 5)
			{
				number_of_shoot++;
				printf_s("\nPudlo");
				battlefield[coord[0]][coord[1]] = 99;
				generate_playground(battlefield, counter, number_of_shoot);
			}
		}
		check_win(counter);
	}
}

//0 - Wolne miejsce
//5 - "fale"
//10 - statek
//20 - trafiony
//2- pudło gracza
//60- zestrzelony cały okręt
void menu(int battlefield[10][10],int counter)
{
	int number_of_shoot = 0;
	char inputc;
	printf_s("\nWitaj w grze Statki");
	printf_s("\nAby wygrac zestrzel 10 okretow");
	printf_s("\nx-oznacza pojedyncze trafienie okretu");
	printf_s("\nS-oznacza zatopienie calego okretu");
	printf_s("\n*-oznacza pudlo");
	printf_s("\nWcisnij f aby wystartowac, wcisnij dowolny klawisz aby wyjsc: ");
	scanf_s("%c", &inputc,1);
	int input = (int)inputc;
	clear_input();
	if (input == 70 )
	{
		input = 102;
	}
	if (input == 102)
	{
		generate_battlefield(battlefield);
		generate_playground(battlefield,counter, number_of_shoot);
		generate_warships(battlefield);
		hit(battlefield, counter,number_of_shoot);
	}
	else
	{
		printf_s("\nKoniec zegnaj");
	}
	
}
int main()
{
	srand(time(0));
	int battlefield[10][10];
	int counter=10;
	menu(battlefield,counter);

}
