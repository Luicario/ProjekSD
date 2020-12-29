#include "object.h"
#include "game.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>


using namespace std;

void gotoxy(int x, int y)
{							//function gerak char
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = x;     // defining x-axis
	coordinates.Y = y;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

map::map()
{

}

void map::create_map(int x, int y)
{
	for (int i = 1; i < x; i++) 
	{
		for (int j = 0; j < y; j++) 
		{
			if (i == 1) 
			{
				gotoxy(j, i);
				cout << "=";
			}
			else if (i == x - 1) 
			{
				gotoxy(j, i);
				cout << "=";
			}
			else if (i > 0 && i != x - 1 && j == 0) 
			{
				gotoxy(j, i);
				cout << "|";
			}
			else if (i > 0 && j <= y - 2) 
			{

			}
			else if (i > 0 && i != x - 1 && j <= y - 1) 
			{
				gotoxy(j, i);
				cout << "|";
			}
		}
		cout << endl;
	}
}

object::object(game* w, float x, float y, float dx, float dy)
{
	world = w;
	X = x;
	Y = y;
	DX = dx;
	DY = dy;
	state = STATE_ACTIVE;
}

void object::SetX(float x)
{
	X = x;
}

void object::SetY(float y)
{
	Y = y;
}
float object::GetX()
{
	return X;
}
float object::GetY()
{
	return Y;
}
void object::SetDX(float dx)
{
	DX = dx;
}
void object::SetDY(float dy)
{
	DY = dy;
}
float object::GetDX()
{
	return DX;
}
float object::GetDY()
{
	return DY;
}
void object::SetState(State s)
{
	state = s;
}
int object::GetState()
{
	return state;
}
float object::GetLeft()
{
	return X;
}
float object::GetRight()
{
	return X;
}
float object::GetTop()
{
	return Y;
}
float object::GetBottom()
{
	return Y;
}
void object::Update(float elapsed)
{
	if (state == STATE_ACTIVE)
	{
		X += DX * elapsed;
		Y += DY * elapsed;
	}
}
bool object::Intersects(object* object)
{
	return !(this->GetRight() + 4.0f < object->GetLeft() || this->GetLeft() -1.0f > object->GetRight() + 4.0f ||
		this->GetTop() > object->GetBottom()
		);
}

CPesawat::CPesawat(game* w, float x, float y, float dx, float dy) : object(w, x, y, dx, dy)
{
	counter_die_anim = 0;
}

void CPesawat::Move(Direction d, float speed)
{
	if (d == DIRECTION_RIGHT)
	{
		DX = speed;
		DY = 0.0f;
	}
	else if (d == DIRECTION_LEFT)
	{
		DX = -speed;
		DY = 0.0f;
	}
	else if (d == STOP)
	{
		DX = 0.0f;
		DY = 0.0f;
	}
}
void CPesawat::Die()
{
	state = STATE_DEADANIMATION;
	counter_die_anim = 0;
}
void CPesawat::Draw()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim == 1)
	{
		gotoxy((int)X, (int)Y); cout << "  -  ";
		gotoxy((int)X, (int)Y + 1); cout << ">=|=<";
	}
}
void CPesawat::Erase()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim == 1)
	{
		gotoxy((int)X, (int)Y); cout << "     ";
		gotoxy((int)X, (int)Y + 1); cout << "     ";
	}
}
void CPesawat::Update(float elapsed)
{
	if (state == STATE_ACTIVE)
	{
		object::Update(elapsed);
		if (DX > 0.0f && this->GetRight() >= 75.0f)
		{
			DX = 0.0f;
			X = 75.0f;
		}
		else if (DX < 0.0f && this->GetLeft() <= 1.0f)
		{
			DX = 0.0f;
			X = 1.0f;
		}
	}
	else if (state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if (counter_die_anim > 20)
			state = STATE_INACTIVE;
	}
}
float CPesawat::GetRight()
{
	return X;
}
float CPesawat::GetBottom()
{
	return Y;
}

Bullet::Bullet(game* w, float x, float y, float dx, float dy) :object(w, x, y, dx, dy)
{

}

bool Bullet::Intersects(object* object)
{
	return !(this->GetRight() < object->GetLeft() || this->GetLeft() > object->GetRight() + 5.0f ||
		this->GetTop() > object->GetBottom() || this->GetTop() > object->GetBottom()
		);
}

