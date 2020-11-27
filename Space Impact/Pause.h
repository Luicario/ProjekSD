#pragma once
#define MAX_NUMBER_OF_ITEMS 4
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Pause {
protected:
	bool pausedStatus = false;
	RectangleShape background;
	RectangleShape container;
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
	Text textpause;
public:
	Pause(RenderWindow* window);
	virtual ~Pause();
	void update();
	void render(RenderTarget* target);
	void pauseState();
	void unpauseState();
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	bool paused();
};