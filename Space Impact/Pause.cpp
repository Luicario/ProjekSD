#include "Pause.h"

Pause::Pause(RenderWindow* window){
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
	textpause.setFont(font);
	textpause.setCharacterSize(72);

	menu[0].setFillColor(Color::Red);		menu[1].setFillColor(Color::White);			menu[2].setFillColor(Color::White);		menu[3].setFillColor(Color::White);
	menu[0].setString("Resume");			menu[1].setString("Exit To Main Menu");		menu[2].setString("Save");				menu[3].setString("Quit");
	textpause.setFillColor(Color::Color(178, 102, 255));
	textpause.setString("PAUSED");

	textpause.setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 112.f, static_cast<float>(window->getSize().y) / 8.f - 35.f));
	menu[0].setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 45.f, static_cast<float>(window->getSize().y) / (MAX_NUMBER_OF_ITEMS + 1) * 1 + 50));
	menu[1].setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 115.f, static_cast<float>(window->getSize().y) / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 50));
	menu[2].setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 20.f, static_cast<float>(window->getSize().y) / (MAX_NUMBER_OF_ITEMS + 1) * 3 + 50));
	menu[3].setPosition(Vector2f((static_cast<float>(window->getSize().x) / 2.f) - 20.f, static_cast<float>(window->getSize().y) / (MAX_NUMBER_OF_ITEMS + 1) * 4 + 50));

	selectedItemIndex = 0;
}

Pause::~Pause() {
	
}

void Pause::update() {

}

void Pause::render(RenderTarget* target) {
	target->draw(background);
	target->draw(container);
	target->draw(textpause);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		target->draw(menu[i]);
	}
}

void Pause::pauseState() {
	this->pausedStatus = true;
}

void Pause::unpauseState() {
	this->pausedStatus = false;
}

void Pause::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void Pause::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

int Pause::GetPressedItem(){	return selectedItemIndex;		}
bool Pause::paused() {		return pausedStatus;    }	