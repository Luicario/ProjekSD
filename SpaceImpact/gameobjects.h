#pragma once

class CGame;

enum State {STATE_INACTIVE, STATE_ACTIVE, STATE_DEADANIMATION};
enum Direction {DIRECTION_RIGHT, DIRECTION_LEFT, DIRECTION_UP, DIRECTION_DOWN};
enum EnemyType {BASIC_ENEMY, ZIGZAG_ENEMY, SEEKER_ENEMY, SHIELD_ENEMY};

#define PLAYER_SPEED 15.0f
#define BULLET_SPEED 50.0f
#define ENEMY_SPEED 15.0f
#define SEEKER_SPEED 25.0f
#define SWITCH_TIMER 0.75f

void gotoxy(int x, int y);

class CObject
{
protected:
	float X, Y, DX, DY;
	int state;
	CGame *world;
public:
	CObject(CGame *w, float x=0.0f, float y=0.0f, float dx=0.0f, float dy=0.0f);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	void SetDX(float dx);
	void SetDY(float dy);
	float GetDX();
	float GetDY();
	void SetState(State s);
	int GetState();
	virtual float GetLeft();
	virtual float GetRight();
	virtual float GetTop();
	virtual float GetBottom();
	virtual void Update(float elapsed);
	virtual void Draw()=0;
	virtual void Erase()=0;
	bool Intersects(CObject *object);
};

class CBullet: public CObject
{
public:
	CBullet(CGame *w, float x=0.0f, float y=0.0f, float dx=0.0f, float dy=0.0f);
	void Draw();
	void Erase();
	void Update(float elapsed);
};

class CPesawat: public CObject
{
protected:
	int counter_die_anim;
public:
	CPesawat(CGame *w, float x=0.0f, float y=0.0f, float dx=0.0f, float dy=0.0f);
	void Move(Direction d, float speed = 1.0f);
	void Die();
	void Draw();
	void Erase();
	void Update(float elapsed);
	float GetRight();
	float GetBottom();
};

class CBasicEnemy: public CPesawat
{
protected:
	int HP;
public:
	CBasicEnemy(CGame *w, int hp = 1, float x=0.0f, float y=0.0f, float dx=-ENEMY_SPEED, float dy=0.0f);
	void SetHP(int hp);
	int GetHP();
	virtual void GetHit(int damage);
	void Draw();
	void Erase();
	void Update(float elapsed);
};

class CZigZagEnemy: public CBasicEnemy
{
protected:
	float Timer_Direction;
public:
	CZigZagEnemy(CGame *w, int hp = 1, float x=0.0f, float y=0.0f, float dx=-ENEMY_SPEED, float dy=0.0f);
	void Draw();
	void Erase();
	void Update(float elapsed);
};

class CSeekerEnemy: public CBasicEnemy
{
public:
	CSeekerEnemy(CGame *w, int hp = 1, float x=0.0f, float y=0.0f, float dx=-SEEKER_SPEED, float dy=0.0f);
	void Draw();
	void Erase();
	void Update(float elapsed);
};

class CShieldEnemy: public CBasicEnemy
{
protected:
	bool Shield;
	float Timer_Shield;
public:
	CShieldEnemy(CGame *w, int hp = 1, float x=0.0f, float y=0.0f, float dx=-ENEMY_SPEED, float dy=0.0f);
	void Draw();
	void Erase();
	void Update(float elapsed);
	void GetHit(int damage);
};