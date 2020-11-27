#include "game.h"
#include<time.h>

void main()
{
	srand((unsigned)time(NULL));
	CGame game;
	game.Initialize();
	game.Run();
}