void Bullet::Draw()
{
	gotoxy((int)X, (int)Y);
	cout << "^";
}
void Bullet::Erase()
{
	gotoxy((int)X, (int)Y);
	cout << " ";
}
void Bullet::Update(float elapsed)
{
	object::Update(elapsed);
	if (X > 80.0f || X < 1.0f || Y < 2.0f)
	{
		state = STATE_INACTIVE;
	}
}

CBasicEnemy::CBasicEnemy(game* w, int hp, float x, float y, float dx, float dy) :CPesawat(w, x, y, dx, dy)
{
	HP = hp;
}
void CBasicEnemy::SetHP(int hp)
{
	HP = hp;
}
int CBasicEnemy::GetHP()
{
	return HP;
}
void CBasicEnemy::GetHit(int damage)
{
	HP -= damage;
	if (HP <= 0)
	{
		HP = 0;
		state = STATE_DEADANIMATION;
	}
}
void CBasicEnemy::Draw()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim % 2 == 1)
	{
		gotoxy((int)X, (int)Y);
		cout << "|=O=|";
	}
}
void CBasicEnemy::Erase()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION)
	{
		gotoxy((int)X, (int)Y);			
		cout << "     ";
	}
}
void CBasicEnemy::Update(float elapsed)
{
	if (state == STATE_ACTIVE)
	{
		object::Update(elapsed);
	}
	else if (state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if (counter_die_anim > 10)
			state = STATE_INACTIVE;
	}
}

CZigZagEnemy::CZigZagEnemy(game* w, int hp, float x, float y, float dx, float dy) :CBasicEnemy(w, hp, x, y, dx, dy)
{
	Timer_Direction = SWITCH_TIMER;
}
void CZigZagEnemy::Draw()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim % 2 == 1)
	{
		gotoxy((int)X, (int)Y);			
		cout << ">>0<<";
	}
}
void CZigZagEnemy::Erase()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION)
	{
		gotoxy((int)X, (int)Y);			
		cout << "     ";
	}
}
void CZigZagEnemy::Update(float elapsed)
{
	if (state == STATE_ACTIVE)
	{
		if (DX == 0.0f)
		{
			DX = rand() % 2 == 0 ? ZIGZAG_SPEED : -ZIGZAG_SPEED;
			Timer_Direction = SWITCH_TIMER;
		}

		if (this->GetLeft() <= 1.0f)
		{
			this->SetX(0.0f);
			this->SetDX(ZIGZAG_SPEED);
			Timer_Direction = SWITCH_TIMER;
		}
		else if (this->GetRight() + 5.0f >= 75.0f)
		{
			this->SetX(80.0f);
			this->SetDX(-ZIGZAG_SPEED);
			Timer_Direction = SWITCH_TIMER;
		}
		else
		{
			Timer_Direction -= elapsed;
			if (Timer_Direction <= -1.0f)
			{
				Timer_Direction = SWITCH_TIMER;
				DX = -DX;
			}
		}

		object::Update(elapsed);
	}
	else if (state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if (counter_die_anim > 10)
			state = STATE_INACTIVE;
	}
}

CSeekerEnemy::CSeekerEnemy(game* w, int hp, float x, float y, float dx, float dy) :CBasicEnemy(w, hp, x, y, dx, dy)
{

}
void CSeekerEnemy::Draw()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim % 2 == 1)
	{
		gotoxy((int)X, (int)Y);			
		cout << "D=8=D";
	}
}
void CSeekerEnemy::Erase()
{
	if (state == STATE_ACTIVE || state == STATE_DEADANIMATION)
	{
		gotoxy((int)X, (int)Y);			
		cout << "       ";
	}
}
void CSeekerEnemy::Update(float elapsed)
{
	if (state == STATE_ACTIVE)
	{
		CPesawat* player = world->GetPlayer();

		if (this->X < player->GetX())
		{
			if (player->GetX() - this->X <= 1.5f)
				this->DX = 0.0f;
			else
				this->DX = 8.0f;
		}
		else if (this->X > player->GetX())
		{
			if (this->X - player->GetX() <= 1.5f)
				this->DX = 0.0f;
			else
				this->DX = -8.0f;
		}

		object::Update(elapsed);
	}
	else if (state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if (counter_die_anim > 10)
			state = STATE_INACTIVE;
	}
}