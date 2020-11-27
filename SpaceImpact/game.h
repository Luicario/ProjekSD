#pragma once

#include <vector>
#include "gameobjects.h"

using namespace std;

class CGame
{
protected:
	int Score;
	int Life;

	CBullet* bullets[100];
	int bullet_count;

	vector<CBasicEnemy*> enemies;
	// bullet menggunakan array dan enemy menggunakan vevtor untuk membeikan contoh penggunaan masing2 struktur data
	// sebagai penyimpanan objek dalam game. Sebenarnya ada banyak cara, jadi jangan terpaku contoh

	CPesawat *player;

	bool over, exit;

	int LastFrameTime;

	float SpawnTimer;
public:
	CGame();
	void Initialize();
	void ClearScreen();
	void Draw();
	void Update(float elapsed);
	void ProcessInput();
	void Run();
	void SpawnBullet(float x, float y);
	void SpawnEnemy(EnemyType type, int hp, float x, float y);
	CPesawat* GetPlayer();
};