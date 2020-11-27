#include "Menu.h"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("Fonts/Vampire_Wars.ttf")) {
		//handle error
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		menu[i].setFont(font);
	
	menu[0].setFillColor(Color::Red);		menu[1].setFillColor(Color::White);		menu[2].setFillColor(Color::White);		menu[3].setFillColor(Color::White);
	menu[0].setString("Play");				menu[1].setString("How To Play");		menu[2].setString("Load Last Saved");	menu[3].setString("Quit");
	menu[0].setCharacterSize(50);			menu[1].setCharacterSize(50);			menu[2].setCharacterSize(50);			menu[3].setCharacterSize(50);

	menu[0].setPosition(Vector2f(width / 2 - 77, height / (MAX_NUMBER_OF_ITEMS + 1) * 1 + 270));
	menu[1].setPosition(Vector2f(width / 2 - 175, height / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 190));
	menu[2].setPosition(Vector2f(width / 2 - 200, height / (MAX_NUMBER_OF_ITEMS + 1) * 3 + 110));
	menu[3].setPosition(Vector2f(width / 2 - 65, height / (MAX_NUMBER_OF_ITEMS + 1) * 4 + 35));

	selectedItemIndex = 0;
}

void Menu::draw(RenderWindow * window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window->draw(menu[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

int Menu::GetPressedItem(){		return selectedItemIndex;	}
Menu::~Menu() {}