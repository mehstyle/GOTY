#include <QCoreApplication>
#include "qstring.h"
#include <string.h>
#include "unit.h"
#include "ctime"
#include <windows.h>
#include <iostream.h>

#define N 7

void Hallo();
int Smash(unit Pole[N][N], const int UserPose[2], unit X_X, int kills);
void MoveMobs(unit Pole[N][N], const int UserPose[2]);
bool MobsATTACK(unit Pole[N][N], const int UserPose[2], unit X_X);
void FieldPrintf(unit Pole[N][N]);
void POTRACHENO();
void congratulation();


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");
	Hallo();
	system("pause");

	//Игрок
	unit user;
	user.Name = 1;
	user.HP = 9000;
	user.Attack = 10;

	//Тонкий моб
	unit monster2;
	monster2.Name = 2;
	monster2.HP = 100;
	monster2.Attack = 10;

	//Моб-танк
	unit monster3;
	monster3.Name = 3;
	monster3.HP = 500;
	monster3.Attack = 5;

	//Труп
	unit X_X;
	X_X.Name = 0;
	X_X.Attack = 0;

	bool flag = false;
	int kills = 0;

	//Инициализация игрового поля и заполнение её случайными мобами
	unit Field[N][N];
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int Rrand = rand()% 2+2;
			Field[i][j].Name = Rrand;
			if (Field[i][j].Name == 2)
			{
				Field[i][j] = monster2;
			}
			if (Field[i][j].Name == 3)
			{
				Field[i][j] = monster3;
			}
		}
	}

	//Координаты появления игрока
	user.X = 3;
	user.Y = 3;
	int Crdnt[2];
	Crdnt[0] = 3;
	Crdnt[1] = 3;
	Field[user.Y][user.X] = user;
	int time = 50;
	do
	{
		system("cls");
		FieldPrintf(Field);
		printf("---------------Razdelitel, karoch---------------\n");
		kills = Smash(Field, Crdnt, X_X, kills);
		flag = MobsATTACK(Field, Crdnt, X_X);
		MoveMobs(Field, Crdnt);
		Sleep(time);
	}while( (flag != true) && (kills != (N*N - 1)));

	if(kills == (N*N - 1))
	{
		congratulation();
	}
	system("pause");
	system("cls");
	return a.exec();
}

//Вывод игрового поля в консоль
void FieldPrintf(unit Pole[N][N])
{
	for(int i = 0; i<N; i++)
	{
		for(int j = 0; j<N; j++)
		{
			printf("%d ", Pole[i][j].Name);
			if (j == N-1){printf("\n");}
		}
	}

}

//Игрок наносит удары мечём вокруг себя
int Smash(unit Pole[N][N], const int UserPose[2], unit X_X, int kills)
{
	int crit = 1;

	int Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]-1][UserPose[1]-1].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]-1][UserPose[1]].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]-1][UserPose[1]+1].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]+1][UserPose[1]-1].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]+1][UserPose[1]].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]+1][UserPose[1]+1].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;

	Pole[UserPose[0]][UserPose[1]-1].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]+1].HP -= Pole[UserPose[0]][UserPose[1]].Attack;
	crit = 1;

	for(int i = UserPose[0] - 1; i <= UserPose[0] + 1; i++)
	{
		for(int j = UserPose[1] - 1; j <= UserPose[1] + 1; j++)
		{
			if(Pole[i][j].HP <= 0)
			{
				Pole[i][j] = X_X;
				kills++;
			}
		}
	}
	FieldPrintf(Pole);
	printf("---------------Razdelitel, karoch---------------\n");
	return kills;
}

//Мобы занимают освободившиеся вокруг игрока клетки
void MoveMobs(unit Pole[N][N], const int UserPose[2])
{
	unit copy;

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			//Координаты не совпадают с координатами игрока
			if( (i != UserPose[0]) || (j != UserPose[1]) )
			{
				//выше и правее
				if( (i >= UserPose[0] + 1) && (j <= UserPose[1] - 1) )
				{
					if(Pole[i][j + 1].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i][j + 1];
						Pole[i][j + 1] = copy;
					}
				}

				//Выше и левее
				if( (i <= UserPose[0] - 1) && (j <= UserPose[1] - 1) )
				{
					if(Pole[i + 1][j].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i + 1][j];
						Pole[i + 1][j] = copy;
					}
				}

				//Ниже и правее
				if( (i >= UserPose[0] + 1) && (j >= UserPose[1] + 1) )
				{
					if(Pole[i - 1][j].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i - 1][j];
						Pole[i - 1][j] = copy;
					}
				}

				//Ниже и левее
				if( (i <= UserPose[0] - 1) && (j >= UserPose[1] + 1) )
				{
					if(Pole[i][j - 1].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i][j - 1];
						Pole[i][j - 1] = copy;
					}
				}

				//Выше
				if( (i >= UserPose[0] - 1) && ((i <= UserPose[0] + 1)) && (j <= UserPose[1]) )
				{
					if(Pole[i][j + 1].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i][j + 1];
						Pole[i][j + 1] = copy;
					}
				}

				//Правее
				if( (i >= UserPose[0]) && (j >= UserPose[1] - 1 ) &&(j <= UserPose[1] + 1) )
				{
					if(Pole[i - 1][j].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i - 1][j];
						Pole[i - 1][j] = copy;
					}
				}

				//Ниже
				if( (i >= UserPose[0] - 1) && ((i <= UserPose[0] + 1)) && (j >= UserPose[1]) )
				{
					if(Pole[i][j - 1].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i][j - 1];
						Pole[i][j - 1] = copy;
					}
				}

				//Левее
				if( (i <= UserPose[0]) && (j >= UserPose[1] - 1 ) &&(j <= UserPose[1] + 1) )
				{
					if(Pole[i + 1][j].Name == 0)
					{
						copy = Pole[i][j];
						Pole[i][j] = Pole[i + 1][j];
						Pole[i + 1][j] = copy;
					}
				}

			}
		}
	}

	FieldPrintf(Pole);
	printf("---------------Razdelitel, karoch---------------\n");
}

