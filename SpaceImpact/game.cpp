#include "game.h"
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

using namespace std;

CGame::CGame()
{
	bullet_count = 0;
	player = NULL;
	exit = false;
}
void CGame::Initialize()
{
	for(int i=0;i<bullet_count;i++)
		delete bullets[i];
	bullet_count = 0;

	// cara loop semua elemen di vector dengan iterator
	for(vector<CBasicEnemy*>::iterator i = enemies.begin(); i!= enemies.end(); i++)
		delete *i;
	enemies.clear();

	Score = 0;
	Life = 3;
	over = false;
	exit = false;
	SpawnTimer = 2.0f;

	if(player) delete player;
	player = new CPesawat(this, 1.0f, 10.0f);

	LastFrameTime = GetTickCount();
}
void CGame::ClearScreen()
{
	player->Erase();

	for(vector<CBasicEnemy*>::iterator i = enemies.begin(); i!= enemies.end(); i++)
	{
		CBasicEnemy *enemy = *i;
		enemy->Erase();
	}

	for(int i=0;i<bullet_count;i++)
		bullets[i]->Erase();
}
void CGame::Draw()
{
	player->Draw();

	for(vector<CBasicEnemy*>::iterator i = enemies.begin(); i!= enemies.end(); i++)
	{
		CBasicEnemy *enemy = *i;
		enemy->Draw();
	}

	for(int i=0;i<bullet_count;i++)
		bullets[i]->Draw();

	gotoxy(0, 0);
	cout<< "Score: " << Score << ", Life: " << Life;
	if(over) cout <<"    GAME OVER!!! Press Esc to exit...";
}
void CGame::Update(float elapsed)
{
	if(over) return;

	SpawnTimer -= elapsed;
	{
		if(SpawnTimer <= 0.0f)
		{
			SpawnTimer = 2.0f;
			this->SpawnEnemy((EnemyType)(rand() % 4), rand() % 5 + 3, 75.0f, (float)(rand()%20) + 1);
		}
	}

	for(vector<CBasicEnemy*>::iterator i = enemies.begin(); i!= enemies.end(); i++)
	{
		CBasicEnemy *enemy = *i;
		if(enemy->GetState() == STATE_ACTIVE && player->Intersects(enemy))
		{
			over = true;
			return;
		}
	}

	player->Update(elapsed);

	//cek bullet tabrak pesawat
	for(int i=0;i<bullet_count;i++)
	{
		if(!bullets[i]->GetState() == STATE_ACTIVE) continue;
		for(vector<CBasicEnemy*>::iterator e = enemies.begin(); e!= enemies.end(); e++)
		{
			CBasicEnemy *enemy = *e;
			if(enemy->GetState() == STATE_ACTIVE && bullets[i]->Intersects(enemy))
			{
				enemy->GetHit(1);
				if(enemy->GetHP() <= 0)
					this->Score++;
				bullets[i]->SetState(STATE_INACTIVE);
				break;
			}
		}
	}


	//update semua bullet, hapus bullet jika sudah tidak aktif
	for(int i=0;i<bullet_count; )
	{
		bullets[i]->Update(elapsed);
		if(bullets[i]->GetState() == STATE_INACTIVE)
		{
			delete bullets[i];
			// bullet elemen terakhir dipindah ke index yg kosong karena dihapus, i tidak perlu ditambah
			bullets[i] = bullets[bullet_count-1];
			-- bullet_count;
		}
		else
			i++;
	}

	for(vector<CBasicEnemy*>::iterator i = enemies.begin(); i!= enemies.end(); )
	{
		CBasicEnemy *enemy = *i;
		enemy->Update(elapsed);

		if(enemy->GetLeft() <= 0.0f)
		{
			this->Life--;
			if(this->Life<=0)
				this->over = true;
		}

		if(enemy->GetState() == STATE_INACTIVE || enemy->GetLeft() <= 0.0f)
		{
			delete enemy;
			i = enemies.erase(i);	// fungsi erase akan menghapus sebuah elemen di vector kemudian return
									// iterator yg menunjuk ke elemen selanjutnya
		}
		else i++;
	}
}
void CGame::ProcessInput()
{
	if(_kbhit())
	{
		char key = _getch();
		if(player && !over)
		{
			if(key == 'D' || key == 'd')
				player->Move(DIRECTION_RIGHT, PLAYER_SPEED);
			else if(key == 'A' || key == 'a')
				player->Move(DIRECTION_LEFT, PLAYER_SPEED);
			else if(key == 'W' || key == 'w')
				player->Move(DIRECTION_UP, PLAYER_SPEED);
			else if(key == 'S' || key == 's')
				player->Move(DIRECTION_DOWN, PLAYER_SPEED);
		}

		if(key == ' ' && !over)
		{
			this->SpawnBullet(player->GetRight(), player->GetTop() + 2.0f);
		}
		else if(key == 27)
		{
			this->exit = true;
		}
	}
}
void CGame::SpawnBullet(float x, float y)
{
	if(bullet_count>=100) return;
	CBullet *newbullet = new CBullet(this, x, y, BULLET_SPEED);
	bullets[bullet_count] = newbullet;
	++bullet_count;
}
void CGame::SpawnEnemy(EnemyType type, int hp, float x, float y)
{
	CBasicEnemy *newenemy = NULL;
	if(type == BASIC_ENEMY)
		newenemy = new CBasicEnemy(this, hp, x, y);
	else if(type == ZIGZAG_ENEMY)
		newenemy = new CZigZagEnemy(this, hp, x, y);
	else if(type == SEEKER_ENEMY)
		newenemy = new CSeekerEnemy(this, hp, x, y);
	else if(type == SHIELD_ENEMY)
		newenemy = new CShieldEnemy(this, hp, x, y);

	if(newenemy)
		enemies.push_back(newenemy);
}
void CGame::Run()
{
	while(!exit)
	{
		// menghitung jeda waktu antar frame
		int CurrentTime = GetTickCount();
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

CPesawat* CGame::GetPlayer()
{
	return player;
}