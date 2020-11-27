#include "Over.h"

Over::Over(RenderWindow* window) {
	if (!font.loadFromFile("Fonts/Vampire_Wars.ttf")) {
		//handle error
	}

	this->background.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	this->background.setFillColor(Color(20, 20, 20, 100));
	this->container.setSize(Vector2f(static_cast<float>(window->getSize().x) / 4.f, static_cast<float>(window->getSize().y)));
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window->getSize().x) / 2.f - this->container.getSize().x / 2.f, 0.f);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i].setFont(font);
	}
	GameOver.setFont(font);
	GameOver.setCharacterSize(72);

	menu[0].setFillColor(Color::Red);		menu[1].setFillColor(Color::White);			menu[2].setFillColor(Color::White);
	menu[0].setString("Retry");				menu[1].setString("Exit To Main Menu");		menu[2].setString("Quit");		
	GameOver.setFillColor(Color::Color(178, 102, 255));
	GameOver.setString("GAME OVER");

	GameOver.setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 190.f, static_cast<float>(window->getSize().y) / 6.f - 50.f));
	menu[0].setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 45.f, static_cast<float>(window->getSize().y) / (MAX_NUMBER_OF_ITEMS + 1) * 1 + 80));
	menu[1].setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 125.f, static_cast<float>(window->getSize().y) / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 50));
	menu[2].setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 20.f, static_cast<float>(window->getSize().y) / (MAX_NUMBER_OF_ITEMS + 1) * 3 + 20));

	selectedItemIndex = 0;
}

void Over::render(RenderTarget* target) {
	target->draw(background);
	target->draw(container);
	target->draw(GameOver);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		target->draw(menu[i]);
	}
}

void Over::OverState() {
	this->overStatus = true;
}

void Over::UnoverState() {
	this->overStatus = false;
}

void Over::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void Over::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

Over::~Over() {}
void Over::update() {}

int Over::GetPressedItem(){   return selectedItemIndex;	}
bool Over::over() {  return overStatus;  }