#pragma once

#include "object.h"
#include <list>
using namespace std;

void HideCursor();

class game
{
protected:
	int Score;
	int Life;
	map arena;
	Bullet* bullets[100];
	int bullet_count;

	list<CBasicEnemy*> enemies;

	// bullet menggunakan array dan enemy menggunakan vevtor untuk membeikan contoh penggunaan masing2 struktur data //

	CPesawat* player;

	bool over, exit, start = false;

	int LastFrameTime;

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
	CPesawat* GetPlayer();
};

