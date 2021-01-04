#pragma once

#include "object.h"
#include "List.h"
#include <iterator>
#include <vector>
#include <list>
using namespace std;

void HideCursor();

class game
{
protected:
	int Score, Life, bullet_count, LastFrameTime, count = 0, phase = 1;
	map arena;
	Bullet* bullets[100];
	list<CBasicEnemy*> enemies;
	List coba;
	CPesawat* player;
	bool over, exit, start = false;
	float SpawnTimer;

public:
	game();
	void Initialize();
	void ClearScreen();
	void Draw();
	void Update(float elapsed);
	void ProcessInput();
	void Run();
	void SpawnBullet(float x, float y);
	void SpawnEnemy(EnemyType type, int hp, float x, float y);
	void WelcomeMessage();
	void GameOver();
	CPesawat* GetPlayer();
};

