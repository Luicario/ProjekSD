#include "gameobjects.h"
#include "game.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#include <iostream>

using namespace std;

void gotoxy(int x, int y) 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

CObject::CObject(CGame *w, float x, float y, float dx, float dy)
{
	world = w;
	X = x;
	Y = y;
	DX = dx;
	DY = dy;
	state = STATE_ACTIVE;
}
void CObject::SetX(float x)
{
	X = x;
}
void CObject::SetY(float y)
{
	Y=y;
}
float CObject::GetX()
{
	return X;
}
float CObject::GetY()
{
	return Y;
}
void CObject::SetDX(float dx)
{
	DX = dx;
}
void CObject::SetDY(float dy)
{
	DY=dy;
}
float CObject::GetDX()
{
	return DX;
}
float CObject::GetDY()
{
	return DY;
}
void CObject::SetState(State s)
{
	state = s;
}
int CObject::GetState()
{
	return state;
}
float CObject::GetLeft()
{
	return X;
}
float CObject::GetRight()
{
	return X;
}
float CObject::GetTop()
{
	return Y;
}
float CObject::GetBottom()
{
	return Y;
}
void CObject::Update(float elapsed)
{
	if(state == STATE_ACTIVE)
	{
		X += DX * elapsed;
		Y += DY * elapsed;
	}
}
bool CObject::Intersects(CObject *object)
{
	return !(this->GetRight() + 0.5f < object->GetLeft() - 0.5f || this->GetLeft() - 0.5f > object->GetRight() + 0.5f
		|| this->GetBottom() + 0.5f < object->GetTop() - 0.5f || this->GetTop() - 0.5f > object->GetBottom() + 0.5f );
}


CBullet::CBullet(CGame *w, float x, float y, float dx, float dy):CObject(w, x, y, dx, dy)
{

}
void CBullet::Draw()
{
	gotoxy((int)X, (int)Y);
	cout << "-";
}
void CBullet::Erase()
{
	gotoxy((int)X, (int)Y);
	cout << " ";
}
void CBullet::Update(float elapsed)
{
	CObject::Update(elapsed);
	if(X > 79.0f || X < 0.0f || Y < 0.0f || Y > 24.0f)
		state = STATE_INACTIVE;
}

CPesawat::CPesawat(CGame *w, float x, float y, float dx, float dy):CObject(w,x,y,dx,dy)
{
	counter_die_anim = 0;
}
void CPesawat::Move(Direction d, float speed)
{
	if(d == DIRECTION_RIGHT)
	{
		DX = speed;
		DY = 0.0f;
	}
	else if(d == DIRECTION_LEFT)
	{
		DX = -speed;
		DY = 0.0f;
	}
	else if(d == DIRECTION_UP)
	{
		DX = 0.0f;
		DY = -speed;
	}
	else if(d == DIRECTION_DOWN)
	{
		DX = 0.0f;
		DY = speed;
	}
}
void CPesawat::Die()
{
	state = STATE_DEADANIMATION;
	counter_die_anim = 0;
}
void CPesawat::Draw()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim == 1)
	{
		gotoxy((int)X+1, (int)Y);		cout<< "|\\==";
		gotoxy((int)X, (int)Y+1);		cout<<"-| \\";
		gotoxy((int)X, (int)Y+2);		cout<<"-|  )";
		gotoxy((int)X, (int)Y+3);		cout<<"-| /";
		gotoxy((int)X+1, (int)Y+4);		cout<< "|/==";
	}
}
void CPesawat::Erase()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim == 1)
	{
		gotoxy((int)X+1, (int)Y);		cout<< "    ";
		gotoxy((int)X, (int)Y+1);		cout<<"     ";
		gotoxy((int)X, (int)Y+2);		cout<<"     ";
		gotoxy((int)X, (int)Y+3);		cout<<"     ";
		gotoxy((int)X+1, (int)Y+4);		cout<< "    ";
	}
}
void CPesawat::Update(float elapsed)
{
	if(state == STATE_ACTIVE)
	{
		CObject::Update(elapsed);
		if(DX > 0.0f && this->GetRight() >= 79.0f)
		{
			DX = 0.0f;
			X = 75.0f;
		}
		else if(DX < 0.0f && this->GetLeft() <= 0.0f )
		{
			DX = 0.0f;
			X = 0.0f;
		}

		if(DY > 0.0f && this->GetBottom() >= 24.0f)
		{
			DY = 0.0f;
			Y = 20.0f;
		}
		else if(DY < 0.0f && this->GetTop() <= 0.0f )
		{
			DY = 0.0f;
			Y = 0.0f;
		}
	}
	else if(state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if(counter_die_anim > 20)
			state = STATE_INACTIVE;
	}
}
float CPesawat::GetRight()
{
	return X + 4.0f;
}
float CPesawat::GetBottom()
{
	return Y + 4.0f;
}

