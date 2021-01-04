#pragma once

class game;

enum State { STATE_INACTIVE, STATE_ACTIVE, STATE_DEADANIMATION };
enum Direction { DIRECTION_RIGHT, DIRECTION_LEFT, STOP };
enum EnemyType { BASIC_ENEMY, ZIGZAG_ENEMY, SEEKER_ENEMY, BOX, BOMB};

#define PLAYER_SPEED 20.0f
#define BULLET_SPEED 40.0f
#define ENEMY_SPEED 4.0f
#define ITEM_SPEED 1.0f
#define SEEKER_SPEED 1.5f
#define ZIGZAG_SPEED 2.5f
#define SWITCH_TIMER 1.5f

void gotoxy(int x, int y);

class map
{
public:
	map();
	void create_map(int x, int y);
};

class object
{
protected:
	float X, Y, DX, DY;
	int state;
	game *world;
public:
	object(game* w, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = 0.0f);
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
	virtual void Draw() = 0;
	virtual void Erase() = 0;
	virtual bool Intersects(object* object);
};

class CPesawat : public object
{
protected:
	int counter_die_anim;
public:
	CPesawat(game* w, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = 0.0f);
	void Move(Direction d, float speed = 1.0f);
	void Die();
	void Draw();
	void Erase();
	void Update(float elapsed);
	float GetRight();
	float GetBottom();
};

class Bullet : public object
{
public:
	Bullet(game* w, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = 0.0f);
	void Draw();
	void Erase();
	void Update(float elapsed);
	bool Intersects(object* object);
};

class CBasicEnemy : public CPesawat
{
protected:
	int HP;
	EnemyType tipe;
public:
	CBasicEnemy(game* w, int hp = 1, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = ENEMY_SPEED);
	void SetHP(int hp);
	int GetHP();
	virtual void GetHit(int damage);
	void Draw();
	void Erase();
	void Update(float elapsed);
	virtual EnemyType GetType();
};

class CZigZagEnemy : public CBasicEnemy
{
protected:
	float Timer_Direction;
public:
	CZigZagEnemy(game* w, int hp = 1, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = ZIGZAG_SPEED);
	void Draw();
	void Erase();
	void Update(float elapsed);
	EnemyType GetType();
};

class CSeekerEnemy : public CBasicEnemy
{
public:
	CSeekerEnemy(game* w, int hp = 1, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = SEEKER_SPEED);
	void Draw();
	void Erase();
	void Update(float elapsed);
	EnemyType GetType();
};

class CHealthBox : public CBasicEnemy
{
protected:
public:
	CHealthBox(game* w, int hp = 1, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = ITEM_SPEED);
	void Draw();
	void Erase();
	void Update(float elapsed);
	EnemyType GetType();
};

class CBomb : public CBasicEnemy
{
protected:
public:
	CBomb(game* w, int hp = 5, float x = 0.0f, float y = 0.0f, float dx = 0.0f, float dy = ITEM_SPEED);
	void Draw();
	void Erase();
	void Update(float elapsed);
	EnemyType GetType();
};
