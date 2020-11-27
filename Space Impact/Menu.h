#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 4
using namespace std;
using namespace sf;

class Menu {
private:
	int selectedItemIndex;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
public:
	Menu(float width, float height);	
	void draw(RenderWindow* window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	~Menu();
};