CBasicEnemy::CBasicEnemy(CGame *w, int hp, float x, float y, float dx, float dy):CPesawat(w,x,y,dx,dy)
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
	if(HP <= 0)
	{
		HP = 0;
		state = STATE_DEADANIMATION;
	}
}
void CBasicEnemy::Draw()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim % 2 == 1)
	{
		gotoxy((int)X, (int)Y);			cout<<"-oooo";
		gotoxy((int)X, (int)Y+1);		cout<<"o   o";
		gotoxy((int)X, (int)Y+2);		cout<<"o "<<HP<<" o";
		gotoxy((int)X, (int)Y+3);		cout<<"o   o";
		gotoxy((int)X, (int)Y+4);		cout<<"-oooo";
	}
}
void CBasicEnemy::Erase()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION)
	{
		gotoxy((int)X, (int)Y);			cout<<"     ";
		gotoxy((int)X, (int)Y+1);		cout<<"     ";
		gotoxy((int)X, (int)Y+2);		cout<<"     ";
		gotoxy((int)X, (int)Y+3);		cout<<"     ";
		gotoxy((int)X, (int)Y+4);		cout<<"     ";
	}
}
void CBasicEnemy::Update(float elapsed)
{
	if(state == STATE_ACTIVE)
	{
		CObject::Update(elapsed);
	}
	else if(state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if(counter_die_anim > 10)
			state = STATE_INACTIVE;
	}
}

CZigZagEnemy::CZigZagEnemy(CGame *w, int hp, float x, float y, float dx, float dy):CBasicEnemy(w,hp,x,y,dx,dy)
{
	Timer_Direction = SWITCH_TIMER;
}
void CZigZagEnemy::Draw()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim % 2 == 1)
	{
		gotoxy((int)X, (int)Y);			cout<<"-----";
		gotoxy((int)X+1, (int)Y+1);		cout<< "/  |";
		gotoxy((int)X, (int)Y+2);		cout<<"{ "<<HP<<" |";
		gotoxy((int)X+1, (int)Y+3);		cout<< "\\  |";
		gotoxy((int)X, (int)Y+4);		cout<<"-----";
	}
}
void CZigZagEnemy::Erase()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION )
	{
		gotoxy((int)X, (int)Y);			cout<<"     ";
		gotoxy((int)X+1, (int)Y+1);		cout<< "    ";
		gotoxy((int)X, (int)Y+2);		cout<<"     ";
		gotoxy((int)X+1, (int)Y+3);		cout<< "    ";
		gotoxy((int)X, (int)Y+4);		cout<<"     ";
	}
}
void CZigZagEnemy::Update(float elapsed)
{
	if(state == STATE_ACTIVE)
	{
		if(DY == 0.0f)
		{
			DY = rand()%2 == 0? ENEMY_SPEED: -ENEMY_SPEED; 
			Timer_Direction = SWITCH_TIMER;
		}
	
		if(this->GetTop() <= 0.0f)
		{
			this->SetY(0.0f);
			this->SetDY(ENEMY_SPEED);
			Timer_Direction = SWITCH_TIMER;
		}
		else if(this->GetBottom() >= 24.0f)
		{
			this->SetY(20.0f);
			this->SetDY(-ENEMY_SPEED);
			Timer_Direction = SWITCH_TIMER;
		}
		else
		{
			Timer_Direction -= elapsed;
			if(Timer_Direction<=0.0f)
			{
				Timer_Direction = SWITCH_TIMER;
				DY = - DY;
			}
		}

		CObject::Update(elapsed);
	}
	else if(state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if(counter_die_anim > 10)
			state = STATE_INACTIVE;
	}
}

