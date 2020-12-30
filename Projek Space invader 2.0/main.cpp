#include "game.h"
#include<time.h>

void main()
{
	srand((unsigned)time(NULL));
	game game;
	game.WelcomeMessage();
	game.Initialize();
	game.Run();
}