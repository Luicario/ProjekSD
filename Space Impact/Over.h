#pragma once
#define MAX_NUMBER_OF_ITEMS 3
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Over {
protected:
	bool overStatus = false;
	RectangleShape background;
	RectangleShape container;
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
	Text GameOver;
public:
	Over(RenderWindow* window);
	
	void render(RenderTarget* target);
	void OverState();
	void UnoverState();

	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	bool over();

	virtual ~Over();
	void update();
};