CSeekerEnemy::CSeekerEnemy(CGame *w, int hp, float x, float y, float dx, float dy):CBasicEnemy(w,hp,x,y,dx,dy)
{
	
}
void CSeekerEnemy::Draw()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim % 2 == 1)
	{
		gotoxy((int)X, (int)Y);			cout<<"====";
		gotoxy((int)X+1, (int)Y+1);		cout<< "* *";
		gotoxy((int)X, (int)Y+2);		cout<<"* "<<HP<<" *";
		gotoxy((int)X+1, (int)Y+3);		cout<< "* *";
		gotoxy((int)X, (int)Y+4);		cout<<"====";
	}
}
void CSeekerEnemy::Erase()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION)
	{
		gotoxy((int)X, (int)Y);			cout<<"    ";
		gotoxy((int)X+1, (int)Y+1);		cout<< "   ";
		gotoxy((int)X, (int)Y+2);		cout<<"     ";
		gotoxy((int)X+1, (int)Y+3);		cout<< "   ";
		gotoxy((int)X, (int)Y+4);		cout<<"    ";
	}
}
void CSeekerEnemy::Update(float elapsed)
{
	if(state == STATE_ACTIVE)
	{
		CPesawat *player = world->GetPlayer();

		if(this->Y < player->GetY())
		{
			if(player->GetY() - this->Y <= 1.5f)
				this->DY = 0.0f;
			else
				this->DY = 8.0f;
		}
		else if(this->Y > player->GetY())
		{
			if(this->Y - player->GetY() <= 1.5f)
				this->DY = 0.0f;
			else
				this->DY = -8.0f;
		}

		CObject::Update(elapsed);
	}
	else if(state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if(counter_die_anim > 10)
			state = STATE_INACTIVE;
	}
}

CShieldEnemy::CShieldEnemy(CGame *w, int hp, float x, float y, float dx, float dy):CBasicEnemy(w,hp,x,y,dx,dy)
{
	Shield = false;
	Timer_Shield = 2.0f;
}
void CShieldEnemy::Draw()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION && counter_die_anim % 2 == 1)
	{
		gotoxy((int)(Shield?X-1:X), (int)Y);		cout << (Shield?"#":"") << "/===\\";
		gotoxy((int)(Shield?X-1:X), (int)Y+1);		cout << (Shield?"#":"") << "|   |";
		gotoxy((int)(Shield?X-1:X), (int)Y+2);		cout << (Shield?"#":"") << "| "<<HP<<" |";
		gotoxy((int)(Shield?X-1:X), (int)Y+3);		cout << (Shield?"#":"") << "|   |";
		gotoxy((int)(Shield?X-1:X), (int)Y+4);		cout << (Shield?"#":"") << "\\===/";
	}
}
void CShieldEnemy::Erase()
{
	if(state == STATE_ACTIVE || state == STATE_DEADANIMATION)
	{
		gotoxy((int)(Shield?X-1:X), (int)Y);		cout << (Shield?" ":"") << "     ";
		gotoxy((int)(Shield?X-1:X), (int)Y+1);		cout << (Shield?" ":"") << "     ";
		gotoxy((int)(Shield?X-1:X), (int)Y+2);		cout << (Shield?" ":"") << "     ";
		gotoxy((int)(Shield?X-1:X), (int)Y+3);		cout << (Shield?" ":"") << "     ";
		gotoxy((int)(Shield?X-1:X), (int)Y+4);		cout << (Shield?" ":"") << "     ";
	}
}
void CShieldEnemy::Update(float elapsed)
{
	if(state == STATE_ACTIVE)
	{
		if(Shield)
		{
			Timer_Shield-=elapsed;
			if(Timer_Shield<=0.0f)
			{
				Timer_Shield = 2.0f;
				Shield = false;
			}
		}
		else
		{
			CObject::Update(elapsed);
			Timer_Shield-=elapsed;
			if(Timer_Shield<=0.0f)
			{
 				Timer_Shield = 5.0f; 
				Shield = true;
			}
		}
	}
	else if(state == STATE_DEADANIMATION)
	{
		counter_die_anim++;
		if(counter_die_anim > 10)
			state = STATE_INACTIVE;
	}
}

void CShieldEnemy::GetHit(int damage)
{
	if(!Shield)
		CBasicEnemy::GetHit(damage);
}
