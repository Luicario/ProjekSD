#include "game.h"
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

using namespace std;

void HideCursor() { // Hides the cursor
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
}

game::game()
{
	bullet_count = 0;
	player = NULL;
	exit = false;
}
void game::Initialize()
{
	for (int i = 0; i < bullet_count; i++)
		delete bullets[i];

	bullet_count = 0;
	
	// cara loop semua elemen di linked list menggunakan iterator //

	for (list<CBasicEnemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
		delete* i;
	enemies.clear();

	Score = 0;
	Life = 3;
	over = false;
	exit = false;
	SpawnTimer = 2.0f;

	if (player)
	{
		delete player;
	}
	player = new CPesawat(this, 37.0f, 25.0f);
	LastFrameTime = GetTickCount64();
	arena.create_map(28, 81);

	for (int i = 0; i < 3; i++)
	{
		coba.push(new Node(rand() % 3));
		coba.push(new Node(rand() % 73 + 1));
	}

}

void game::ClearScreen()
{
	player->Erase();
	for (int i = 0; i < bullet_count; i++)
		bullets[i]->Erase();
		
	for (list<CBasicEnemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		CBasicEnemy* enemy = *i;
		enemy->Erase();
	}
}

void game::Draw()
{
	player->Draw();

	for (list<CBasicEnemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		CBasicEnemy* enemy = *i;
		enemy->Draw();
	}

	for (int i = 0; i < bullet_count; i++)
		bullets[i]->Draw();

	gotoxy(0, 0);
	cout << "Score: " << Score << ", Life: " << Life;

	if (over)
	{
		GameOver();
	}
}

void game::Update(float elapsed)
{
	if (over)
	{
		return;
	}

	player->Update(elapsed);

	for (int i = 0; i < bullet_count; )
	{
		bullets[i]->Update(elapsed);
		if (bullets[i]->GetState() == STATE_INACTIVE)
		{
			delete bullets[i];
			bullets[i] = bullets[bullet_count - 1];
			--bullet_count;
		}
		else
			i++;
	}


	SpawnTimer -= elapsed;
	{
		if (SpawnTimer <= 0.0f)
		{
			coba.push(new Node(rand() % 3));
			coba.push(new Node(rand() % 73 + 1));

			int rng1,rng2;
			rng1 = coba.pop();
			rng2 = coba.pop();
			this->SpawnEnemy((EnemyType)(rng1), 1, (float)(rng2), 2.0f);

			coba.push(new Node(rand() % 3));
			coba.push(new Node(rand() % 73 + 1));

			rng1 = coba.pop();
			rng2 = coba.pop();
			this->SpawnEnemy((EnemyType)(rng1), 1, (float)(rng2), 2.0f);

			SpawnTimer = 2.0f;
			count++;
			if (count % 2 == 0)
			{
				coba.push(new Node(rand() % 3));
				coba.push(new Node(rand() % 73 + 1));

				rng1 = coba.pop();
				rng2 = coba.pop();
				this->SpawnEnemy((EnemyType)(rng1), 1, (float)(rng2), 2.0f);
			}
			if (count % 10 == 0)
			{
				count = 0;

				coba.push(new Node(rand() % 3));
				coba.push(new Node(rand() % 73 + 1));

				rng1 = coba.pop() % 2 + 3;
				rng2 = coba.pop();

				this->SpawnEnemy((EnemyType)(rng1), 5, (float)(rng2), 4.0f);

			}
		}
	}

	//collision player sama musuh
	for (list<CBasicEnemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		CBasicEnemy* enemy = *i;
		if (enemy->GetState() == STATE_ACTIVE && player->Intersects(enemy))
		{
			delete enemy;
			i = enemies.erase(i);
			this->Life--;
		}
	}

	//musuh nya sampe bawah atau ditembak
	for (list<CBasicEnemy*>::iterator i = enemies.begin(); i != enemies.end(); )
	{
		CBasicEnemy* enemy = *i;
		enemy->Update(elapsed);

		if (enemy->GetTop() >= 27.0f && enemy->GetType() != BOX)
		{
			this->Life--;
		}

		if (enemy->GetState() == STATE_INACTIVE || enemy->GetTop() >= 27.0f)
		{
			delete enemy;
			i = enemies.erase(i);	// fungsi erase akan menghapus sebuah elemen di linked list kemudian return
		}
		else i++;
	}


	//collision peluru sama musuh
	for (int i = 0; i < bullet_count; i++)
	{
		if (!bullets[i]->GetState() == STATE_ACTIVE) continue;
		for (list<CBasicEnemy*>::iterator e = enemies.begin(); e != enemies.end(); e++)
		{
			CBasicEnemy* enemy = *e;
			if (enemy->GetState() == STATE_ACTIVE && bullets[i]->Intersects(enemy) && (enemy->GetType() != BOX && enemy->GetType() != BOMB))
			{
				enemy->GetHit(1);
				if (enemy->GetHP() <= 0)
					this->Score++;

				if (this->Score % (phase * phase * 10) == 0)
				{
					this->Life++;
					this->phase++;
				}
				bullets[i]->SetState(STATE_INACTIVE);
				break;
			}

			if (enemy->GetState() == STATE_ACTIVE && bullets[i]->Intersects(enemy) && enemy->GetType() == BOX)
			{
				enemy->GetHit(1);
				if (enemy->GetHP() <= 0)
					this->Life++;

				bullets[i]->SetState(STATE_INACTIVE);
				break;
			}

			if (enemy->GetState() == STATE_ACTIVE && bullets[i]->Intersects(enemy) && enemy->GetType() == BOMB)
			{

				enemy->GetHit(1);
				if (enemy->GetHP() <= 0)
				{
					this->Score += 10;
					coba.reset();
					for (int i = 0; i < 3; i++)
					{
						coba.push(new Node(rand() % 3));
						coba.push(new Node(rand() % 73 + 1));
					}

					for (list<CBasicEnemy*>::iterator i = enemies.begin(); i != enemies.end(); )
					{
						CBasicEnemy* enemy = *i;
						delete enemy;
						i = enemies.erase(i);
					}

				}
				SpawnTimer = 2.0f;
				bullets[i]->SetState(STATE_INACTIVE);
				break;
			}

		}
	}

	if (this->Life <= 0)
		this->over = true;
}

void game::ProcessInput()
{
	if (_kbhit())
	{
		char key = _getch();
		if (player && !over)
		{
			if (key == 'D' || key == 'd')
				player->Move(DIRECTION_RIGHT, PLAYER_SPEED);
			else if (key == 'A' || key == 'a')
				player->Move(DIRECTION_LEFT, PLAYER_SPEED);
			else if (key == 'S' || key == 's')
				player->Move(STOP, PLAYER_SPEED);
		}

		if (key == 32 && !over)
		{
			this->SpawnBullet(player->GetRight() + 2.0f, player->GetTop() + 3.0f);
		}

		else if (key == 27)
		{
			this->exit = true;
			this->over = true;
		}
	}
}

void game::SpawnBullet(float x, float y)
{
	if (bullet_count >= 100) return;
	Bullet* newbullet = new Bullet(this, x, y, 0, -1.0f * BULLET_SPEED);
	bullets[bullet_count] = newbullet;
	++bullet_count;
}

void game::SpawnEnemy(EnemyType type, int hp, float x, float y)
{
	CBasicEnemy* newenemy = NULL;
	if (type == BASIC_ENEMY)
		newenemy = new CBasicEnemy(this, hp, x, y);
	else if (type == ZIGZAG_ENEMY)
		newenemy = new CZigZagEnemy(this, hp, x, y);
	else if (type == SEEKER_ENEMY)
		newenemy = new CSeekerEnemy(this, hp, x, y);
	else if (type == BOX)
		newenemy = new CHealthBox(this, hp, x, y);
	else if (type == BOMB)
		newenemy = new CBomb(this, hp, x, y);

	if (newenemy)
		enemies.push_back(newenemy);
}

void game :: WelcomeMessage() {
	int x = 13;
	int y = 6;
	gotoxy(x, y);		cout << " _____ _____ _____ _____ _____    _____ _____ _____ _____ ____  _____ _____	";
	gotoxy(x, y + 1);	cout << "|   __|  _  |  _  |     |   __|  |     |   | |  |  |  _  |    \\|   __| __  |	";
	gotoxy(x, y + 2);	cout << "|__   |   __|     |   --|   __|  |-   -| | | |  |  |     |  |  |   __|    -|	";
	gotoxy(x, y + 3);	cout << "|_____|__|  |__|__|_____|_____|  |_____|_|___|\\___/|__|__|____/|_____|__|__|	";
	gotoxy(x, y + 6);	cout << "				Press any key to play";
	gotoxy(x, y + 7);	cout << "			developed by OUR KELOMPOK. - 2020";
	gotoxy(x, y + 9);	cout << "		  C14190189 / Iverson Auldrych Given Krysthio";
	gotoxy(x, y + 10);	cout << "		  C14190196 / Louis Margatan Subekti";
	gotoxy(x, y + 11);	cout << "		  C14190201 / George Kim Anderson Kurniawan Putra	";
	_getch();
	system("cls");
}

void game::GameOver() {
	int x = 13;
	int y = 6;
	system("cls");
	gotoxy(x, y);		cout << " _______  _______  __   __  _______    _______  __   __  _______  ______   ";
	gotoxy(x, y + 1);	cout << "|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  ";
	gotoxy(x, y + 2);	cout << "|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  ";
	gotoxy(x, y + 3);	cout << "|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ ";
	gotoxy(x, y + 4);	cout << "|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |";
	gotoxy(x, y + 5);	cout << "|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |";
	gotoxy(x, y + 6);	cout << "|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|";
	gotoxy(x, y + 10);	cout << "				Press Any Key to Continue...";
	gotoxy(x, y + 11);	cout << "				THANK YOU FOR PLAYING     	";
	_getch();

}

void game::Run()
{
	while (!exit && !over)
	{
		HideCursor();
		// menghitung jeda waktu antar frame
		int CurrentTime = GetTickCount64();
		int elapsedInt = CurrentTime - LastFrameTime;
		LastFrameTime = CurrentTime;
		float elapsedFloat = (float)elapsedInt / 1000.0f;

		this->ClearScreen();
		this->ProcessInput();

		// update setiap objek berdasarkan jeda waktu 
		//contoh: objek dengan kecepatan 100 pixel per detik hanya bergerak sebanyak 10 pixel jika jeda waktunya 0.1 detik
		this->Update(elapsedFloat);
		this->Draw();

		Sleep(30);
	}
}

CPesawat* game::GetPlayer()
{
	return player;
}