//Мобы атакуют игрока
bool MobsATTACK(unit Pole[N][N], const int UserPose[2], unit X_X)
{
	bool flag = false;
	int crit = 1;

	int Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]-1][UserPose[1]-1].Attack * crit;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]-1][UserPose[1]].Attack * crit;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]-1][UserPose[1]+1].Attack * crit;
	crit = 1;


	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]+1][UserPose[1]-1].Attack * crit;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]+1][UserPose[1]].Attack * crit;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]+1][UserPose[1]+1].Attack * crit;
	crit = 1;


	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]][UserPose[1]-1].Attack * crit;
	crit = 1;

	Rand = rand()% 10;
	if(Rand == 3)
		crit = 2;
	Pole[UserPose[0]][UserPose[1]].HP -= Pole[UserPose[0]][UserPose[1]+1].Attack * crit;
	crit = 1;

	if(Pole[UserPose[0]][UserPose[1]].HP <= 0)
	{
		flag = true;
		Pole[UserPose[0]][UserPose[1]] = X_X;
		FieldPrintf(Pole);
		printf("---------------Razdelitel, karoch---------------\n");
		POTRACHENO();

		return flag;

	}
	if(flag == false)
	{
		FieldPrintf(Pole);
		printf("---------------Razdelitel, karoch---------------\n");
	}
	printf("                                        Ticushee HP geroja, karochi %d\n", Pole[UserPose[0]][UserPose[1]].HP);
	return flag;
}

//Done
void POTRACHENO()
{
	printf("!!!!!!!    !!!!    !!!!!!!!  !!!!!!     !!!    !!    !!  !!!!!!  !!    !!    !!!!\n");
	printf("!!   !!  !!    !!     !!     !!   !!   !! !!   !!    !!  !!      !!    !!  !!    !!\n");
	printf("!!   !!  !!    !!     !!     !!!!!!   !!   !!  !!    !!  !!      !!    !!  !!    !!\n");
	printf("!!   !!  !!    !!     !!     !!       !!!!!!!    !!!!!!  !!!!!!  !!!!!!!!  !!    !!\n");
	printf("!!   !!  !!    !!     !!     !!       !!   !!        !!  !!      !!    !!  !!    !!\n");
	printf("!!   !!    !!!!       !!     !!       !!   !!        !!  !!!!!!  !!    !!    !!!!\n");
	printf("\n");
	printf("\n");
	printf("          \\ /     \\ /\n");
	printf("           X       X\n");
	printf("          / \\     / \\\n");
	printf("\n");
	printf("              @@@\n");
	printf("           @@     @@\n");
	printf("         @@         @@\n");
	printf("---------------Razdelitel, karoch---------------\n");
}

void congratulation()
{
	printf("XXX   X   X  X   X   XXXXX  X    X  XXXX   X   X\n");
	printf("X  X  X  XX  X   X     X     X   X  X   X  X  XX\n");
	printf("XXX   X X X  X   X     X      XXXX  XXXX   X X X\n");
	printf("X  X  XX  X  XXXXXX    X        X   X      XX  X\n");
	printf("XXX   X   X       X    X      XX    X      X   X\n");
}

void Hallo()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int time = 50;
	char str1[150] = "Он был обычным копом в Нью-Йоркской полиции, когда его пёсика задавил фургончик с мороженным.";
	char str2[150] = "Проведя доскональное расследование он выяснил, что за этим стоит картель афганских монстров-мафиози.";
	char str3[150] = "Путём подкупа, шантажа и прочих гнусных приёмов он выяснил где находится их логово.";
	char str4[150] = "И вот он, хорошенько подготовившись и наточив свою меч,";
	char str5[150] = "стоит перед входом в этот рассадник зла, подлости и безумия, осталось сделать только один шаг...\n";
	char str6[150] = "\nНачнем нашу игру?\n\n";
	for (unsigned int i=0; i< 93; i++)
	{
		Sleep(time);
		cout<<str1[i];
	}
	cout<<endl;

	for (unsigned int i=0; i< 100; i++)
	{
		Sleep(time);
		cout<<str2[i];
	}
	cout<<endl;

	for (unsigned int i=0; i< 83; i++)
	{
		Sleep(time);
		cout<<str3[i];
	}
	cout<<endl;


	for (unsigned int i=0; i< 55; i++)
	{
		Sleep(time);
		cout<<str4[i];
	}
	cout<<endl;

	for (unsigned int i=0; i< 97; i++)
	{
		Sleep(time);
		cout<<str5[i];
	}
	cout<<endl;

	for (unsigned int i=0; i< 19; i++)
	{
		Sleep(time);
		cout<<str6[i];
	}
	cout<<endl;

	printf("\n");
}
